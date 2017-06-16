#include    "klib_sl.h"


void* memcpy(void* dest, const void* src, size_t len)
{
    char* d = (char*)dest;
    const char* s = (const char*)src;
    for (size_t i=0; i<len; i++)
        d[i] = s[i];
    return dest;
}

