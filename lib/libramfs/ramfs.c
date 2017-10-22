#include "ramfs.h"

// http://wiki.osdev.org/Tar
unsigned int getsize(const char *in)
{
    unsigned int size = 0;
    unsigned int j;
    unsigned int count = 1;
 
    for (j = 11; j > 0; j--, count *= 8)
        size += ((in[j - 1] - '0') * count);
 
    return size;
}

memblock fs_loc_buf(memblock fs_buf, const char* filename)
{
    memblock m;
    for (HD_TAR* header = (HD_TAR*)(fs_buf.ptr);
        header->name[0] != '\0';)
        {
            unsigned int size = getsize(header->size);
            if (strcmp(header->name, filename) == 0)
            {
                m.ptr = (uintptr_t)header;
                m.ptr += 512;
                m.len = size;
                return m;
            }
            header = (HD_TAR*)((uintptr_t)header + ((size/512)+1)*512 + (size%512?512:0));
        }

    m.ptr = 0;
    m.len = 0;
    return m;
}
