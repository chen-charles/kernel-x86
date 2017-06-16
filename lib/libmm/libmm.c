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

======  0
MM_Data_Section_H 
======  
Physical Memory Availibility Table @ 1
======  
TODO: Recursively build @ deg inc sizeof(uintreg_t)*8

*/

/* physical page availibility */
bool isPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec);
#define isPhysicalPageAvailiable(pPhysAddr, pMMDatSec) isPhyPGAvl(pPhysAddr, (MM_Data_Section_H*)pMMDatSec)
bool flipPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec);


#ifndef _libmm_test_
uintptr_t MM_init(size_t nTotalPages, size_t szPage, size_t nInusePages, uintptr_t* pInusePages)
#define MM_REQUIRED_DATA_SECTION_SIZE   0x400000    /* 4m */
#else
uintptr_t MM_init(size_t nTotalPages, size_t szPage, size_t nInusePages, uintptr_t* pInusePages, uintptr_t mbase)
#define MM_REQUIRED_DATA_SECTION_SIZE   0x4000    /* 16k */
#endif
{
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
        if (!pg_prop.required.inuse)
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
    pg_prop.required.run = false;
    pg_prop.required.priviliged = true;
    pg_prop.required.inuse = true;

    for(int i=searchI; i<searchI+curPages; i++)
    {
        /* Fatal: mapping failed */
        if (!write_page(szPage * i, szPage * i, &pg_prop)) return -1;
        flush_page(szPage * i);
    }

    /* buffer space allocated, ready for initialization */

#ifndef _libmm_test_
    uintptr_t pbuf = searchI*szPage;
#else
    uintptr_t pbuf = mbase + searchI*szPage;
#endif

    MM_Data_Section_H* dath = (MM_Data_Section_H*)(pbuf);
    pbuf += sizeof(MM_Data_Section_H);

    memset((void*)dath, 0, sizeof(uintreg_t));
    dath->magic += 0x024D4D03;  //begin, M, M, end
    dath->szDataSec = MM_REQUIRED_DATA_SECTION_SIZE;
    dath->nTotalPages = nTotalPages;
    dath->szPage = szPage;

    dath->nPages = nTotalPages;

    // physical memory availibility
    dath->pPMemAvl = pbuf;
    memset((void*)pbuf, 0, (1 + (dath->nPages - 1) / (8*sizeof(uintreg_t))) * sizeof(uintreg_t));
    pbuf += (1 + (dath->nPages - 1) / (8*sizeof(uintreg_t))) * sizeof(uintreg_t);
    // accessor isPhyPGAvl
    // flip-er  flipPhyPGAvl

    for(int i=searchI; i<searchI+curPages; i++)
        flipPhyPGAvl(szPage * i, dath); // allocated buffer page inuse
    
    for(int i=0; i<nInusePages; i++)
        flipPhyPGAvl(((*(pInusePages+i)) & (uintptr_t)(-0x10)), dath);
    
    // TODO: add more layers to this structure
    return (uintptr_t)dath;
}

bool isPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec)
{
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    uintreg_t pgIndx = pPhysAddr/(pMMDatSec->szPage);
    uintreg_t pgtbIndx = pgIndx/(8*sizeof(uintreg_t));

    return TESTBIT(*(pPMA+pgtbIndx), pgIndx%(8*sizeof(uintreg_t)));
}
#define isPhysicalPageAvailiable(pPhysAddr, pMMDatSec) isPhyPGAvl(pPhysAddr, (MM_Data_Section_H*)pMMDatSec)

bool flipPhyPGAvl(uintptr_t pPhysAddr, MM_Data_Section_H* pMMDatSec)
{
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    uintreg_t pgIndx = pPhysAddr/(pMMDatSec->szPage);
    uintreg_t pgtbIndx = pgIndx/(8*sizeof(uintreg_t));

    flipbit(pPMA+pgtbIndx, pgIndx%(8*sizeof(uintreg_t)));
    return TESTBIT(*(pPMA+pgtbIndx), pgIndx%(8*sizeof(uintreg_t)));
}

PHYSICAL_ADDRESS nextFreePhysicalPage(MM_Data_Section_H* pMMDatSec)
{
    uintreg_t* pPMA = (uintreg_t*)(pMMDatSec->pPMemAvl);
    
    for(int i=0; i<(pMMDatSec->nPages) / (8*sizeof(uintreg_t)); i++)
        // reserve the last a few leftover pages
    {
        if (*(pPMA+i) != (uintreg_t)(-1))
        {
            for(int j=0; j<8*sizeof(uintreg_t); j++)
            {
                if (!TESTBIT(*(pPMA+i), j))
                {
                    return (pMMDatSec->szPage) * ((i * sizeof(uintreg_t) * 8) + j);
                }
            }
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


#ifdef USING_LOOKUP
    page_property property;
    property.required.inuse = false;
    for(VIRTUAL_ADDRESS i=virt_begin; i<=virt_end; i+=(pMMDatSec->szPage))
    {
        PHYSICAL_ADDRESS phys;
        phys = lookup_virt_to_phys(i);
        flipPhyPGAvl(phys, pMMDatSec);
        write_page(phys, phys, &property);
        flush_page(phys);
    }
#else
    // it should be fairly straight forward to implement a O(1) algorithm for this
    for(uintptr_t paddr=0; paddr<pMMDatSec->szPage * pMMDatSec->nPages; paddr+=pMMDatSec->szPage)
    {
        page_property property;
        VIRTUAL_ADDRESS cur = read_page(paddr, &property);
        if (!cur) continue;
        // for thread safety and multiple-mmap-one-munmap, allow mmap in random order
        for(VIRTUAL_ADDRESS i=virt_begin; i<=virt_end; i+=(pMMDatSec->szPage))
        {
            if (cur == i)
            {
                property.required.inuse = false;
                flipPhyPGAvl(paddr, pMMDatSec);
                write_page(paddr, paddr, &property);
                flush_page(paddr);
            }
        }
    }
#endif

    return 0;
}
