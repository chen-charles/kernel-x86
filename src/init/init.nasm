%include    "/../asm.inc"

bits 32
align 4

extern  hang
extern  multiboot_startup
extern  gdt_init
extern  mk_selector

extern  memset

extern  c_idt_init

extern  lapic_init
extern  ioapic_init
extern  fpu_sse_init
extern  libmm_init
extern  libmalloc_init
;extern  malloc

extern  cpp_entry

global  init

init:
        ; machine-state is ready to be in C mode now
        
        ; reset shared buffer
        ; see memloc.h
        push    0xB00
        push    0
        push    0x500
        call    memset
        add     esp, 12

        ;parse multiboot here
        push    ebx
        call    multiboot_startup
        add esp, 4

        test    eax, eax
        jnz hang
        
        call    gdt_init
        test    eax, eax
        jz hang
        
        lgdt    [eax]

	; disable 8259A
	mov al, 0xff
	out 0xa1, al
	out 0x21, al

        call    c_idt_init
        jz hang

        lidt	[eax]

        
        push    0
        push    0
        push    8
        call    mk_selector
        add esp, 3*4
        
        lea ebx, [_init]
        push ax
        push ebx
        retf
        
 _init:
        mov ax, 0x18

        mov ss, ax
        mov es, ax
        mov ds, ax
        mov fs, ax
        mov gs, ax

        call    lapic_init
        call    ioapic_init
        sti

        call    fpu_sse_init
        call    libmm_init
        call    libmalloc_init

;        push    0x100000
;        call    malloc
;        add     esp, 4
       
        call    cpp_entry

        ;mov eax, 0xAAFFFFAA
        mov ebx, 0xFFAAAAFF
        jmp $
        