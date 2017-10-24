#ifndef _SERIAL_
#define _SERIAL_

#include    <stdarg.h>
#include    <stdbool.h>

#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>
#include    <klib_ad/x86/instruction.h>

#include	"include/interrupt.h"
#include    "include/memloc.h"

EXTERN_C

#define COM1 0x3f8   /* COM1 */

// Serial Write
int is_transmit_empty();
void write_serial(char a);

// Serial Read
int serial_received();
char read_serial();

// Serial Init
int serial_irq_handler(void* esp, uint8_t int_id);
int serial_init();

// utils
void serial_print(const char* c_str);
void serial_println(const char* c_str);
int serial_printf(const char* format, ...);
int serial_vprintf(const char* format, va_list args);

// debug interface
#ifdef DEBUG
#define dprintf(...) (*(uintptr_t*)(SERIAL_ENABLED) == SERIAL_ENABLED_MAGIC ? serial_printf(__VA_ARGS__) : 0)
#else
#define dprintf(...) 0
#endif

EXTERN_C_END

#endif
