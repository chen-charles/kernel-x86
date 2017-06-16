// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_GDT_H_
#define _KLIB_GDT_H_

#include <klib_sl/type.h>


#define DA_32		0x4000
#define DA_LIMIT_4K	0x8000

#define DA_DPL0	0x00
#define DA_DPL1	0x20
#define DA_DPL2	0x40
#define DA_DPL3	0x60

#define DA_DR	0x90
#define DA_DRW	0x92
#define DA_DRWA	0x93
#define DA_C	0x98
#define DA_CR	0x9A
#define DA_CCO	0x9C
#define DA_CCOR	0x9E

#define DA_LDT		0x82
#define DA_TaskGate	0x85
#define DA_386TSS	0x89
#define DA_386CGate	0x8C
#define DA_386IGate	0x8E
#define DA_386TGate	0x8F

typedef struct s_descriptor
{
	uint16_t	limit_low;		/* Limit */
	uint16_t	base_low;		/* Base */
	uint8_t	base_mid;		/* Base */
	uint8_t	attr1;			/* P(1) DPL(2) DT(1) TYPE(4) */
	uint8_t	limit_high_attr2;	/* G(1) D(1) 0(1) AVL(1) LimitHigh(4) */
	uint8_t	base_high;		/* Base */
}DESCRIPTOR;

typedef struct s_gate
{
	uint16_t	offset_low;	/* Offset Low */
	uint16_t	selector;	/* Selector */
	uint8_t	dcount;
	uint8_t	attr;		/* P(1) DPL(2) DT(1) TYPE(4) */
	uint16_t	offset_high;	/* Offset High */
}GATE;

typedef struct s_tss {
	uint32_t	backlink;
	uint32_t	esp0;		/* stack pointer to use during interrupt */
	uint32_t	ss0;		/*   "   segment  "  "    "        "     */
	uint32_t	esp1;
	uint32_t	ss1;
	uint32_t	esp2;
	uint32_t	ss2;
	uint32_t	cr3;
	uint32_t	eip;
	uint32_t	flags;
	uint32_t	eax;
	uint32_t	ecx;
	uint32_t	edx;
	uint32_t	ebx;
	uint32_t	esp;
	uint32_t	ebp;
	uint32_t	esi;
	uint32_t	edi;
	uint32_t	es;
	uint32_t	cs;
	uint32_t	ss;
	uint32_t	ds;
	uint32_t	fs;
	uint32_t	gs;
	uint32_t	ldt;
	uint16_t	trap;
	uint16_t	iobase;
	/*uint8_t	iomap[2];*/
}TSS;

void init_pm_desc(DESCRIPTOR* p_desc, uint32_t base, uint32_t limit, uint16_t attribute);
uint16_t mk_selector(uint16_t index, uint8_t RPL, bool isLDT);

#endif
