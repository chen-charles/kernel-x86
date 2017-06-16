// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_IDT_H_
#define _KLIB_IDT_H_

#include <klib_sl/type.h>
#include "gdt.h"

void init_idt_desc(void* ptr, void* handler, byte privilege, uint16_t selector);

#endif
