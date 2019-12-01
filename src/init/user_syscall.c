#include "include/user_syscall.h"
#include "include/interrupt.h"

uintreg_t usermode_syscall(_IN_ uintreg_t callno, _IN_OUT_ uintreg_t wParam, _IN_OUT_ uintreg_t lParam)
{
    uintreg_t retval;

    __asm__ volatile (
        "mov ecx, %1\n"
        "mov edx, %2\n"
        "mov ebx, %3\n"
        "int %4\n"
        "mov %0, eax"
        : "=rm" (retval)
        : "m" (callno), "m" (wParam), "m" (lParam), "n"((INT_VEC_SYSCALL))
        : "eax", "ebx", "ecx", "edx", "memory"
    );

    return retval;
}

int usermode_serial_print(const char* c_str)
{
    return usermode_syscall(SYSCALL_SERIAL_PRINT, c_str, 0);
}
