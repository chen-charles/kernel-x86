// Copyright 2016 Jianye Chen All Rights Reserved.

#ifndef _KLIB_TYPE_H_
#define _KLIB_TYPE_H_

//Conventions
#include	<stdint.h>
#include	<stddef.h>
#include	<stdbool.h>

typedef unsigned char byte;
typedef uintptr_t uintreg_t;	//general purpose register uint repr.

#ifdef __cplusplus
#define EXTERN_C extern "C" {
#define EXTERN_C_END } 
#else
#define EXTERN_C 
#define EXTERN_C_END 
#endif	//__cplusplus

typedef struct
{
	uintptr_t ptr;
	size_t len;
}
memblock;

#ifndef _IN_
#define _IN_
#endif

#ifndef _OUT_
#define _OUT_
#endif

#ifndef _IN_OUT_
#define _IN_OUT_
#endif

#endif
