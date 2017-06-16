#ifndef KINIT_ALLOC
#define KINIT_ALLOC 1

#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>

/*
Kernel Initialization Memory Space

TODO: include release operations
*/

EXTERN_C

static const uintreg_t _kinit_alloc_address = 0x400000;
static const uintreg_t _min_alloc_size = 0x100000;
static const uintreg_t _kinit_alloc_size = 0x400000;

void* kinit_alloc(size_t size);
void* kinit_aligned_alloc(size_t size, size_t alignment);

EXTERN_C_END

#endif
