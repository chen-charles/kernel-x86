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

#include    "libmm.h"
/*
libmm
MM Data Section Memory Usage Layout

SECTION BEGIN 

size=szMem/szPage*sizeof(uintptr_t) + sizeof(MM_Data_Section_H)
======  0
MM_Data_Section_H 
======  
phys<->virt Lookup Table @ 32/64 bit
lets' say you have 64 GB memory and each page has a page size 0x1000
this requires 80 MB (64bits/page) global memory for physical<->lookup
this does not seem too bad considering this a global lookup for munmap efficiency
the memory space should always contain a continuous block that is large enough (% in szMem)
63/31:12    0x1000 aligned mapped address
11:-        reserved
5           (B) Busy
4           (S) Supervisor
3           (X) Execute
2           (W) Write
1           (R) Read
0           (P) Present
======  
TODO: Recursively build @ deg inc sizeof(uintreg_t)*8

*/

/* physical page availibility */
bool isPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec);
#define isPhysicalPageAvailiable(pPhysAddr, pMMDatSec) isPhyPGAvl(pPhysAddr, (MM_Data_Section_H*)pMMDatSec)
bool flipPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec);

void encode(uintptr_t* pEntry, page_property* prop)
{
    if (prop->required.present) setbit(pEntry, 0);
    else clearbit(pEntry, 0);
    if (prop->required.read) setbit(pEntry, 1);
    else clearbit(pEntry, 1);
    if (prop->required.write) setbit(pEntry, 2);
    else clearbit(pEntry, 2);
    if (prop->required.execute) setbit(pEntry, 3);
    else clearbit(pEntry, 3);
    if (prop->required.privileged) setbit(pEntry, 4);
    else clearbit(pEntry, 4);
    if (prop->required.busy) setbit(pEntry, 5);
    else clearbit(pEntry, 5);
}

void sync(PHYSICAL_ADDRESS phys, VIRTUAL_ADDRESS virt, page_property* prop, MM_Data_Section_H* pMMDatSec)
{
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    uintreg_t pgIndx = phys/(pMMDatSec->szPage);
    *(pPMA+pgIndx) = virt - virt%(pMMDatSec->szPage);
    encode(pPMA+pgIndx, prop);
}

#ifndef _libmm_test_
uintptr_t MM_init(size_t nTotalPages, size_t szPage, size_t nInusePages, uintptr_t* pInusePages)
#else
uintptr_t MM_init(size_t nTotalPages, size_t szPage, size_t nInusePages, uintptr_t* pInusePages, uintptr_t mbase)
#endif
{
    int szMem = nTotalPages * szPage;
    int MM_REQUIRED_DATA_SECTION_SIZE = szMem/szPage*sizeof(uintptr_t) + sizeof(MM_Data_Section_H);
    int totalPages = nTotalPages;

    // Required # of pages to be mapped
    int nPages = MM_REQUIRED_DATA_SECTION_SIZE/szPage
                + (MM_REQUIRED_DATA_SECTION_SIZE%szPage ? 1 : 0);
    
    page_property pg_prop;
    
    // Scan for a continuous block of size MM_REQUIRED_DATA_SECTION_SIZE
    // must check whether or not the page is inuse
    int curSearchInusePageIndx = 0;
    int searchI=0, curPages=0;
    for(int i=0; i<totalPages; i++)
    {
        if (curSearchInusePageIndx < nInusePages)
        {
            if (szPage * i == ((*(pInusePages + curSearchInusePageIndx)) & (uintptr_t)(-0x10)))
            {
                curSearchInusePageIndx ++;
                searchI=0; curPages=0;
                continue;
            }
            while (szPage * i > ((*(pInusePages + curSearchInusePageIndx)) & (uintptr_t)(-0x10))
                && curSearchInusePageIndx < nInusePages) curSearchInusePageIndx++;
        }
        
        read_page(szPage * i, &pg_prop);
        if (!pg_prop.required.busy)
        {
            if (curPages++ == 0) searchI = i;
            if (curPages == nPages) break;
        }
        else
        {
            searchI=0; curPages=0;
        }
    }
    
    /* Fatal: cannot find a continuous block */
    if (curPages != nPages) return -1;

    pg_prop.required.present = true;
    pg_prop.required.read = true;
    pg_prop.required.write = true;
    pg_prop.required.execute = false;
    pg_prop.required.privileged = true;
    pg_prop.required.busy = true;

    for(int i=searchI; i<searchI+curPages; i++)
    {
        /* Fatal: mapping failed */
        if (!write_page(szPage * i, szPage * i, &pg_prop)) return -1;
        flush_page(szPage * i);
    }

    /* buffer space allocated, ready for initialization */

#ifndef _libmm_test_
    uintptr_t pbuf = searchI * szPage;
#else
    uintptr_t pbuf = mbase + searchI * szPage;
#endif
    
    MM_Data_Section_H* dath = (MM_Data_Section_H*)(pbuf);
    pbuf += sizeof(MM_Data_Section_H);

    memset((void*)dath, 0, sizeof(uintreg_t));
    dath->magic += 0x024D4D03;  //begin, M, M, end
    dath->szDataSec = MM_REQUIRED_DATA_SECTION_SIZE;
    dath->nTotalPages = nTotalPages;
    dath->szPage = szPage;
    dath->nPages = nTotalPages;

    // physical memory table
    dath->pPMemAvl = pbuf;
    memset((void*)pbuf, 0, dath->nPages * sizeof(uintptr_t));
    pbuf += dath->nPages * sizeof(uintptr_t);
    // accessor isPhyPGAvl
    // flip-er  flipPhyPGAvl

    for(int i=searchI; i<searchI+curPages; i++)
        flipPhyPGAvl(szPage * i, dath); // allocated buffer page inuse
    
    for(int i=0; i<nInusePages; i++)
        flipPhyPGAvl(((*(pInusePages+i)) & (uintptr_t)(-0x10)), dath);
    
    // sync p<->v
    for(int i=0; i<nTotalPages; i++)
    {
        VIRTUAL_ADDRESS vaddr = read_page(i*(dath->szPage), &pg_prop);
        sync(i*(dath->szPage), vaddr, &pg_prop, dath);
    }

    // TODO: add more layers to this structure
    return (uintptr_t)dath;
}

