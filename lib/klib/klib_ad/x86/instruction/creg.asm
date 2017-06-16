%include "/x86.inc"

global read_cr0
global read_cr1
global read_cr2
global read_cr3
global read_cr4

global write_cr0
global write_cr1
global write_cr2
global write_cr3
global write_cr4

read_cr0:
	mov eax, cr0
	ret
	
read_cr1:
	mov eax, cr1
	ret
	
read_cr2:
	mov eax, cr2
	ret

read_cr3:
	mov eax, cr3
	ret
	
read_cr4:
	mov eax, cr4
	ret
	
write_cr0:
	push ebp
	mov ebp, esp
	
	mov eax, [c_param(0)]
	mov cr0, eax
	
	pop ebp
	ret
	
write_cr1:
	push ebp
	mov ebp, esp
	
	mov eax, [c_param(0)]
	mov cr1, eax
	
	pop ebp
	ret
	
write_cr2:
	push ebp
	mov ebp, esp
	
	mov eax, [c_param(0)]
	mov cr2, eax
	
	pop ebp
	ret
	
write_cr3:
	push ebp
	mov ebp, esp
	
	mov eax, [c_param(0)]
	mov cr3, eax
	
	pop ebp
	ret
	
write_cr4:
	push ebp
	mov ebp, esp
	
	mov eax, [c_param(0)]
	mov cr4, eax
	
	pop ebp
	ret
	
	