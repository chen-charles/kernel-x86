%include "/x86.inc"

global is_fpu_present
global is_sse_present

global fxsave
global fxrstor

;osdev
;bool is_fpu_present();
is_fpu_present:
%define CR0_TS  0b1000
%define CR0_EM  0b100

	push	ebp
	mov	ebp, esp


        pushad
	
        MOV EDX, CR0                            ; Start probe, get CR0
        push    edx
        AND EDX, (-1) - (CR0_TS + CR0_EM)       ; clear TS and EM to force fpu access
        MOV CR0, EDX                            ; store control word
        FNINIT                                  ; load defaults to FPU
        FNSTSW [.testword]                      ; store status word
        pop     edx
        mov cr0, edx
        CMP word [.testword], 0                 ; compare the written status with the expected FPU state
        popad
        JNE .nofpu                              ; jump if the FPU hasn't written anything (i.e. it's not there)
        JMP .hasfpu

        .testword: DW 0x55AA                    ; store garbage to be able to detect a change


.nofpu:
        xor eax, eax
        jmp .ret

.hasfpu:
        mov eax, 1

.ret:
	pop	ebp
	ret

;bool is_sse_present();
is_sse_present:
	push	ebp
	mov	ebp, esp
        pushad

        mov eax, 0x1
        cpuid
        test edx, 1<<25

        popad
        jnz .hasSSE

        xor eax, eax
        jmp .ret

.hasSSE:
        mov eax, 1

.ret:
        
	pop	ebp
	ret

;void fxsave(uintptr_t destination);
fxsave:
	push	ebp
	mov	ebp, esp
	
        push    ebx
        mov     ebx, [c_param(0)]
        fxsave  [ebx]
        pop     ebx

	pop	ebp
	ret

;void fxrstor(uintptr_t source);
fxrstor:
	push	ebp
	mov	ebp, esp
	
        push    ebx
        mov     ebx, [c_param(0)]
        fxrstor [ebx]
        pop     ebx

	pop	ebp
	ret

