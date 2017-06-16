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

#include    "libmalloc.h"

/*
libmalloc
Malloc_Ctx Memory Usage Layout

SECTION BEGIN 

======  0
Malloc_Ctx 
======  
Virtural Memory Availibility Table @ 1
======  
TODO: Recursively build @ deg inc sizeof(uintreg_t)*8

*/

bool isMallocPage(uintptr_t pVirtAddr, Malloc_Ctx* ctx);
bool flipMallocPage(uintptr_t pVirtAddr, Malloc_Ctx* ctx);

//at least ONE entry MUST present
typedef struct
{
	size_t  size;	//including entry size
	
	uint32_t    properties;	//bit 0: isInUse?
	#define	MALLOC_ENTRY_FREE	0b00000000
	#define	MALLOC_ENTRY_INUSE	0b00000001
    #define isEntryFree(pEntry) (!TESTBIT((pEntry->properties), 0))
	
	//data followed by this
}
malloc_entry_h;

#define MIN_INITIAL_MALLOC_BUFFER_SIZE  4096    // bytes
Malloc_Ctx* Malloc_init(size_t szPage, size_t nSystemTotalPages)
{
    int nBytesRequired = sizeof(Malloc_Ctx) + sizeof(malloc_entry_h) + (1 + (nSystemTotalPages - 1) / (8*sizeof(uintreg_t))) * sizeof(uintreg_t) + MIN_INITIAL_MALLOC_BUFFER_SIZE;
    
    page_property prop;
    prop.required.present = true;
    prop.required.read = true;
    prop.required.write = true;
    prop.required.run = false;
    prop.required.priviliged = false;
    prop.required.inuse = true;
    uintptr_t pbuf = (uintptr_t)mmap((void*)0, nBytesRequired, &prop);

    Malloc_Ctx* ctx = (Malloc_Ctx*)pbuf;
    pbuf += sizeof(Malloc_Ctx);

    ctx->magic = 0x024D4D03;
    ctx->szPage = szPage;
    ctx->nSystemTotalPages = nSystemTotalPages;
    ctx->pVMemAvl = pbuf;

    memset((void*)pbuf, 0, (1 + (nSystemTotalPages - 1) / (8*sizeof(uintreg_t))) * sizeof(uintreg_t));
    pbuf += (1 + (nSystemTotalPages - 1) / (8*sizeof(uintreg_t))) * sizeof(uintreg_t);

    flipMallocPage((uintptr_t)ctx, ctx);

    malloc_entry_h* pEntry = (malloc_entry_h*)pbuf;
    pEntry->size = szPage - (pbuf - (uintptr_t)ctx);
    pEntry->properties = MALLOC_ENTRY_FREE;

    ctx->pMallocBuf = pbuf;
    ctx->nEntries = 1;
    ctx->nMaxAvlBytes = pEntry->size - sizeof(malloc_entry_h);

    return ctx;
}

bool isMallocPage(uintptr_t pVirtAddr, Malloc_Ctx* ctx)
{
    uintreg_t* pPMA = (uintreg_t*)(ctx->pVMemAvl);
    uintreg_t pgIndx = pVirtAddr/(ctx->szPage);
    uintreg_t pgtbIndx = pgIndx/(8*sizeof(uintreg_t));

    return TESTBIT(*(pPMA+pgtbIndx), pgIndx%(8*sizeof(uintreg_t)));
}

bool flipMallocPage(uintptr_t pVirtAddr, Malloc_Ctx* ctx)
{
    uintreg_t* pPMA = (uintreg_t*)(ctx->pVMemAvl);
    uintreg_t pgIndx = pVirtAddr/(ctx->szPage);
    uintreg_t pgtbIndx = pgIndx/(8*sizeof(uintreg_t));

    flipbit(pPMA+pgtbIndx, pgIndx%(8*sizeof(uintreg_t)));
    return TESTBIT(*(pPMA+pgtbIndx), pgIndx%(8*sizeof(uintreg_t)));
}

Malloc_Ctx* nextMallocPage(Malloc_Ctx* ctx, uintptr_t beginAddr)
{
    uintreg_t* pPMA = (uintreg_t*)(ctx->pVMemAvl);
    uintreg_t pgtbIndx;

    for(int i=beginAddr/(ctx->szPage); i<ctx->nSystemTotalPages; i++)
    {
        pgtbIndx = i/(8*sizeof(uintreg_t));
        if (TESTBIT(*(pPMA+pgtbIndx), i%(8*sizeof(uintreg_t))))
        {
            return (Malloc_Ctx*) (i*(ctx->szPage));
        }
    }

    return (Malloc_Ctx*)-1;
}

