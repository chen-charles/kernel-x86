%ifndef _X86_INC_
%define _X86_INC_

op_size	EQU	4
NULL	EQU	0
NULLPTR	EQU	0


%define c_param(num) ebp+((num+2)*op_size)


PG_RO_S EQU 153
PG_RW_S EQU 155
PG_RO_U EQU 157
PG_RW_U EQU 159


%endif

