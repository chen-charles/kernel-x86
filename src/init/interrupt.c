#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>

#include    <klib_ad/x86/idt.h>
#include    <klib_ad/x86/instruction.h>

#include    "include/memloc.h"
#include	"include/interrupt.h"
#include    "include/bochsdbg.h"

//INTR_STACKTOP interrupt stacktop: task-switch context save
//interrupt stack is always cleared no matter what
int interrupt(void* esp, uint32_t int_id)
{
    // bochsdbg_bp_if_equal(int_id, 32);
    //(*(SYS_INTERRUPT_SIGNALS+int_id))++;
    if (InterruptMasked(int_id))
        return 0;
    if (int_id == INT_VEC_APIC_SPUR)
        return 0;

    /* you could install custom handlers for the following intr. */
    if (int_id == INT_VEC_APIC_TIMER)
        TickSystemInternalTime();
    else if (int_id == INT_VEC_IOAPIC_IRQ1)
    {
        /* 
         * Read keyboard status
         */
        byte status = in_byte(0x64);
        byte scancode = in_byte(0x60);

        return 0;
    }

    // handle custom interrupts
    
    // bochsdbg_bp_eax(get_interrupt_handler(32));

    uintptr_t* handler = (uintptr_t*)pIHTable;
    handler += int_id;
    if (*handler == 0)
        return 1;

    return (uintptr_t)(*handler);
    // return (*(interrupt_handler)(*handler))(esp, int_id);
}

void set_interrupt_handler(interrupt_handler handler, uint8_t int_id)
{
    if (int_id >= 256 || int_id < 0) return;
    
    cli();
    
    uintptr_t* p = (uintptr_t*)pIHTable;
    p += int_id;
    *p = (uintptr_t)handler;

    sti();
}

interrupt_handler get_interrupt_handler(uint8_t int_id)
{
    if (int_id >= 256 || int_id < 0) return (interrupt_handler)0;
    
    uintptr_t* handler = (uintptr_t*)pIHTable;
    handler += int_id;

    return (interrupt_handler)(*handler);
}