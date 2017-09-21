#include	<klib_ad/x86/lapic.h>
#include	<klib_ad/x86/ioapic.h>
#include	"include/interrupt.h"
#include	<klib_ad/x86/instruction.h>

#include    "include/memloc.h"
#include	"include/bochsdbg.h"

void mapLAPIC(uintptr_t apic_base, uint32_t ticks_per_second);
/* force enable lapic if not enabled, enable lapic interrupts */

int lapic_init()
{
	
    //this block is used to clear ALL old PCI interrupts invoked
    //this block ensures the correctness so absolutely NO previous interrupts will get in the way
    //IRQ0~IRQ15
    //MUST AFTER IDT SETUP

    for (int i=0; i<16; i++)
        MaskInterrupt(i);
    sti();
    for (int i=0; i<100000; i++);
    cli();
    for (int i=0; i<16; i++)
        UnMaskInterrupt(i);
    
    enableLAPIC();

    //setup APIC, interrupts and timer
    //base_addr, # of ticks per second
    //system timer percision
    mapLAPIC((0xfffff000&cpuGetLAPICBase()), APIC_TIMER_FREQUENCY);
    
    return cpuGetLAPICBase();
}

int ioapic_init()
{
	// wiki.osdev.org/IOAPIC

	// IOREDTBL
	// Following there are two 32-bit register for each IRQ. The first IRQ has indexes 0x10 and 0x11, the second 0x12 and 0x13, the third 0x14 and 0x15, and so on. So the Redirection Entry register for IRQ n is 0x10 + n * 2 (+ 1). In the first of the two registers you access to the LOW uint32_t / bits 31:0, and the second for the high uint32_t / 63:32. Each redirection entry is made of the following fields:
	// Field	Bits	Description
	// Vector	0 - 7	The Interrupt vector that will be raised on the specified CPU(s).
	// Delivery Mode	8 - 10	How the interrupt will be sent to the CPU(s). It can be 000 (Fixed), 001 (Lowest Priority), 010 (SMI), 100 (NMI), 101 (INIT) and 111 (ExtINT). Most of the cases you want Fixed mode, or Lowest Priority if you don't want to suspend a high priority task on some important Processor/Core/Thread.
	// Destination Mode	11	Specify how the Destination field shall be interpreted. 0: Physical Destination, 1: Logical Destination
	// Delivery Status	12	If 0, the IRQ is just relaxed and waiting for something to happen (or it has fired and already processed by Local APIC(s)). If 1, it means that the IRQ has been sent to the Local APICs but it's still waiting to be delivered.
	// Pin Polarity	13	0: Active high, 1: Active low. For ISA IRQs assume Active High unless otherwise specified in Interrupt Source Override descriptors of the MADT or in the MP Tables.
	// Remote IRR	14	TODO
	// Trigger Mode	15	0: Edge, 1: Level. For ISA IRQs assume Edge unless otherwise specified in Interrupt Source Override descriptors of the MADT or in the MP Tables.
	// Mask	16	Just like in the old PIC, you can temporary disable this IRQ by setting this bit, and reenable it by clearing the bit.
	// Destination	56 - 63	This field is interpreted according to the Destination Format bit. If Physical destination is choosen, then this field is limited to bits 56 - 59 (only 16 CPUs addressable). You put here the APIC ID of the CPU that you want to receive the interrupt. TODO: Logical destination format...
	
	// keyboard 
	write_ioapic_register(DEFAULT_IOAPIC_LOC, IOREDTBL(1), INT_VEC_IOAPIC_IRQ1);
	write_ioapic_register(DEFAULT_IOAPIC_LOC, IOREDTBL(1)+1, 0);
	
	// serial port 1/3 
	write_ioapic_register(DEFAULT_IOAPIC_LOC, IOREDTBL(4), INT_VEC_IOAPIC_IRQ4);
	write_ioapic_register(DEFAULT_IOAPIC_LOC, IOREDTBL(4)+1, 0);
	
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
