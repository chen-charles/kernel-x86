%include    "/../asm.inc"
%include    "/multiboot2.inc"


bits 32
align 4

extern  init

[section .bss]
align 4
StackSpace		resb	4 * 4096
StackTop:


[section .text]
global _start
global hang

_start:
        xchg    bx, bx
	jmp .realstart

;ensures the multiboot header is in the very front of the program
;Boot State
;EAX    MAGIC
;EBX    pInfo
;CS     Read/Execute
;SS     Read/Write
;Protected Mode Enabled
;Paging Disabled
;Interrupt Flag Cleared (if)
align 8 ;required as alignment of 64-bits
MULTIBOOT2_HEADER_LENGTH EQU .multiboot2_end - .multiboot2
.multiboot2:
    dd MULTIBOOT2_HEADER_MAGIC   ; magic number (multiboot 2)
    dd 0                         ; architecture 0 (protected mode i386)
    dd MULTIBOOT2_HEADER_LENGTH
    dd 0x100000000 - (MULTIBOOT2_HEADER_MAGIC + 0 + MULTIBOOT2_HEADER_LENGTH)
    
    ; multiboot tags 
    InformationRequestTag   0, 1
    dd 9

    AddressTag  0, .multiboot2, _start, 0, 0
    EntryAddressTag 0, _start
    framebufferTag  0, 800, 600, 32
    ModuleAlignmentTag 0

    ; required end tag
    dw 0    ; type
    dw 0    ; flags
    dd 8    ; size
.multiboot2_end:

align 4
.raw_boot:
        hlt

.realstart:
        mov esp, StackTop   ;setup stack pointer
        cmp eax, MULTIBOOT2_BOOTLOADER_MAGIC     ;is multiboot failed
        jne .raw_boot
        
        push    0
        popf

        jmp init
        
        nop
        nop
        
hang:
        cli
        hlt
        