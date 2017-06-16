#include "mm.paging.h"

uint32_t mm_edit_page(bool isPresent, uint32_t virt_loc, uint32_t phy_loc, uint8_t access_r, uint32_t* paging_data_addr, const uint32_t page_size)
{
    uint32_t* p = (uint32_t*)paging_data_addr;
    p += virt_loc/page_size;
    *p = (phy_loc-phy_loc%page_size)|access_r;
    if (isPresent) setbit(p, 0);
    else clearbit(p, 0);
    flush_cache();
    return *p;
}
