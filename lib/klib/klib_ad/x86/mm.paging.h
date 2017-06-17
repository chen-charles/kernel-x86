// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_MM_PAGING_H_
#define _KLIB_MM_PAGING_H_

#include <klib_sl/type.h>
#include <klib_sl/c/klib_sl.h>
#include "instruction.h"

EXTERN_C

void flush_cache();

enum PagingMode {BIT32, PAE, IA32E};


// phyaddr=linaddr

/* 
Mode 32-bit Paging
set CR0:PG

note szPage is either 0x400000 or 0x4000
*/
uintreg_t init_paging_32bit(const uint32_t szPage, memblock aligned_buf);

/* 
Mode PAE
set CR0:PG
set CR4:PAE

*/

/* 
Mode IA-32e
set CR4:PAE
set IA32_EFER:LME
set CR0:PG

*/

EXTERN_C_END

#endif