bool isPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec)
{
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    uintreg_t pgIndx = pPhysAddr/(pMMDatSec->szPage);

    return TESTBIT(*(pPMA+pgIndx), 0);
}
#define isPhysicalPageAvailiable(pPhysAddr, pMMDatSec) isPhyPGAvl(pPhysAddr, (MM_Data_Section_H*)pMMDatSec)

bool flipPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec)
{
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    uintreg_t pgIndx = pPhysAddr/(pMMDatSec->szPage);

    flipbit(pPMA+pgIndx, 0);
    return TESTBIT(*(pPMA+pgIndx), 0);
}

PHYSICAL_ADDRESS nextFreePhysicalPage(MM_Data_Section_H* pMMDatSec)
{
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    
    for(int i=0; i<pMMDatSec->nPages; i++)
    {
        if (!TESTBIT(*(pPMA+i), 5)) // inuse-bit
        {
            return (pMMDatSec->szPage) * i;
        }
    }

    return -1;
}

// no double map check
void *MM_mmap(void* addr, size_t len, page_property* usage, MM_Data_Section_H* pMMDatSec)
{
    if (len == 0) return (void*)-1; // MAP_FAILED 

    // find page boundaries 
    VIRTUAL_ADDRESS virtPG_begin = ((uintptr_t)addr)/(pMMDatSec->szPage);
    VIRTUAL_ADDRESS virtPG_end = ((uintptr_t)addr + len)/(pMMDatSec->szPage); // take this end

    // map and return
    for(VIRTUAL_ADDRESS i=virtPG_begin; i<=virtPG_end; i+=pMMDatSec->szPage)
    {
        // scan for next non-special, unmapped page
        PHYSICAL_ADDRESS nextPG = nextFreePhysicalPage(pMMDatSec);
        if (nextPG == -1) return (void*)-1; //  no more available pages
        flipPhyPGAvl(nextPG, pMMDatSec);
        // map it
        write_page(nextPG, i*(pMMDatSec->szPage), usage);
        sync(nextPG, i*(pMMDatSec->szPage), usage, pMMDatSec);
        flush_page(nextPG);
    }

    return (void*)(virtPG_begin*(pMMDatSec->szPage));
}

// no security check
int MM_munmap(void* addr, size_t len, MM_Data_Section_H* pMMDatSec)
{
    // find page boundaries 
    VIRTUAL_ADDRESS virt_begin = ((uintptr_t)addr) - ((uintptr_t)addr)%(pMMDatSec->szPage);
    VIRTUAL_ADDRESS virt_end = ((uintptr_t)addr + len + pMMDatSec->szPage - 1)/(pMMDatSec->szPage)*(pMMDatSec->szPage); // take this end

    page_property property;
    property.required.busy = false;
    for(VIRTUAL_ADDRESS i=virt_begin; i<=virt_end; i+=(pMMDatSec->szPage))
    {
        PHYSICAL_ADDRESS phys;
        phys = lookup_virt_to_phys(i, pMMDatSec);
        flipPhyPGAvl(phys, pMMDatSec);
        write_page(phys, phys, &property);
        sync(phys, phys, &property, pMMDatSec);
        flush_page(phys);
    }

    return 0;
}

VIRTUAL_ADDRESS lookup_phys_to_virt(PHYSICAL_ADDRESS phys, MM_Data_Section_H* pMMDatSec)
{
    page_property prop;
#ifdef NATIVE_PHYS_TO_VIRT
    return read_page(phys, &prop);
#else
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    uintreg_t pgIndx = phys/(pMMDatSec->szPage);

    return *(pPMA+pgIndx) - *(pPMA+pgIndx) % (pMMDatSec->szPage);
#endif
}

PHYSICAL_ADDRESS lookup_virt_to_phys(VIRTUAL_ADDRESS virt, MM_Data_Section_H* pMMDatSec)
{
    page_property prop;
#ifdef NATIVE_PHYS_TO_VIRT
    #error not implemented
#else
    return read_page(virt, &prop);
#endif
}
