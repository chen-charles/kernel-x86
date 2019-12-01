#ifndef KINIT_PANIC_H
#define KINIT_PANIC_H

#include <klib_sl/type.h>

EXTERN_C

// NO_EXIT
void panic(const char* format, ...);

EXTERN_C_END

#endif
