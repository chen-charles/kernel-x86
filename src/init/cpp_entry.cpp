#include    "include/cpp_entry.hpp"
#include    "include/memloc.h"
#include    "include/bochsdbg.h"
#include    <klib_ad/x86/gdt.h>
#include    <klib_ad/x86/idt.h>
#include    <klib_ad/x86/fpusse.h>
#include    <klib_ad/x86/mm.paging.h>
#include    <libmm/libmm.h>
#include    "include/kinit_alloc.h"

extern "C" void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}

void *operator new(size_t size) { return calloc(1, size); }
void *operator new[](size_t size) { return calloc(1, size); }
void operator delete(void *p) { free(p); }
void operator delete[](void *p) { free(p); }

void libproc_setup();
extern "C" int cpp_entry()
{
    // tasks:
    // setup libproc scheduler
    // prepare current process
    // prepare kernel-init process
    // wait for interrupt jump
    
    libproc_setup();

    return 0;   // should never be reached
}

// extern "C" void __stack_chk_fail(){}
// extern "C" int snprintf ( char * s, size_t n, const char * format, ...)
// {
//     return 0;
// }

// extern "C" long int strtol (const char* str, char** endptr, int base)
// {
//     return 0;
// }

// extern "C" const unsigned short * * __ctype_b_loc (void)
// {
//     return 0;
// }
// extern "C" int * __errno_location(void)
// {
//     return 0;
// }
// extern "C" char *strdup(const char *s1)
// {
//     return 0;
// }

#include    <libmm/libmm.h>
#include    <libproc/libproc.hpp>
#include    "include/memloc.h"

#include    "include/interrupt.h"
extern "C"
{
    void *mmap(void* addr, size_t len, page_property* usage);
}

typedef struct
{
    /* fpu state, alignment 16 required */
    byte    fxsave[512];

    /*
    if we use the AVL bits in the paging structure (which is avail. on both x86 and x86_64)
    we can set pages available to a process with a bitmap
    then mmap as normal with libmm
    */
    byte    memory_owned[128];   // present-inuse pages, 1024 pages

    /* pushad order */
    uint32_t    edi;    // EDI: esp - 0x20
    uint32_t    esi;
    uint32_t    ebp;
    uint32_t    esp_stub;    // this value is not restored by popad
    uint32_t    ebx;
    uint32_t    edx;
    uint32_t    ecx;
    uint32_t    eax;    // EAX: esp - 0x4

    // stack layout right after interrupt is occured
    // ->esp in param is right here
    // the error code would be here if present
    // the handler MUST pop the error code before IRET(D) by returning 0x45525243 'ERRC'

    /* iretd uses those to restore the status */
    uint32_t    eip;    // esp + 0x0
    uint32_t    cs;     // esp + 0x4
    uint32_t    eflags; // esp + 0x8

    // x-rings
    uint32_t    esp;    // esp + 0xC    // esp to return    // ss:esp is only used when returning across rings
    uint32_t    ss;     // esp + 0x10

    Privilege priv;
}
ContextSwitchCtx;

extern "C" PHYSICAL_ADDRESS fetch_page_addr(VIRTUAL_ADDRESS from);

