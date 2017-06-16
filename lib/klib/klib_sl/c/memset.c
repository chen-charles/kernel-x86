#include    "klib_sl.h"


void* memset(void* ptr, int value, size_t num)
{
    unsigned char* p = (unsigned char*)ptr;
    for (int i=0; i<num; i++)
        p[i] = (unsigned char)value;
    return ptr;
}

