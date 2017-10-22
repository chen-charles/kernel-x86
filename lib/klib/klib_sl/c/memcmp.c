#include    "klib_sl.h"

int memcmp(const void* lhs, const void* rhs, size_t count)
{
    byte *left=(byte*)lhs, *right=(byte*)rhs;
    for (size_t i = 0; i < count; i++)
    {
        if (*left != *right)
            return *left - *right;
        left ++; right ++;
    }
    
    return 0;
}