int ctxSwitch_timerTick_intr(void* esp, uint8_t int_id)
{
    if ((int)GetSystemInternalTime()%10) 
        return 0;

    Scheduler* scheduler = GetTypedPtrAt(Scheduler, LIBPROC_SCHEDULER_PTR);
    page_property prop;

    if (scheduler->tick())  // hardware ctx switch required, slow, 1ms tick will trash the cpu, exception-free code
    {
        ProcessContextInfo *prev = scheduler->prevCtx(), *next = scheduler->nextCtx();
        Process *prevProc = scheduler->prevProc(), *nextProc = scheduler->nextProc();
        ContextSwitchCtx *prevCtx = (ContextSwitchCtx*)(prev == nullptr ? 0 : (prev->ptr)), *nextCtx = (ContextSwitchCtx*)(next->ptr);

        /*
        note: this handler will always run in Ring 0 (KERNEL)
        that is, a kernel-level process will not push ss:esp
        it is the handler's responsibility to save the kernel stack to tss

        tss kernel stack is intr-handler exclusive
        a manual stack switch must occur for the next kernel process

        note: (kernel->kernel) must perform stack switch to next stack
        note: (kernel->user) must perform stack switch to tss
        note: tss stack should be emptied whenever intr returns
        note: tss stack must allow underflow (->user)

        0a. nullptr(KERNEL)->KERNEL_INT->KERNEL
            no stack shift, entering from init
        0b. nullptr(KERNEL)->KERNEL_INT->USER
            #GP
            the first running process must be KERNEL
        0c. nullptr(USER)
            #GP
            once entered scheduling, there will always be a process running
            if everyone is idling, then the current process will not require a ctx switch
        1. KERNEL->KERNEL_INT->KERNEL   // no ss:esp pushed/restored
            calculate&store prev->esp
            shift the oldStack to the newStack
        2. KERNEL->KERNEL_INT->USER     // no ss:esp pushed, restore ss:esp
            calculate prev->esp
            shift the stack to TSS stack
            restore next->ss/esp
        3. USER->KERNEL_INT->KERNEL     // ss:esp pushed, no restore
            store prev->ss/esp
            shift the tssStack to the newStack
            shift the stack down
        4. USER->KERNEL_INT->USER       // ss:esp pushed, restore   // simple case
            store prev->ss/esp
            restore next->ss/esp
        */


        // store prevCtx
        if (prev != nullptr)
        {
            fxsave(&(prevCtx->fxsave[0]));
            for (int i=-8; i<5; i++)
                *(&(prevCtx->eip)+i) = *(((uint32_t*)esp)+i);
        }

        for (int i=0; i<128; i++)
        {
            for (int j=0; j<8; j++)
            {
                PHYSICAL_ADDRESS mapped = read_page((i*8+j)*PAGESIZE, &prop);

                // save old ctx
                if (prev != nullptr)
                {
                    if (prop.required.present && prop.required.busy)
                    {
                        setbit(&(prevCtx->memory_owned[i]), j);
                    }
                    else
                    {
                        clearbit(&(prevCtx->memory_owned[i]), j);
                    }
                }

                // restore new ctx
                if (TESTBIT(nextCtx->memory_owned[i], j) 
                    || (prevCtx != nullptr && (i*8+j)*PAGESIZE == lookup_virt_to_phys(prevCtx->esp, GetTypedPtrAt(MM_Data_Section_H, LIBMM_DATSEC_PTR))))
                {
                    prop.required.present = true;
                    prop.required.read = true;
                    prop.required.write = true;
                    prop.required.execute = true;
                    prop.required.busy = true;
                    prop.required.privileged = false;
                    write_page(fetch_page_addr((i*8+j)*PAGESIZE), (i*8+j)*PAGESIZE, &prop);
                    // write_page((i*8+j)*PAGESIZE, mapped ? mapped : lookup_phys_to_virt((i*8+j)*PAGESIZE, GetTypedPtrAt(MM_Data_Section_H, LIBMM_DATSEC_PTR)), &prop);
                    flush_page((i*8+j)*PAGESIZE);
                }
                else if (mapped)
                {
                    prop.required.present = false;
                    write_page(mapped, (i*8+j)*PAGESIZE, &prop);
                    flush_page((i*8+j)*PAGESIZE);
                }
            }
        }

        // case 0a switch to the new stack from the current stack
        if ((prevProc == nullptr || prevProc->priv == Privilege::KERNEL) && nextProc->priv == Privilege::KERNEL)
        {
            bochsdbg_bp_eax(0xA);
            
            // case 1
            if (prevProc != nullptr)
                prevCtx->esp = prevCtx->esp_stub + sizeof(uint32_t) * 3;  // intr off;   // exact previous stack location


            __asm__ volatile ( "push eax" );
            __asm__ volatile ( "mov eax, esp" );
            __asm__ volatile ( "sub eax, ebp" );

            __asm__ volatile ( "pushad" );
            register uint32_t* target_stack __asm__("eax") = (uint32_t*)nextCtx->esp;
            register uintptr_t esp_cur __asm__("ebx");
            register int i __asm__("ecx") = 2;
            __asm__ volatile ( "mov %0, esp" : "=rm" ( esp_cur ));
            for (register uint32_t* esp_old __asm__("edx") = (uint32_t*)esp + 2; esp_old > (uint32_t*)esp_cur; esp_old--)
                *(uint32_t*)(target_stack + (i--)) = *esp_old;
            __asm__ volatile ( "mov esp, %0" : : "r" ((uintptr_t)( target_stack + i )));
            __asm__ volatile ( "popad" );

            __asm__ volatile ( "mov ebp, esp" );
            __asm__ volatile ( "sub ebp, eax" );
            __asm__ volatile ( "pop eax" );

            esp = (void*)(nextCtx->esp);
        }

        // case 2 KERNEL->KERNEL_INT->USER
        if (prevProc != nullptr && prevProc->priv == Privilege::KERNEL && nextProc->priv == Privilege::USER)
        {
            bochsdbg_bp_eax(2);

            prevCtx->esp = prevCtx->esp_stub + sizeof(uint32_t) * 3; // intr off;   // exact previous stack location

            __asm__ volatile ( "push eax" );
            __asm__ volatile ( "mov eax, esp" );
            __asm__ volatile ( "sub eax, ebp" );

            __asm__ volatile ( "pushad" );
            // shift to tss stack
            register uint32_t* target_stack __asm__("eax") = (uint32_t*)((TSS*)pTSSegment)->esp0;

            // x-rings underflow
            *(target_stack+3) = nextCtx->esp;
            *(target_stack+4) = nextCtx->ss;

            register uintptr_t esp_cur __asm__("ebx");
            register int i __asm__("ecx") = 2;
            __asm__ volatile ( "mov %0, esp" : "=rm" ( esp_cur ));
            for (register uint32_t* esp_old __asm__("edx") = (uint32_t*)esp + 2; esp_old > (uint32_t*)esp_cur; esp_old--)
                *(uint32_t*)(target_stack + (i--)) = *esp_old;
            __asm__ volatile ( "mov esp, %0" : : "r" ((uintptr_t)( target_stack + i )));
            __asm__ volatile ( "popad" );

            __asm__ volatile ( "mov ebp, esp" );
            __asm__ volatile ( "sub ebp, eax" );
            __asm__ volatile ( "pop eax" );

            esp = (void*)(uint32_t*)((TSS*)pTSSegment)->esp0;
        }

        // case 3
        if (prevProc != nullptr && prevProc->priv == Privilege::USER && nextProc->priv == Privilege::KERNEL)
        {
            bochsdbg_bp_eax(3);

            prevCtx->esp = prevCtx->esp_stub + sizeof(uint32_t) * 5;
            prevCtx->ss = *((uint32_t*)esp+4);

            // at tss stack, switch to kernel stack
            __asm__ volatile ( "push eax" );
            __asm__ volatile ( "mov eax, esp" );
            __asm__ volatile ( "sub eax, ebp" );

            __asm__ volatile ( "pushad" );
            register uint32_t* target_stack __asm__("eax") = (uint32_t*)(nextCtx->esp - sizeof(uint32_t) * 3);

            register uintptr_t esp_cur __asm__("ebx");
            register int i __asm__("ecx") = 2;
            __asm__ volatile ( "mov %0, esp" : "=rm" ( esp_cur ));
            for (register uint32_t* esp_old __asm__("edx") = (uint32_t*)esp + 2; esp_old > (uint32_t*)esp_cur; esp_old--)
                *(uint32_t*)(target_stack + (i--)) = *esp_old;
            __asm__ volatile ( "mov esp, %0" : : "r" ((uintptr_t)( target_stack + i )));
            __asm__ volatile ( "popad" );

            __asm__ volatile ( "mov ebp, esp" );
            __asm__ volatile ( "sub ebp, eax" );
            __asm__ volatile ( "pop eax" );

            esp = (void*)(nextCtx->esp - sizeof(uint32_t) * 3);
        }

        // case 4
        if (prevProc != nullptr && prevProc->priv == Privilege::USER && nextProc->priv == Privilege::USER)
        {
            bochsdbg_bp_eax(4);
            prevCtx->esp = *((uint32_t*)esp+3);
            prevCtx->ss = *((uint32_t*)esp+4);
            *((uint32_t*)esp+3) = nextCtx->esp;
            *((uint32_t*)esp+4) = nextCtx->ss;
        }

        // restore nextCtx
        fxrstor(&(nextCtx->fxsave[0]));
        for (int i=-8; i<5; i++)
            *(((uint32_t*)esp)+i) = *(&(nextCtx->eip)+i);

        bochsdbg_bp_eax(0x200);
    }

    return 0;
}

