
#ifndef INIT_MEMLOC
#define INIT_MEMLOC


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


#define PM_GDT_PTR	0x00000500	//160 entries max
#define PM_IDT_PTR	0x00001000	//256 entries max	//ends at 0x0000c100
#define PM_TSS_PTR	0x0000c100	//104 bytes	//ends at 0x0000c168
							    //align to 0x0000c200

#define LIBMM_DATSEC_PTR	0x0000c200	//uintptr_t
#define PREFERRED_MMAP_CTR_PTR	0x0000c204	//uintreg_t
#define LIBMALLOC_CTX_PTR	0x0000c208	//uintptr_t
// c20c
#define	SYSTEM_INTERNAL_TIME_PTR	0x0000c210	//uint64_t

#define LIBPROC_SCHEDULER_PTR	0x0000c218

#define PM_INT_REDIRECT_TABLE_PTR 0x0000e000    //256 entries(uint32_t) ends at 0x0000e400

#define PM_PAGING_4MB_VIRTPHYS_DATA	0x00010000	//len=0x4000, ends at 0x14000
#define PM_PAGING_4MB_PHYSVIRT_DATA 0x00020000	//len=0x4000, ends at 0x18000

#endif
