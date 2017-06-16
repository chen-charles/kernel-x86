#include <klib_ad/x86/lapic.h>
#include <klib_ad/x86/ioapic.h>
#include "include/interrupt.h"
#include <klib_ad/x86/instruction.h>

#include    "include/memloc.h"

void mapLAPIC(uintptr_t apic_base, uint32_t ticks_per_second);
/* force enable lapic if not enabled, enable lapic interrupts */

int lapic_init()
{
	
    //this block is used to clear ALL old PCI interrupts invoked
    //this block ensures the correctness so absolutely NO previous interrupts will get in the way
    //IRQ0~IRQ15
    //MUST AFTER IDT SETUP

    for (int i=0; i<16; i++)
        mask_interrupt(i);
    sti();
    for (int i=0; i<100000; i++);
    cli();
    for (int i=0; i<16; i++)
        unmask_interrupt(i);
    
    enableLAPIC();

    //setup APIC, interrupts and timer
    //base_addr, # of ticks per second
    //system timer percision
    mapLAPIC((0xfffff000&cpuGetLAPICBase()), APIC_TIMER_FREQUENCY);
	*((uint64_t*)SYSTEM_INTERNAL_TIME_PTR) = 0;
    
    return cpuGetLAPICBase();
}

int ioapic_init()
{
	write_ioapic_register(DEFAULT_IOAPIC_LOC, 0x12, INT_VEC_IOAPIC_IRQ1);
    write_ioapic_register(DEFAULT_IOAPIC_LOC, 0x13, 0);
}

void mapLAPIC(uintptr_t apic_base, uint32_t ticks_per_second)
{
/*
	//CMCI
	uint32_t CMCI = 0;
	setbit(&CMCI, 16);	//not masked
	CMCI += INT_VEC_APIC_CMCI;
	memcpy(0xFEE002F0, &CMCI, sizeof(CMCI));
*/
	//Timer
	//osdev code
    
    //initialize PIT Ch 2 in one-shot mode
	//wait for 1/100 second
	uint32_t tmp, cpubusfreq;
	out_byte(0x61, (in_byte(0x61)&0xFD)|1);
	out_byte(0x43,0xB2);
	//1193180/100 Hz = 11931 = 2e9bh
	out_byte(0x42,0x9B);	//LSB
	in_byte(0x60);	//short delay
	out_byte(0x42,0x2E);	//MSB
 
	//reset PIT one-shot counter (start counting)
	tmp=(uint32_t)(in_byte(0x61)&0xFE);
	out_byte(0x61,(uint8_t)tmp);		//gate low
	out_byte(0x61,(uint8_t)tmp|1);		//gate high
	//reset APIC timer (set counter to -1)
	*(uint32_t*)(apic_base+APIC_TMRINITCNT)=0xFFFFFFFF;
 
	//now wait until PIT counter reaches zero
	while(!(in_byte(0x61)&0x20));
 
	//stop APIC timer
	*(uint32_t*)(apic_base+APIC_LVT_TMR)=APIC_DISABLE;
 
	//now do the math...
	cpubusfreq=((0xFFFFFFFF-*(uint32_t*)(apic_base+APIC_TMRCURRCNT))+1)*16*100;
	tmp=cpubusfreq/ticks_per_second/16;
 
	//sanity check, now tmp holds appropriate number of ticks, use it as APIC timer counter initializer
	*(uint32_t*)(apic_base+APIC_TMRINITCNT)=(tmp<16?16:tmp);
	//finally re-enable timer in periodic mode
	*(uint32_t*)(apic_base+APIC_LVT_TMR)=32|TMR_PERIODIC;
	//setting divide value register again not needed by the manuals
	//although I have found buggy hardware that required it
	*(uint32_t*)(apic_base+APIC_TMRDIV)=0x03;
        
//	uint32_t TIMER = 0;
////	setbit(&TIMER, 16);
//	setbit(&TIMER, 17);	//periodic
//	TIMER |= INT_VEC_APIC_TIMER;
//	memcpy((void*)0xFEE00320, &TIMER, sizeof(TIMER));
//	uint32_t TIMER_DCR = 0;	//Divide Configuration Reg.	//Intel 3A 10-16
//	clearbit(&TIMER_DCR, 0);
//	setbit(&TIMER_DCR, 1);
//	setbit(&TIMER_DCR, 3);
//	memcpy((void*)0xFEE003E0, &TIMER_DCR, sizeof(TIMER_DCR));
//	uint32_t TIMER_IC = 0x0000ffff;	//Initial Count	//Intel 3A 10-17
//	memcpy((void*)0xFEE00380, &TIMER_IC, sizeof(TIMER_IC));

	//Thermal Monitor
	uint32_t TM = 0;
//	setbit(&TM, 16);
	TM += INT_VEC_APIC_TM;
	*((uint32_t*)0xFEE00330) = TM;
	//memcpy((void*)0xFEE00330, &TM, sizeof(TM));

	//Performance Counter
	uint32_t PC = 0;
//	setbit(&PC, 16);
	PC += INT_VEC_APIC_PC;
	*((uint32_t*)0xFEE00340) = PC;
	// memcpy((void*)0xFEE00340, &PC, sizeof(PC));

	//LINT0
	uint32_t LINT0 = 0;
//	setbit(&LINT0, 16);
	setbit(&LINT0, 15);
	LINT0 += INT_VEC_APIC_LINT0;
	*((uint32_t*)0xFEE00350) = LINT0;
	// memcpy((void*)0xFEE00350, &LINT0, sizeof(LINT0));

	//LINT1
	uint32_t LINT1 = 0;
//	setbit(&LINT1, 16);
	LINT1 += INT_VEC_APIC_LINT1;
	*((uint32_t*)0xFEE00360) = LINT1;
	// memcpy((void*)0xFEE00360, &LINT1, sizeof(LINT1));

	//Error
	uint32_t ERR = 0;
//	setbit(&ERR, 16);
	ERR += INT_VEC_APIC_ERR;
	*((uint32_t*)0xFEE00370) = ERR;
	// memcpy((void*)0xFEE00370, &ERR, sizeof(ERR));

}
