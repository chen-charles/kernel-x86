global _start
extern main


bits 32
align 4

[section .bss]


[section .text]
_start:
    call main
    
    jmp $
