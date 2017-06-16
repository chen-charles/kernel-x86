#ifndef _KLIB_INTR_H
#define _KLIB_INTR_H 1

#include <klib_sl/type.h>
#include <klib_sl/c/klib_sl.h>


//Processor built-in Interrupts Intel 3A 6-20 ~ 6-50
#define INT_VEC_DE	0
#define INT_VEC_DB	1
#define INT_VEC_NMI	2
#define INT_VEC_BP	3
#define INT_VEC_OF	4
#define INT_VEC_BR	5
#define INT_VEC_UD	6
#define INT_VEC_NM	7
#define INT_VEC_DF	8
#define INT_VEC_CSO	9
#define INT_VEC_TS	10
#define INT_VEC_NP	11
#define INT_VEC_SS	12
#define INT_VEC_GP	13
#define INT_VEC_PF	14
#define INT_VEC_15	15
#define INT_VEC_MF	16
#define INT_VEC_AC	17
#define INT_VEC_MC	18
#define INT_VEC_XM	19
#define INT_VEC_VE	20
#define INT_VEC_CP  21

//LAPIC & IOAPIC IRQ
#define INT_VEC_APIC_TIMER	32	//apci-timer tick	IRQ0


//User-Defined Interrupts Intel 3A 6-51
#define INTERNEL_INTERRUPT_BASE	128

#endif
