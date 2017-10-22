#include    "klib_sl.h"

size_t strlen(const char *str)
{
    size_t i=0;
    while (*(str + i) != '\x00') i++;
    return i;
}
