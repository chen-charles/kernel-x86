%include "/x86.inc"

global readmsr
global writemsr

;void readmsr(uint32_t msr, byte* b_array_8);
readmsr:
	push	ebp
	mov 	ebp, esp
	push	ecx
	push	eax
	push	edx
	push	ebx

	mov	ecx, [c_param(0)]
	rdmsr
	mov	ebx, [c_param(1)]
	mov	[ebx], eax
	mov	[ebx+4], edx
	
	pop	ebx
	pop	edx
	pop	eax
	pop	ecx
	pop	ebp
	ret

;void writemsr(uint32_t msr, byte* b_array_8);
writemsr:
	push	ebp
	mov 	ebp, esp
	push	ecx
	push	eax
	push	edx
	push	ebx

	mov	ebx, [c_param(1)]
	mov	eax, [ebx]
	mov	edx, [ebx+4]

	mov	ecx, [c_param(0)]
	wrmsr
	
	pop	ebx
	pop	edx
	pop	eax
	pop	ecx
	pop	ebp
	ret
	
	