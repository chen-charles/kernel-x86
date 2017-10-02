
#ifndef INIT_MEMLOC
#define INIT_MEMLOC

#include    <klib_sl/c/klib_sl.h>

EXTERN_C

#define GetValAt(typ, mloc) (*((typ*)mloc))
#define GetPtrValAt(mloc) GetValAt(uintptr_t, mloc)
#define GetTypedPtrAt(typ, mloc) (typ*)GetPtrValAt(mloc)

#define PAGESIZE	0x400000

/*
http://wiki.osdev.org/Memory_Map_(x86)


Overview
start	end	size	type	description
Low Memory (the first MiB)
0x00000000	0x000003FF	1 KiB	RAM - partially unusable (see above)	Real Mode IVT (Interrupt Vector Table)
0x00000400	0x000004FF	256 bytes	RAM - partially unusable (see above)	BDA (BIOS data area)
0x00000500	0x00007BFF	almost 30 KiB	RAM (guaranteed free for use)	Conventional memory
0x00007C00 (typical location)	0x00007DFF	512 bytes	RAM - partially unusable (see above)	Your OS BootSector
0x00007E00	0x0007FFFF	480.5 KiB	RAM (guaranteed free for use)	Conventional memory
0x00080000	0x0009FBFF	approximately 120 KiB, depending on EBDA size	RAM (free for use, if it exists)	Conventional memory
0x0009FC00 (typical location)	0x0009FFFF	1 KiB	RAM (unusable)	EBDA (Extended BIOS Data Area)
0x000A0000	0x000FFFFF	384 KiB	various (unusable)	Video memory, ROM Area


"Upper" Memory (> 1 MiB)
start	end	size	region/exception	description
High Memory
0x00100000	0x00EFFFFF	0x00E00000 (14 MiB)	RAM -- free for use (if it exists)	Extended memory 1, 2
0x00F00000	0x00FFFFFF	0x00100000 (1 MiB)	Possible memory mapped hardware	ISA Memory Hole 15-16MB 3
0x01000000	 ????????	 ???????? (whatever exists)	RAM -- free for use	More Extended memory 1
0xC0000000 (sometimes, depends on motherboard and devices)	0xFFFFFFFF	0x40000000 (1 GiB)	various (typically reserved for memory mapped devices)	Memory mapped PCI devices, PnP NVRAM?, IO APIC/s, local APIC/s, BIOS, ...
0x0000000100000000 (possible memory above 4 GiB)	 ????????????????	 ???????????????? (whatever exists)	RAM -- free for use (PAE/64bit)	More Extended memory 1
 ????????????????	 ????????????????	 ????????????????	Possible memory mapped hardware	Potentially usable for memory mapped PCI devices in modern hardware (but typically not, due to backward compatibility)
*/

/*
Memory Layout

PINNED
0x00000000	0x00001000	RealModeIVT BiosDataArea GDTR(0x6) IDTR(0x6) 
	BIOS	0x0000	0x0500	Required to Preserve
	GDTD	0x0500	0x05E0
	GDTR	0x05E0	0x05F0
	IDTR	0x05F0	0x0600
	TSSD	0x0600	0x0668	(only exists on INTEL86; AMD64 does not support hardware context switch)
	INTM	0x0680	0x06A0	Interrupt Masks (256 bits)
	CUST	0x06A0	0x0700	Custom Data
	PtrS	0x0700	0x1000	PtrSpace (allocate only with size 32bit/64bit, 4bytes/8bytes)	Capacity=576/1152

0x00001000	0x00002000	IDTDesc256x INTEL86=0x8/entry(0x800) AMD64=0x10/entry(0x1000)
0x00002000	0x00003000	Custom Interrupt Handler Table


0x00100000	Kernel ELF .text location
this address is always sync-ed with ld -Ttext X
The following information must be present ALL TIME in memory (accessible by priv-rings), 
	1. GDT(R), IDT(R), PagingData
	2. Interrupt handlers and subroutines
	3. Global Memory Manager routines and data
	4. Process Scheduler routines and data
	5. Hardware reserved (APIC EOI memory, etc.)
When kernel sets up the runtime environment for the first time, 
	1. GDT(R), IDT(R) are stored within first 0x10000
	2. Routines and libs are loaded within kernel [.text]
	3. Paging data must be placed at a location outside kernel

*/

// Global Shared Data Section	0x0000	0x1000
// Requires Initialization: memset((void*)0x500, 0, 0x1000-0x500);
#define SHARED_GDTD	0x00000500	// 28 max. (normally 16 is sufficient)
#define SHARED_GDTR	0x000005E0
#define SHARED_IDTR 0x000005F0
#define SHARED_TSSD	0x00000600	// sizeof(TSS) == 0x68
#define SHARED_INTM	0x00000680	// 256-bit interrupt masks -> 0x20
	#define InterruptMasked(id) TESTBIT(*(uint8_t*)(SHARED_INTM + id/8), id%8)
	#define MaskInterrupt(id) setbit((uint8_t*)(SHARED_INTM + id/8), id%8)
	#define UnMaskInterrupt(id) clearbit((uint8_t*)(SHARED_INTM + id/8), id%8)
#define SHARED_DATA	0x000006A0
	#define SHARED_TIME	(SHARED_DATA)	// uint64_t
	#define GetSystemInternalTime()	GetValAt(uint64_t, SHARED_TIME)
	#define TickSystemInternalTime()	(GetValAt(uint64_t, SHARED_TIME)++)

	// #define SHARED_PNXT	(SHARED_DATA + 8)	// next pointer in shared pointers
	// #define offsetSharedPtr()	GetValAt(uint16_t, SHARED_PNXT)
	// #define nextSharedPtr()	((SHARED_PTRS + sizeof(uintptr_t)*offsetSharedPtr() >= 0x1000) ? (__asm__ volatile ("int 3")) : (SHARED_PTRS + sizeof(uintptr_t)*(GetValAt(uint16_t, SHARED_PNXT)++)))
#define SHARED_PTRS	0x00000700
	#define LIBMM_DATSEC_PTR	(SHARED_PTRS)
	#define PREFERRED_MMAP_CTR_PTR	(SHARED_PTRS+4)
	#define LIBMALLOC_CTX_PTR	(SHARED_PTRS+8)
	#define LIBPROC_SCHEDULER_PTR	(SHARED_PTRS+12)

// Global Tables
#define pGDTable	0x00000500
#define pTSSegment	0x00000600
#define pIDTable	0x00001000
#define pIHTable	0x00002000

#define PM_PAGING_4MB_VIRTPHYS_DATA	0x00010000	//len=0x4000, ends at 0x14000
#define PM_PAGING_4KB_VIRTPHYS_DATA 0x10000000

EXTERN_C_END

#endif
