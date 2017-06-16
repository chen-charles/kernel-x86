%include "/x86.inc"

global outb
global outw
global outd
global inb
global inw
global ind

;void outb(uint16_t port, uint8_t val);
outb:
	push ebp
	mov ebp, esp
	push edx
	
	xor edx, edx
	xor eax, eax
	mov edx, [c_param(0)]
	mov eax, [c_param(1)]
	
	out dx, al
	
	pop edx
	pop ebp
	ret
	
;void outw(uint16_t port, uint16_t val);
outw:
	push ebp
	mov ebp, esp
	push edx
	
	xor edx, edx
	xor eax, eax
	mov edx, [c_param(0)]
	mov eax, [c_param(1)]
	
	out dx, ax
	
	pop edx
	pop ebp
	ret
	
;void outd(uint16_t port, uint32_t val);
outd:
	push ebp
	mov ebp, esp
	push edx
	
	xor edx, edx
	xor eax, eax
	mov edx, [c_param(0)]
	mov eax, [c_param(1)]
	
	out dx, eax
	
	pop edx
	pop ebp
	ret
	
;uint8_t inb(uint16_t port);
inb:
	push ebp
	mov ebp, esp
	push edx
	
	xor eax, eax
	
	mov dx, [c_param(0)]
	in al, dx
	
	pop edx
	pop ebp
	ret
	
;uint16_t inw(uint16_t port);
inw:
	push ebp
	mov ebp, esp
	push edx
	
	xor eax, eax
	
	mov dx, [c_param(0)]
	in ax, dx
	
	pop edx
	pop ebp
	ret
	
;uint32_t ind(uint16_t port);
ind:
	push ebp
	mov ebp, esp
	push edx
	
	xor eax, eax
	
	mov dx, [c_param(0)]
	in eax, dx
	
	pop edx
	pop ebp
	ret
	
