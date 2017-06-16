#ifndef _KLIB_FPUSSE_H_
#define _KLIB_FPUSSE_H_

#include <klib_sl/type.h>
#include <klib_sl/c/klib_sl.h>
#include "instruction.h"

EXTERN_C

bool is_fpu_present();
bool is_sse_present();

int fpu_sse_init();

void fxsave(void* destination);
void fxrstor(void* source);

EXTERN_C_END

#endif
