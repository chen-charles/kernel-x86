/*
library Malloc --- malloc drop-in implementation
Copyright (C) 2016  Jianye Chen
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIB_MALLOC
#define LIB_MALLOC

#include    "type.h"
#include    "bit_op.h"

#ifndef uintreg_t
typedef uintptr_t uintreg_t;
#endif

#ifndef IMMEDIATE_SETBIT
#define IMMEDIATE_SETBIT(pos) (1<<pos)
#endif

#ifndef memset
void* memset(void* ptr, int value, size_t num);
#endif
#ifndef memcpy
void* memcpy(void* destination, const void* source, size_t num);
#endif

/* BEGIN REQUIRED INTERFACE */

/* types and consts */

#ifndef page_property
/*
not recommended for modification
*/
typedef struct _pg_prop_req
{
    bool present;   // true iff physically mapped 
    bool read;
    bool write;
    bool run;
    bool priviliged;
    bool inuse;     // MM_mmap and MM_munmap operate on; if not needed, sync to present 
} 
page_property_required;

/*
add fields here for additional flags in the (custom) paging structure
*/
typedef struct _pg_prop  
{
    page_property_required required;
}
page_property; 
#endif

void *mmap(void* addr, size_t len, page_property* usage);
int munmap(void* addr, size_t len);

/* END REQUIRED INTERFACE */


/* BEGIN INITIALIZATION */

typedef struct _malloc_ctx
{
    uint32_t   magic;  // 0x024D4D03;  begin, M, M, end
    size_t  szPage;
    size_t  nSystemTotalPages;    // total
    size_t  nMaxAvlBytes;   // max possible size = szPage*nPagesAllocated-sizeof(ctx)-sizeof(malloc_entry_h)
    size_t  nEntries;
    uintptr_t   pVMemAvl;   // malloc-tagged pages
    uintptr_t   pMallocBuf; // points to the starting location of this buffer section
}
Malloc_Ctx;

/*
libmalloc requires this function to be called before any libmalloc functionality is used
*/

Malloc_Ctx* Malloc_init(size_t szPage, size_t nSystemTotalPages);

/* END INITIALIZATION */

/* BEGIN PUBLIC INTERFACE */

void* MM_malloc(size_t size, Malloc_Ctx* ctx);
void MM_free(void* ptr);

/* END PUBLIC INTERFACE*/

#endif
