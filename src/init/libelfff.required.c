#include <klib_sl/type.h>

#include <libmm/libmm.h>
#include "include/serial.h"

#include <libelfff/libelfff.h>

void* elfff_mmap(void* addr, size_t len, elfff_page_property* usage)
{
    page_property properties;
    properties.required.present = true;
    properties.required.read = usage->read;
    properties.required.write = usage->write;
    properties.required.execute = usage->execute;
    properties.required.privileged = false;
    properties.required.busy = true;

    return mmap(addr, len, &properties);
}

int elfff_dprintf(const char * format, ...)
{
    va_list args;
    va_start(args, format);
    int val = serial_vprintf(format, args);
    va_end(args);
    return val;
}
