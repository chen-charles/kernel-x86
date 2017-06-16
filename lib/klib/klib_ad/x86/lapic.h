#ifndef _KLIB_LAPIC_H
#define _KLIB_LAPIC_H

#include <klib_sl/type.h>
#include <klib_sl/c/klib_sl.h>
#include "instruction.h"

/* 
default mp lapic location
customized location must align at 4K boundary
*/
#define DEFAULT_LAPIC_LOC   0xfee00000


/* lapic relative locations */
#define APIC_APICID 0x20
#define APIC_APICVER    0x30
#define APIC_TASKPRIOR  0x80
#define APIC_EOI    0xB0
#define APIC_LDR    0xD0
#define APIC_DFR    0xE0
#define APIC_SPURIOUS   0xF0
#define APIC_ESR    0x280
#define APIC_ICRL   0x300
#define APIC_ICRH   0x310
#define APIC_LVT_TMR    0x320
#define APIC_LVT_PERF   0x340
#define APIC_LVT_LINT0  0x350
#define APIC_LVT_LINT1  0x360
#define APIC_LVT_ERR    0x370
#define APIC_TMRINITCNT 0x380
#define APIC_TMRCURRCNT 0x390
#define APIC_TMRDIV 0x3E0
#define APIC_LAST   0x38F
#define APIC_DISABLE    0x10000
#define APIC_SW_ENABLE  0x100
#define APIC_CPUFOCUS   0x200
#define APIC_NMI    (4<<8)
#define TMR_PERIODIC    0x20000
#define TMR_BASEDIV (1<<20)


/* MSR set/get lapic base */
void cpuSetLAPICBase(uintptr_t lapic);
uintptr_t cpuGetLAPICBase();

void enableLAPIC();

//PARSE MADT
typedef struct
{
	char Signature[4];
	uint32_t Length;
	uint8_t Revision;
	uint8_t Checksum;
	char OEMID[6];
	char OEMTableID[8];
	uint32_t OEMRevision;
	uint32_t CreatorID;
	uint32_t CreatorRevision;
	
	uint32_t LC_addr;
	uint32_t flags;

}MADT;

typedef struct
{
	byte PID;
	byte APICID;
	uint32_t Flags;
}ProcessorLAPIC;


#endif
