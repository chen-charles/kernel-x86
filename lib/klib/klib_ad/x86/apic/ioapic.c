
#include	"ioapic.h"

void write_ioapic_register(const uintptr_t apic_base, const uint8_t offset, const uint32_t val)
{
	/* tell IOREGSEL where we want to write to */
	*(uint32_t*)(apic_base) = offset;
	/* write the value to IOWIN */
	*(uint32_t*)(apic_base + 0x10) = val;
}

uint32_t read_ioapic_register(const uintptr_t apic_base, const uint8_t offset)
{
	/* tell IOREGSEL where we want to read from */
	*(uint32_t*)(apic_base) = offset;
	/* return the data from IOWIN */
	return *(uint32_t*)(apic_base + 0x10);
}

