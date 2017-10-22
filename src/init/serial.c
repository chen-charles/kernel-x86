#include "include/serial.h"
#include "include/bochsdbg.h"

int serial_received()
{
    return inb(COM1 + 5) & 1;
}

char read_serial()
{
    while (serial_received() == 0);

    return inb(COM1);
}

int is_transmit_empty()
{
    return inb(COM1 + 5) & 0x20;
}

void write_serial(char a)
{
    while (is_transmit_empty() == 0);

    outb(COM1, a);
}

int serial_irq_handler(void* esp, uint8_t int_id)
{
    while(serial_received()) 
    {
        serial_printf("Received: %d\r\n", (int)read_serial());
    }
    return 0;
}

int serial_init()
{
    outb(COM1 + 1, 0x00);    // Disable all interrupts
    outb(COM1 + 3, 0x80);    // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1 + 1, 0x00);    //                  (hi byte)
    outb(COM1 + 3, 0x03);    // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B);    // IRQs enabled, RTS/DSR set

    set_interrupt_handler(serial_irq_handler, INT_VEC_IOAPIC_IRQ4);

    // read_serial();  // blocking
    serial_println("Serial started. ");
    
    return 0;
}

void serial_print(const char* c_str)
{
    if (!c_str) return;
    while (*c_str)
        write_serial(*(c_str++));
}

void serial_println(const char* c_str)
{
    serial_print(c_str);
    write_serial('\n');
}

int serial_printf(const char* format, ...)
{
    va_list args;  
    va_start(args, format);

    bool inFormat = false;
    bool inEscape = false;
    int indx = 0;

    while (*(format+indx))
    {
        char cur = *(format + indx++);

        int num, rev_num;
        switch (cur)
        {
        case '\\':
            if (inEscape) inEscape = false;
            else
            {
                inEscape = true;
                break;
            }
        case '%':
            if (inFormat)
                goto __printf_format_unrecognized;
            
            inFormat = true;
            break;
        case 's':
            if (inFormat)
            {
                inFormat = false;
                serial_print(va_arg(args, const char*));
                break;
            }
        case 'd':
            if (inFormat)
            {
                inFormat = false;
                num = va_arg(args, int);
                rev_num = 0;

                for (; num; num /= 10)
                {
                    rev_num *= 10;
                    rev_num += num%10;
                }

                if (!rev_num)
                    write_serial('0');
                    
                for (; rev_num; rev_num /= 10)
                    write_serial('0' + rev_num%10);
                
                break;
            }
        default:
            if (inFormat)
            {
                inFormat = false;
                goto __printf_format_unrecognized;
            }
            write_serial(cur);
        }
    }

    va_end(args);
    return indx;

__printf_format_unrecognized:
    serial_printf("serial_printf > format unrecognized @ %d\n\tformat=", indx - 1);
    serial_println(format);
    return indx;
}
