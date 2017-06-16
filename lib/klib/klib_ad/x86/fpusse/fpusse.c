#include "fpusse.h"

int fpu_sse_init()
{
    int cr0 = read_cr0();
    int cr4 = read_cr4();
    if (is_fpu_present())
    {
        cr0 = CLEARBIT(cr0, 2);
        cr0 = SETBIT(cr0, 5);
        cr0 = SETBIT(cr0, 1);
        write_cr0(cr0);
        if (is_sse_present())
        {
            cr4 = SETBIT(cr4, 9);
            cr4 = SETBIT(cr4, 10);
            write_cr4(cr4);
        }
    }
    else
    {
        cr0 = SETBIT(cr0, 2);
        cr0 = CLEARBIT(cr0, 5);
        write_cr0(CLEARBIT(cr0, 1));
    }
    
    return 0;
}
