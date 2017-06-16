#ifndef _KLIB_CPUID_H_
#define _KLIB_CPUID_H_

static inline void cpuid(int code, uint32_t* a, uint32_t* d)
{
    __asm__ __volatile__ (".intel_syntax noprefix");
    __asm__ __volatile__ ( "cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx" );
}

#endif
