ENTRY(_start)
OUTPUT_FORMAT(elf32-i386)

SECTIONS 
{
    . = 0x100000;

    .start : 
    {
        */start.nasm.o(.*)
        
    }

    .init : ALIGN (0x1000) 
    {
        */libinit.a:*(.*)
    }

    .libs : ALIGN (0x1000) 
    {
        */*.a:*(.*)
    }
}
