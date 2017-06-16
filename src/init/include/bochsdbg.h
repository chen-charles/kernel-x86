#ifndef _BOCHSDBG_
#define _BOCHSDBG_

// bochsdbg magic breakpoint
// inline volatile

#define bochsdbg_bp() __asm__ volatile ( "xchg bx, bx" )

#define bochsdbg_bp_eax(eax) \
{   \
    __asm__ volatile ("push eax");  \
    __asm__ volatile ("mov eax, %0" : : ""((long)(eax))); \
    bochsdbg_bp();  \
    __asm__ volatile ("pop eax");   \
}

#define bochsdbg_bp_if_eax_ne(eax_desired)  \
{   \
    __asm__ volatile ("pushf"); \
    __asm__ volatile ("cmp eax, %0" : : ""((long)(eax_desired))); \
    __asm__ goto ("je %l[_equal]" : : : "memory" : _equal);    \
    bochsdbg_bp();  \
_equal: \
    __asm__ volatile ("popf");  \
}

#define bochsdbg_bp_if_equal(v1, v2) \
{   \
    __asm__ volatile ("push eax");  \
    __asm__ volatile ("push ebx");  \
    __asm__ volatile ("pushf"); \
    __asm__ volatile ("mov eax, %0" : : ""((long)(v1)));    \
    __asm__ volatile ("mov ebx, %0" : : ""((long)(v2)));    \
    __asm__ volatile ("cmp eax, ebx");  \
    __asm__ goto ("jne %l[_equal]" : : : "memory" : _equal);    \
    bochsdbg_bp();  \
_equal: \
    __asm__ volatile ("popf");  \
    __asm__ volatile ("pop ebx");   \
    __asm__ volatile ("pop eax");   \
}

#define bochsdbg_assert(v1, v2) \
{   \
    __asm__ volatile ("push eax");  \
    __asm__ volatile ("push ebx");  \
    __asm__ volatile ("pushf"); \
    __asm__ volatile ("mov eax, %0" : : ""((long)(v1)));    \
    __asm__ volatile ("mov ebx, %0" : : ""((long)(v2)));    \
    __asm__ volatile ("cmp eax, ebx");  \
    __asm__ goto ("je %l[_equal]" : : : "memory" : _equal);    \
    bochsdbg_bp();  \
_equal: \
    __asm__ volatile ("popf");  \
    __asm__ volatile ("pop ebx");   \
    __asm__ volatile ("pop eax");   \
}

#endif
