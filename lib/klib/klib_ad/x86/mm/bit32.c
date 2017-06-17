#include "mm.paging.h"

uintreg_t init_paging_32bit(const uint32_t szPage, memblock aligned_buf)
{
    if (aligned_buf.ptr%0x1000) return -1;   // not aligned

    if (szPage == 0x400000)
    {
        if (aligned_buf.len < 0x4000) return -1;    // buffer too short

        uint32_t pde = 0b10011011;  // Present, RW, PWThrough, noCache
        
        for (int i=0; i<1024; i++)
            *((uint32_t*)(aligned_buf.ptr) + i) = pde + i * 0x400000;

        write_cr3(aligned_buf.ptr);
        write_cr4(SETBIT(read_cr4(), 4));
    }
    else if (szPage == 0x4000)
    {
        if (aligned_buf.len < 0x401000) return -1;

        uint32_t pde = 0b00011011;

        for (int i=0; i<1024; i++)
        {
            *((uint32_t*)(aligned_buf.ptr) + i) = pde + aligned_buf.ptr + (i+1) * 0x1000;
        }

        for (int i=0; i<1024*1024; i++)
        {
            uint32_t pte = 0b00011011;
            *((uint32_t*)(aligned_buf.ptr + 0x1000) + i) = pte + i * 0x1000;
        }

        write_cr3(aligned_buf.ptr);
    }

    write_cr0(SETBIT(read_cr0(), 31));
    flush_cache();
    return aligned_buf.ptr;
}

