
#include "idt.h"


void init_idt_desc(void* ptr, void* handler, byte privilege, uint16_t selector)
{
	GATE *p_gate	= ptr;
	uint32_t base	= (uint32_t)handler;
	p_gate->offset_low	= base & 0xFFFF;
	p_gate->selector	= selector;
	p_gate->dcount	= 0;
	p_gate->attr	= DA_386IGate | (privilege << 5);
	p_gate->offset_high	= (base >> 16) & 0xFFFF;
}

