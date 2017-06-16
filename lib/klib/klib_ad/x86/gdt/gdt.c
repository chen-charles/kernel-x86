
#include "gdt.h"

void init_pm_desc(DESCRIPTOR* p_desc, uint32_t base, uint32_t limit, uint16_t attribute)
{
	p_desc->limit_low		= limit & 0x0FFFF;
	p_desc->base_low		= base & 0x0FFFF;
	p_desc->base_mid		= (base >> 16) & 0x0FF;
	p_desc->attr1			= attribute & 0xFF;
	p_desc->limit_high_attr2	= ((limit >> 16) & 0x0F) | (attribute >> 8) & 0xF0;
	p_desc->base_high		= (base >> 24) & 0x0FF;
	
}

uint16_t mk_selector(uint16_t index, uint8_t RPL, bool isLDT)
{
	uint16_t selector=0;
	if (isLDT) selector |= 4;
	selector |= RPL;
	return selector + index;
}

