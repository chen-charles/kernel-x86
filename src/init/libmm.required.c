#include <klib_sl/type.h>
#include <klib_ad/x86/mm.paging.h>

#include <libmm/libmm.h>

#include "include/memloc.h"
#include "include/bochsdbg.h"

void *mmap(void* addr, size_t len, page_property* usage)
{
    page_property properties;
    uintreg_t* ct = (uintreg_t*)PREFERRED_MMAP_CTR_PTR;
    if (addr == 0)
    {
        addr = (void*)(0x30000000 + (*ct)*PAGESIZE);
        *ct = *ct + ((len+PAGESIZE-1)/PAGESIZE);
    }
    if (usage == 0)
    {
        properties.required.present = true;
        properties.required.read = true;
        properties.required.write = true;
        properties.required.execute = true;
        properties.required.privileged = true;
        properties.required.busy = true;
        usage = &properties;
    }
    return MM_mmap(addr, len, usage, GetTypedPtrAt(MM_Data_Section_H, LIBMM_DATSEC_PTR));
}

int munmap(void* addr, size_t len)
{
    return MM_munmap(addr, len, GetTypedPtrAt(MM_Data_Section_H, LIBMM_DATSEC_PTR));
}

uintreg_t libmm_init()
{
    memblock mem;
    mem.ptr = PM_PAGING_4MB_VIRTPHYS_DATA;
    mem.len = 0x4000;
    init_paging_32bit(PAGESIZE, mem);
    // mem.ptr = PM_PAGING_4KB_VIRTPHYS_DATA;
    // mem.len = 0x401000;
    // init_paging_32bit(0x4000, mem);

    uintptr_t inusePages[] = {0, 0x400000, 0x10000000, 0xfec00000};   // curPage, hardware page
    for (int i=0; i<1000; i++)
    {
        if (i*PAGESIZE == 0 || i*PAGESIZE == 0x400000 || i*PAGESIZE == 0x10000000)
        {
            setbit((((uint32_t*)PM_PAGING_4MB_VIRTPHYS_DATA)+i), 9);    // P + U
            continue;
        }
        // NP+NU
        clearbit((((uint32_t*)PM_PAGING_4MB_VIRTPHYS_DATA)+i), 0);
        clearbit((((uint32_t*)PM_PAGING_4MB_VIRTPHYS_DATA)+i), 9);
    }

    // memcpy((void*)PM_PAGING_4MB_PHYSVIRT_DATA, (void*)mem.ptr, mem.len);
    MM_Data_Section_H* pMMDatSec = (MM_Data_Section_H*)MM_init(1024/2, PAGESIZE, 4, inusePages);
    
    *(uintptr_t*)(LIBMM_DATSEC_PTR) = (uintptr_t)pMMDatSec;
    *(uintreg_t*)(PREFERRED_MMAP_CTR_PTR) = 0;
    
    // page_property properties;
    // properties.required.present = true;
    // properties.required.read = true;
    // properties.required.write = true;
    // properties.required.run = true;
    // properties.required.privileged = true;

    // uintptr_t* pp = (uintptr_t*)mmap(0x40000000, 0x400000, &properties);
    // *pp = 100;
    //return mmap(0, 0x400000, &properties);
    return LIBMM_DATSEC_PTR;
    // return lookup_virt_to_phys(0x40000000);

    // page_property properties;
    // properties.required.present = true;
    // properties.required.read = true;
    // properties.required.write = true;
    // properties.required.run = true;
    // properties.required.privileged = true;
    //return (uintreg_t)MM_mmap((void*)0x40000000, PAGESIZE, &properties, pMMDatSec);;
}



/*
if a page is no longer in use, then it does not need to present. 
however, if a page is not present, it can be in use. 
allowed states:
P + U 
NP+ U 
NP+NU 
*/

/*
if page is not present, return value MUST be ZERO. 
*/
// VIRTUAL_ADDRESS read_page(PHYSICAL_ADDRESS from, page_property* properties)
// {
//     uint32_t* p = (uint32_t*)PM_PAGING_4MB_PHYSVIRT_DATA;
//     uint32_t indx = from/PAGESIZE;
//     uint32_t data = *(p+indx);

//     properties->required.present = TESTBIT(data, 0);
//     properties->required.read = true;
//     properties->required.write = TESTBIT(data, 1);
//     properties->required.execute = true;
//     properties->required.privileged = TESTBIT(data, 2);
//     properties->required.busy = TESTBIT(data, 9);

//     if (properties->required.present)
//         return data-data%PAGESIZE;
//     else
//         return (VIRTUAL_ADDRESS)0;
// }

PHYSICAL_ADDRESS read_page(VIRTUAL_ADDRESS from, page_property* properties)
{
    uint32_t* p = (uint32_t*)PM_PAGING_4MB_VIRTPHYS_DATA;
    uint32_t indx = from/PAGESIZE;
    uint32_t data = *(p+indx);

    properties->required.present = TESTBIT(data, 0);
    properties->required.read = true;
    properties->required.write = TESTBIT(data, 1);
    properties->required.execute = true;
    properties->required.privileged = TESTBIT(data, 2);
    properties->required.busy = TESTBIT(data, 9);

    if (properties->required.present)
        return data-data%PAGESIZE;
    else
        return (PHYSICAL_ADDRESS)0;
}
PHYSICAL_ADDRESS fetch_page_addr(VIRTUAL_ADDRESS from)
{
    uint32_t* p = (uint32_t*)PM_PAGING_4MB_VIRTPHYS_DATA;
    uint32_t indx = from/PAGESIZE;
    uint32_t data = *(p+indx);
    return data-data%PAGESIZE;
}
VIRTUAL_ADDRESS write_page(PHYSICAL_ADDRESS from, VIRTUAL_ADDRESS to, page_property* properties)
{
    uint32_t* p = (uint32_t*)PM_PAGING_4MB_VIRTPHYS_DATA;
    uint32_t indx = to/PAGESIZE;
    uint32_t data = *(p+indx);

    if (properties->required.present) data = SETBIT(data, 0);
    else data = CLEARBIT(data, 0);
    if (properties->required.write) data = SETBIT(data, 1);
    else data = CLEARBIT(data, 1);
    if (properties->required.privileged) data = CLEARBIT(data, 2);
    else data = SETBIT(data, 2);
    if (properties->required.busy) data = SETBIT(data, 9);
    else
    {
         data = CLEARBIT(data, 9);
         data = CLEARBIT(data, 0);
    }

    data &= 0b1111111111111;
    data += from-from%PAGESIZE;
    *(p+indx) = data;

    // p = (uint32_t*)PM_PAGING_4MB_PHYSVIRT_DATA;
    // indx = from/PAGESIZE;
    // data &= 0b1111111111111;
    // data += to-to%PAGESIZE;
    // *(p+indx) = data;

    return to-to%PAGESIZE;
}

void flush_page(VIRTUAL_ADDRESS from)
{
    // VIRTUAL_ADDRESS vaddr = lookup_phys_to_virt(from, GetTypedPtrAt(MM_Data_Section_H, LIBMM_DATSEC_PTR));
    __asm__ volatile ("invlpg %0" : : ""((long)from));
}

/* END REQUIRED INTERFACE */
