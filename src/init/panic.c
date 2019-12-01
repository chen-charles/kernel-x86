#include "include/panic.h"
#include "include/serial.h"
#include "include/bochsdbg.h"

#include <klib_ad/x86/instruction.h>

void panic(const char* format, ...)
{
    /* Disable interrupts to stop the system from receiving any more context switches */
    cli();

    /* Call the unprotected versions so we don't hang on spinlock */
    serial_println("\n\n\n>>>PANIC<<<");
    serial_println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");

    va_list args;  
    va_start(args, format);
    serial_vprintf(format, args);
    va_end(args);

    serial_println("\nI don't know what to do... I think I will just die now...");
    serial_println("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<");

    while(1);
    
    // NO_EXIT
}
