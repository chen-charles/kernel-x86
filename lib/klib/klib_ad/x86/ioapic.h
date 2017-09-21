#ifndef _KLIB_IOAPIC_H
#define _KLIB_IOAPIC_H

#include <klib_sl/type.h>
#include <klib_sl/c/klib_sl.h>

/* 
default mp ioapic location
customized location must align at 1K boundary
2nd IOAPIC if exist is located at 1K increment
*/
#define DEFAULT_IOAPIC_LOC   0xfec00000
#define IOAPIC_AT(base, index) (base + index*0x1000)
#define DEFAULT_IOAPIC_AT(index)    (IOAPIC_AT(DEFAULT_IOAPIC_LOC, index))
#define IOREDTBL(x) (0x10+x*2)

void write_ioapic_register(const uintptr_t apic_base, const uint8_t offset, const uint32_t val);
uint32_t read_ioapic_register(const uintptr_t apic_base, const uint8_t offset);

#endif
