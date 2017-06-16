#include <klib_sl/type.h>
#include <klib_ad/x86/mm.paging.h>

//#include <libmm/libmm.h>
#include <libmalloc/libmalloc.h>
#include "include/memloc.h"

void *mmap(void* addr, size_t len, page_property* usage);
int munmap(void* addr, size_t len);

uintreg_t libmalloc_init()
{
    Malloc_Ctx* ctx = Malloc_init(PAGESIZE, 1024);
    *(uintptr_t*)(LIBMALLOC_CTX_PTR) = (uintptr_t)ctx;
    return (uintreg_t)ctx;
}

void* malloc(size_t size)
{
    return MM_malloc(size, (Malloc_Ctx*)(*(uintptr_t*)(LIBMALLOC_CTX_PTR)));
}

void free(void* ptr)
{
    MM_free(ptr);
}

void* calloc(size_t num, size_t size)
{
    void* p = malloc(num*size);
    memset(p, 0, num*size);
    return p;
}

void* aligned_malloc(size_t size, size_t alignment)
{
    uintptr_t p = (uintptr_t)malloc(size+alignment);
    return (void*)(p + (alignment-p%alignment));
}

