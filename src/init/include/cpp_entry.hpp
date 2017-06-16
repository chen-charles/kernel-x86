#ifndef _CPP_ENTRY_
#define _CPP_ENTRY_

#define __cplusplus 201103L
#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>
#include    <klib_sl/cc/klib_sl.hpp>
// #include    <typeinfo>

//must be redeclared as extern "C", since cpp makes diff symname
extern "C" void* malloc(size_t size);
extern "C" void* calloc (size_t num, size_t size);
extern "C" void* realloc (void* ptr, size_t size); //not tested yet    //even expands, the data is unchanged, but the ptr might do
extern "C" void free(void* ptr);	//this ptr MUST be the first byte of the data space allocated


void *operator new(size_t size);
void *operator new[](size_t size);

void operator delete(void *p);
void operator delete[](void *p);



#endif