Malloc_Ctx* newMallocPage(size_t nPages, Malloc_Ctx* ctx)
{
    page_property prop;
    prop.required.present = true;
    prop.required.read = true;
    prop.required.write = true;
    prop.required.run = false;
    prop.required.priviliged = false;
    prop.required.inuse = true;
    
    Malloc_Ctx* newCtx = (Malloc_Ctx*) mmap((void*)0, nPages*ctx->szPage, &prop);
    memcpy((void*)newCtx, (void*)ctx, sizeof(Malloc_Ctx));
    newCtx->nMaxAvlBytes = nPages*ctx->szPage - sizeof(Malloc_Ctx) - sizeof(malloc_entry_h);
    newCtx->nEntries = 1;
    newCtx->pMallocBuf = ((uintptr_t)newCtx) + sizeof(Malloc_Ctx);
    malloc_entry_h* pEntry = (malloc_entry_h*) newCtx->pMallocBuf;
    pEntry->size = newCtx->nMaxAvlBytes + sizeof(malloc_entry_h);
    pEntry->properties = MALLOC_ENTRY_FREE;
    flipMallocPage((uintptr_t)newCtx, ctx);
    return newCtx;
}

void* MM_malloc(size_t size, Malloc_Ctx* ctx)
{
    if (size == 0) return (void*)0;

    uintptr_t beginAddr = 0;
    while (true)
    {
        Malloc_Ctx* curCtx = nextMallocPage(ctx, beginAddr);
        if (curCtx == (Malloc_Ctx*)-1)  //after scanning, no suitable page is available
        {
            int nPages = (size + sizeof(malloc_entry_h) + sizeof(Malloc_Ctx)) / ctx->szPage;
            curCtx = newMallocPage(nPages, ctx);  //allocate new chunk for this malloc
        }

        if (size > curCtx->nMaxAvlBytes)
        {
            // this page is not possible
            beginAddr = (uintptr_t)curCtx + ctx->szPage;    // find the next page
        }
        else
        {
            // this page might be suitable
            malloc_entry_h* pEntry = (malloc_entry_h*)(curCtx->pMallocBuf);

            for (int i=0; i<ctx->nEntries; i++)
            {
                if (!isEntryFree(pEntry))
                {
                    pEntry = (malloc_entry_h*) (((uintptr_t)pEntry) + pEntry->size);
                    continue;
                }

                
                // this is free
                // check if next chunk is free, do merge
                while ((i != ctx->nEntries-1) && (isEntryFree(((malloc_entry_h*) (((uintptr_t)pEntry) + pEntry->size)))))
                {
                    pEntry->size += ((malloc_entry_h*) (((uintptr_t)pEntry) + pEntry->size))->size;
                    ctx->nEntries --;
                }

                //pretend the malloc header is 5 bytes long
                //a request of 6 bytes would actually need 11 bytes in memory
                //thus, a spare memory of 10 bytes(+5 header) will not fit in a 6 bytes request
                
                //h h h h h x x x x x x x x x x
                //ONEONEONE DATAONEDATAONEDATAONE
                
                //h h h h h h h h h h x x x x x
                //ONEONEONE TWOTWOTWO DATATWODATA
                
                //in the real case, a 5 bytes request will return a 10(+5) bytes spare that is present
                //since the additional 5 bytes of a spare header would be wasted anyways
                
                //also, a 6 bytes request would return the 10(+5) bytes spare as well
                //otherwise, the memory table structure would be broken

                // is enough now?
                if (pEntry->size - sizeof(malloc_entry_h) >= size)
                {
                    // new entry needed?
                    if (pEntry->size - sizeof(malloc_entry_h) - size > sizeof(malloc_entry_h))
                    {
                        size_t orisize = pEntry->size;
                        pEntry->size = sizeof(malloc_entry_h) + size;
                        setbit(&(pEntry->properties), 0);	//in use now
                        

                        malloc_entry_h* nextEntry = (malloc_entry_h*) ((uintptr_t)pEntry + pEntry->size);
                        nextEntry->size = orisize - pEntry->size;	//left over size
                        nextEntry->properties = MALLOC_ENTRY_FREE;
                        ctx->nEntries++;
                                            
                        return (void*)(((uintptr_t)pEntry) + sizeof(malloc_entry_h));
                    }
                    else
                    {
                        setbit(&(pEntry->properties), 0);	//in use now
                        return (void*)(((uintptr_t)pEntry) + sizeof(malloc_entry_h));
                    }
                }
                else
                {
                    // not enough
                    // go find next entry
                    pEntry = (malloc_entry_h*) (((uintptr_t)pEntry) + pEntry->size);
                }
            }
            // failed to find any chunk for this malloc, search next
            beginAddr = (uintptr_t)curCtx + ctx->szPage;    // find the next page
        }
    }
}

void MM_free(void* ptr)
{
    malloc_entry_h* pEntry = (malloc_entry_h*) (((uintptr_t)ptr) - sizeof(malloc_entry_h));
    pEntry->properties = MALLOC_ENTRY_FREE;
}
