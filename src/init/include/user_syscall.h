#ifndef __USER_SYSCALL__
#define __USER_SYSCALL__

#include <klib_sl/type.h>

#define SYSCALL_SERIAL_PRINT    0x01

EXTERN_C

/*
Usermode system call entrance: actual meanings are specific to each function
*/
uintreg_t usermode_syscall(uintreg_t callno, uintreg_t wParam, uintreg_t lParam);

/*
Serial output
*/
int usermode_serial_print(const char* c_str);

EXTERN_C_END

#endif