extern "C" void* aligned_malloc(size_t size, size_t alignment);

void uinitProcess()
{
    __asm__ volatile ("xor eax, eax");
    while (1) __asm__ volatile ("inc eax");
}

void kinitProcess()
{
    // pci scan

    __asm__ volatile ("xor ebx, ebx");
    while (1) __asm__ volatile ("inc ebx");
}

void set_tss_esp(uint32_t esp)
{
    TSS* tss = (TSS*)pTSSegment;
    tss->ss0 = 0x18;
    tss->esp0 = esp;
    __asm__ volatile (
        "mov ax, 0x50\n"
        "ltr ax");
}

Process* CreateProcessXRings(uintptr_t eip, Privilege priv, uint64_t priority)
{
    Scheduler* scheduler = GetTypedPtrAt(Scheduler, LIBPROC_SCHEDULER_PTR);
    ProcessContextInfo contextInfo;
    page_property prop;

    ContextSwitchCtx* pcsc = (ContextSwitchCtx*)aligned_malloc(sizeof(ContextSwitchCtx), 16);
    memset(pcsc, 0, sizeof(ContextSwitchCtx));

    read_page(0, &prop);
    prop.required.privileged = priv == Privilege::KERNEL;
    prop.required.privileged = false;

    pcsc->eax = 0;
    pcsc->esp = (uintptr_t)mmap(0, 0x400000, &prop) + 0x3fffcc;
    pcsc->eip = eip;
    pcsc->eflags = 0;

    switch (priv)
    {
        case Privilege::KERNEL:
            pcsc->cs = 0x08;    // allow RPL3 access
            pcsc->ss = 0x18;
            break;
        case Privilege::USER:
            pcsc->cs = 0x23;
            pcsc->ss = 0x2B;
            break;
        default:
        ;
    };

    for (int i=0; i<128; i++)
        for (int j=0; j<8; j++)
        {
            read_page((i*8+j)*PAGESIZE, &prop);
            if (prop.required.present)            
                setbit(&(pcsc->memory_owned[i]), j);
            else
                clearbit(&(pcsc->memory_owned[i]), j);

            if ((i*8+j)*PAGESIZE == lookup_virt_to_phys(pcsc->eip - (pcsc->eip%PAGESIZE), GetTypedPtrAt(MM_Data_Section_H, LIBMM_DATSEC_PTR)))
                setbit(&(pcsc->memory_owned[i]), j);
            if ((i*8+j)*PAGESIZE == lookup_virt_to_phys(pcsc->esp - (pcsc->esp%PAGESIZE), GetTypedPtrAt(MM_Data_Section_H, LIBMM_DATSEC_PTR)))
                setbit(&(pcsc->memory_owned[i]), j);
        }

    contextInfo.ptr = (uintptr_t)pcsc;
    contextInfo.len = sizeof(ContextSwitchCtx);
    return scheduler->CreateProcess(priority, contextInfo, priv);
}

