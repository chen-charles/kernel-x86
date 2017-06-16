#include    "include/kinit_alloc.h"

void* kinit_alloc(size_t size)
{
    if (_kinit_alloc_size < _min_alloc_size) return (void*)0;
    
    
    // 32bits
    // HEADERHEA CURSORCURSORCURSORC RAWRAWRAWRAW
    // 0xff 0xff 0xHH 0xHH 0xHH 0xHH DATADATADATA
    
    if (*(uint16_t*)_kinit_alloc_address != 0xfffc) 
    {
        *(uint16_t*)_kinit_alloc_address = 0xfffc;
        *(uintreg_t*)(_kinit_alloc_address + sizeof(uint16_t)) = 0;
    }
    uintreg_t* cur = (uintreg_t*)(_kinit_alloc_address+2);
    if (_kinit_alloc_address + sizeof(uint16_t) + sizeof(uintreg_t) + *cur + size >= _kinit_alloc_address + _kinit_alloc_size) return (void*)0;
    *cur += size;
    
    return (void*)(_kinit_alloc_address + sizeof(uint16_t) + sizeof(uintreg_t) + *cur - size);
}

void* kinit_aligned_alloc(size_t size, size_t alignment)
{
    void* p = kinit_alloc(size);
    int k=0;
    do {(uintptr_t)p++;k++;} while ((uintptr_t)p % alignment != 0);
    kinit_alloc(k);
    return p;
}
