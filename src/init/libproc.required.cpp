#include    <libproc/libproc.hpp>
#include    "include/memloc.h"

extern "C" uint64_t SYSTEM_INTERNAL_TIME()
{
    return GetSystemInternalTime();
}

