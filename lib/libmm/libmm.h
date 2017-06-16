/*
library Memory Management --- connecting hardware mmu with kernel level memory management
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

/*
library Memory Management
HAL Core Component

libmm connects hardware mmu with kernel level memory management
libmm requires a "description" of the low level paging mechanics to provide direct memory mapping
libmm provides the mmap/munmap interface
*/

#ifndef LIB_MM
#define LIB_MM

#define USING_LOOKUP

#include "type.h"
#include "bit_op.h"

EXTERN_C

#ifndef uintreg_t
typedef uintptr_t uintreg_t;
#endif

#ifndef IMMEDIATE_SETBIT
#define IMMEDIATE_SETBIT(pos) (1<<pos)
#endif

#ifndef memset
void* memset(void* ptr, int value, size_t num);
#endif

/*
libmm requires access to physical memory below the HAL

A return value of -1 indicates a failure or unimplemented error, libmm should cleanup all used resources, and then fail all requests to libmm with ERR: LIBMM_INTERFACE_FAILURE

either way, libmm requires the following interface to be implemented,
*/

/* BEGIN REQUIRED INTERFACE */

/* types and consts */

/*
page is either inuse or not inuse
other situations should be marked with usage and pageStart
such as STUCK, FORCE_MAPPED
min page size is 16 bytes (unlikely small)

entry: pageStart + specialusage
*/
#define pageUsage_FORCE_MAPPED 1;
#define pageUsage_STUCK 2;

/*
Paging below HAL
*/
typedef uintptr_t PHYSICAL_ADDRESS;
typedef uintptr_t VIRTUAL_ADDRESS;
typedef uintptr_t MAPPED_VIRTUAL_ADDRESS;

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

/*
if page is not present, return value MUST be ZERO. 
*/
VIRTUAL_ADDRESS read_page(PHYSICAL_ADDRESS from, page_property* properties);
VIRTUAL_ADDRESS write_page(PHYSICAL_ADDRESS from, VIRTUAL_ADDRESS to, page_property* properties);
void flush_page(PHYSICAL_ADDRESS from);

/*
optional lookup requisites
#define USING_LOOKUP 
*/
#ifdef USING_LOOKUP
VIRTUAL_ADDRESS lookup_phys_to_virt(PHYSICAL_ADDRESS phys);
PHYSICAL_ADDRESS lookup_virt_to_phys(VIRTUAL_ADDRESS virt);
#else
#warning "USING_LOOKUP is not defined, munmap is working in low efficiency mode"
#endif

/* END REQUIRED INTERFACE */


/* BEGIN INITIALIZATION */

typedef struct _mm_data_section_h
{
    uintreg_t   magic;  // 0x024D4D03;  begin, M, M, end
    size_t  szDataSec;
    size_t  nTotalPages;
    size_t  szPage;
    size_t  nPages;
    uintptr_t   pPMemAvl;
}
MM_Data_Section_H;

/*
libmm requires this function to be called before any libmm functionality is used
paging must be enabled at the moment of this function being called
paging must be in a phys<->virt relationship
this function can only be called once

supplied special usage table MUST be sorted at this moment
*/

#ifndef _libmm_test_
uintptr_t MM_init(size_t nTotalPages, size_t szPage, size_t nInusePages, uintptr_t* pInusePages);
#else
uintptr_t MM_init(size_t nTotalPages, size_t szPage, size_t nInusePages, uintptr_t* pInusePages, uintptr_t mbase);
#endif

/* END INITIALIZATION */


/*
libmm public interface

libmm should support mmap/munmap and a public mapping interface for unpreventable memory usages at specific memory locations (typically hardware)
*/

/* BEGIN PUBLIC INTERFACE */

/*
kernel internal protected memory mapping
phys->virt, managed mapping
no security checks

map any free page into the given virtual address, decalre usage for page usage
note: this only modifies the inuse field, instead of the present field
*/
void *MM_mmap(void* addr, size_t len, page_property* usage, MM_Data_Section_H* pMMDatSec);
int MM_munmap(void* addr, size_t len, MM_Data_Section_H* pMMDatSec);


/* MM_force_map only works with libproc compatable interface */
/* function signature is not stable */
#ifdef USING_LIB_PROC
/*
MM_force_map will force a connection between the given physical address and the given virtual_address. 
It is extremely unsafe to use MM_force_map after the scheduler is set up, since context-switch will not cancel this mapping. 
A call with a pageUsage_FORCE_MAPPED marked page will do nothing and fail due to stability. 
Do NOT attempt to use this function anytime after the scheduler is set up, unless you understand,
    the physical page will be marked as pageUsage_FORCE_MAPPED (unusable)
    the virtual page will be marked as pageUsage_FORCE_MAPPED (unusable)
    the virtual page (which points to the physical page) will be accessible by ALL processes until a MM_force_unmap is called
    processes which marked this physical page as INUSE before the mapping will copy this page to another physical page and re-link with the original virtual page
    processes which marked this virtual page as INUSE before the mapping will not be scheduled until a MM_force_unmap is called (as mapping will not work)

MM_force_unmap will do nothing and fail if the parameters are not matched up with any of the previous calls to MM_force_map
*/
uintreg_t MM_force_map(PHYSICAL_ADDRESS phys, VIRTUAL_ADDRESS virt);
uintreg_t MM_force_unmap(PHYSICAL_ADDRESS phys, VIRTUAL_ADDRESS virt);
#else
#warning "USING_LIB_PROC is not defined, force map & force_unmap will not be available"
#endif

/* END PUBLIC INTERFACE*/

EXTERN_C_END

#endif
