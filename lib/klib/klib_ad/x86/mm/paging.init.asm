%include "/x86.inc"

;global init_paging
global flush_cache

;void init_paging(uint32_t s_flatdata32, uintptr_t paging_data_addr);
init_paging: ;phyaddr=linaddr   ;selector data 32
    push	ebp
    mov ebp, esp
    push	es
    mov	eax, [c_param(0)]
    mov	es, ax
    mov	edi, [c_param(1)]
    mov	eax, 0	;base addr
    or	eax, PG_RW_S

    mov	ecx, 1024
    .1:
        mov	[es:edi], eax
        add	eax, 400000h	;4mb
        add	edi, 4
        loop	.1

    mov	eax, [c_param(1)]
    mov	cr3, eax
    ;CR4.PSE

    mov	eax, cr4
    or	eax, 10h	;0b10000
    mov	cr4, eax
    mov	eax, cr0
    or	eax, 80000000h
    mov	cr0, eax
    jmp	short .2

    .2:
        nop
    pop	es
    pop	ebp

    ret

flush_cache:
    push	ebp
    mov ebp, esp

    wbinvd  ;flush ALL cache
    mov eax, cr3
    mov cr3, eax

    pop	ebp
    ret

