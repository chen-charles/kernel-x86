%ifndef __ASM__
%define __ASM__

;DECLARATIONS MUST MATCH GLOBAL.H!!

SYS_LAPIC_ADDR EQU 0xed00  ;ends at 0xed08
SYS_FSC_ENABLED_ADDR    EQU 0xe408

PAGING_DATA_ADDR EQU 200000h ;2mb
PAGING_BASE_ADDR EQU 201000h ;1024*4 = 1000h
PG_RO_S EQU 153
PG_RW_S EQU 155
PG_RO_U EQU 157
PG_RW_U EQU 159

op_size	EQU	4
%define c_param(num) ebp+((num+2)*op_size)
NULL	EQU	0
NULLPTR	EQU	0


PM_RING0_STACKTOP   EQU 0x0000e000

; usage: Descriptor Base, Limit, Attr
;        Base:  dd
;        Limit: dd (low 20 bits available)
;        Attr:  dw (lower 4 bits of higher byte are always 0)
%macro Descriptor 3
	dw	%2 & 0FFFFh				; seg limit 1				(2 字节)
	dw	%1 & 0FFFFh				; seg base 1				(2 字节)
	db	(%1 >> 16) & 0FFh			; seg base 2				(1 字节)
	dw	((%2 >> 8) & 0F00h) | (%3 & 0F0FFh)	; attr 1 + seg limit 2 + attr 2		(2 字节)
	db	(%1 >> 24) & 0FFh			; seg base 3				(1 字节)
%endmacro ; 8 bytes in total

; usage: Gate Selector, Offset, DCount, Attr
;        Selector:  dw
;        Offset:    dd
;        DCount:    db
;        Attr:      db
%macro Gate 4
	dw	(%2 & 0FFFFh)				; offset 1				(2 字节)
	dw	%1					; selector				(2 字节)
	dw	(%3 & 1Fh) | ((%4 << 8) & 0FF00h)	; attr					(2 字节)
	dw	((%2 >> 16) & 0FFFFh)			; offset 2				(2 字节)
%endmacro ; 8 bytes in total

DA_32		EQU	4000h	; 32 位段
DA_LIMIT_4K	EQU	8000h	; 段界限粒度为 4K 字节

DA_DPL0		EQU	  00h	; DPL = 0
DA_DPL1		EQU	  20h	; DPL = 1
DA_DPL2		EQU	  40h	; DPL = 2
DA_DPL3		EQU	  60h	; DPL = 3
;----------------------------------------------------------------------------
; 存储段描述符类型值说明
;----------------------------------------------------------------------------
DA_DR		EQU	90h	; 存在的只读数据段类型值
DA_DRW		EQU	92h	; 存在的可读写数据段属性值
DA_DRWA		EQU	93h	; 存在的已访问可读写数据段类型值
DA_C		EQU	98h	; 存在的只执行代码段属性值
DA_CR		EQU	9Ah	; 存在的可执行可读代码段属性值
DA_CCO		EQU	9Ch	; 存在的只执行一致代码段属性值
DA_CCOR		EQU	9Eh	; 存在的可执行可读一致代码段属性值
;----------------------------------------------------------------------------
; 系统段描述符类型值说明
;----------------------------------------------------------------------------
DA_LDT		EQU	  82h	; 局部描述符表段类型值
DA_TaskGate	EQU	  85h	; 任务门类型值
DA_386TSS	EQU	  89h	; 可用 386 任务状态段类型值
DA_386CGate	EQU	  8Ch	; 386 调用门类型值
DA_386IGate	EQU	  8Eh	; 386 中断门类型值
DA_386TGate	EQU	  8Fh	; 386 陷阱门类型值

;----------------------------------------------------------------------------
;Selector Attributes
SA_RPL0		EQU	0	; ┓
SA_RPL1		EQU	1	; ┣ RPL
SA_RPL2		EQU	2	; ┃
SA_RPL3		EQU	3	; ┛

SA_TIG		EQU	0	; ┓TI	;GDT
SA_TIL		EQU	4	; ┛	;LDT

%endif