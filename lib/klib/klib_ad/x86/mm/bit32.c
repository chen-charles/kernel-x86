#include "mm.paging.h"



uintreg_t init_paging_32bit(const uint32_t szPage, memblock aligned_buf)
{
    if (aligned_buf.ptr%4) return -1;   // not aligned

    if (szPage == 0x400000)
    {
        if (aligned_buf.len < 0x4000) return -1;    // buffer too short

        uint32_t pde = 0b10011011;  // Present, RW, PWThrough, noCache
        
        for (int i=0; i<1024; i++)
            *((uint32_t*)(aligned_buf.ptr)+i) = pde + 0x400000*i;

        write_cr3(aligned_buf.ptr);
        write_cr4(SETBIT(read_cr4(), 4));
        write_cr0(SETBIT(read_cr0(), 31));
        flush_cache();
    }
    else if (szPage == 0x4000)
    {
        return -1;  // not implemented
    }
}

