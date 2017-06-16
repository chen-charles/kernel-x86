%include    "/../asm.inc"
%include    "/multiboot2.inc"


bits 32
align 4

extern  init

[SECTION .data]

[SECTION .bss]
StackSpace		resb	10 * 1024
StackTop:


[section .text]
global _start
global hang

_start:
	jmp .realstart

;ensures the multiboot header is in the very front of the program
align 8 ;required as alignment of 64-bits
MULTIBOOT2_HEADER_LENGTH EQU .multiboot2_end - .multiboot2
.multiboot2:
    dd MULTIBOOT2_HEADER_MAGIC   ; magic number (multiboot 2)
    dd 0                         ; architecture 0 (protected mode i386)
    ;dd 24
    ;dd .multiboot2_end - .multiboot2 ; header length
    dd MULTIBOOT2_HEADER_LENGTH
    ; checksum
    ;dd 0x100000000 - (MULTIBOOT2_HEADER_MAGIC + 0 + (.multiboot2 - .multiboot2_end))
    ;dd 0x100000000 - (MULTIBOOT2_HEADER_MAGIC + 0 + 24)
    dd 0x100000000 - (MULTIBOOT2_HEADER_MAGIC + 0 + MULTIBOOT2_HEADER_LENGTH)
    
    ; multiboot tags 
    InformationRequestTag   0, 0
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
        cli
        hlt
        
.realstart:
        cli
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
        