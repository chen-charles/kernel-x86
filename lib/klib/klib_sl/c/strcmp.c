#include    "klib_sl.h"

int strcmp(const char *str1, const char *str2)
{
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int mcmp = memcmp((const void*)str1, (const void*)str2, (len1 < len2 ? len1 : len2));
    if (len1 != len2 && mcmp == 0)
        return len1 > len2 ? 1 : -1;
    return mcmp;
}
