#include "lapic.h"
#include <klib_sl/c/string.h>

#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 // Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800
#define IA32_APIC_BASE_ADDR 0xfee00000

void enableLAPIC()
{
/* Hardware enable the Local APIC if it wasn't enabled */
	uintptr_t p = cpuGetLAPICBase();
	cpuSetLAPICBase(p);
	
/* Set the Spourious Interrupt Vector Register bit 8 to start receiving interrupts */
	byte* ptr = (byte*)(p + 0xf0);
	(*((uint32_t*)ptr)) = 39 | 0x100;
}

/* Set the physical address for local APIC registers */
void cpuSetLAPICBase(uintptr_t lapic)
{
	uint32_t edx = 0;
	uint32_t eax = (lapic & 0xfffff100) | IA32_APIC_BASE_MSR_ENABLE;
 
#ifdef __PHYSICAL_MEMORY_EXTENSION__
	edx = (lapic >> 32) & 0x0f;
#endif

	byte arr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	memcpy(&arr[0], &eax, sizeof(eax));
	memcpy(&arr[4], &edx, sizeof(edx));
	writemsr(IA32_APIC_BASE_MSR, (byte*)&arr);
}
 
/**
 * Get the physical address of the APIC registers page
 * make sure you map it to virtual memory ;)
 */
uintptr_t cpuGetLAPICBase()
{
	uint32_t eax, edx;
	byte arr[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	readmsr(IA32_APIC_BASE_MSR, (byte*)&arr);
	memcpy(&eax, &arr[0], sizeof(eax));
	memcpy(&edx, &arr[4], sizeof(edx));
 
#ifdef __PHYSICAL_MEMORY_EXTENSION__
	return (eax & 0xfffff100) | ((edx & 0x0f) << 32);
#else
	return (eax & 0xfffff100);
#endif
}