void libproc_setup()
{
    cli();
    /* Scheduler and other temp. mallocs are allocated on vaddr 0x40000000~ */
    /* it's physical page is dynam. allocated by libmm */
    /* you MUST restore this paging reference as the scheduler object is in that area */

    /* note: process stores their physical page usage (as multiple process can be running on the same vaddr) */

    // libproc
    Scheduler* scheduler = new Scheduler();
    *((uintptr_t*)LIBPROC_SCHEDULER_PTR) = (uintptr_t)scheduler;

    ProcessContextInfo contextInfo;
    page_property prop;

    read_page(0, &prop);
    prop.required.privileged = false;

    // TSS xrings setup
    // this is the new kernel stack when kernel-curproc starts running
    TSS* tss = (TSS*)pTSSegment;
    memset(tss, 0, sizeof(TSS));
    uintptr_t intr_stkpg = (uintptr_t)mmap(0, 0x400000, &prop);
    set_tss_esp(intr_stkpg + 0x3fffcc); 

    // create kernel process, R0
    CreateProcessXRings((uintptr_t)kinitProcess, Privilege::KERNEL, 2);

    // create user-init process, R3
    CreateProcessXRings((uintptr_t)uinitProcess, Privilege::USER, 2);

    // signal scheduler tick is now available
    // set_interrupt_handler(&timerTick_intr, INT_VEC_APIC_TIMER);

    set_interrupt_handler(ctxSwitch_timerTick_intr, INT_VEC_APIC_TIMER);
    // wait for interrupt, end of init.
    sti();
    while (1);
}
