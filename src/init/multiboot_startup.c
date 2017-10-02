#include    "include/multiboot2.h"
#include    "include/bochsdbg.h"
#include    <klib_sl/type.h>
#include    <klib_sl/c/klib_sl.h>

uintreg_t multiboot_startup(uint32_t header);

// uintreg_t multiboot_startup(byte* header)
// Returns 0 if the multiboot startup was successful
// 
// input: EBX
// 
// parses multiboot startup information into global constants
// This Function is called right after C-code envir is prepared
uintreg_t multiboot_startup(uint32_t header)
{
    uint32_t totalsize = *(uint32_t*)header;
    uintptr_t tagHeaderLoc = header+8;

    while (tagHeaderLoc != header + totalsize)
    {
        multiboot_tag_t* tagHeader = (multiboot_tag_t*)tagHeaderLoc;
        
        switch(tagHeader->type)
        {
            case MULTIBOOT_TAG_TYPE_END:
                break;
            case MULTIBOOT_TAG_TYPE_CMDLINE:
                break;
            case MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME:
                break;
            case MULTIBOOT_TAG_TYPE_MODULE:
                break;
            case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
                break;
            case MULTIBOOT_TAG_TYPE_BOOTDEV:
                break;
            case MULTIBOOT_TAG_TYPE_MMAP:
                // memory manager
                break;
            case MULTIBOOT_TAG_TYPE_VBE:
                // vbe 2.0+, not comp w/ vbe 3.0
                break;
            case MULTIBOOT_TAG_TYPE_FRAMEBUFFER:
                for (uint32_t* p = (uint32_t*)(uint32_t)(((struct multiboot_tag_framebuffer*)tagHeader)->common.framebuffer_addr);
                    (uintptr_t)p < ((struct multiboot_tag_framebuffer*)tagHeader)->common.framebuffer_addr 
                        + 
                        ((struct multiboot_tag_framebuffer*)tagHeader)->common.framebuffer_width
                        *
                        ((struct multiboot_tag_framebuffer*)tagHeader)->common.framebuffer_height
                        *
                        4;
                    p++)
                    *p = 0x000000FF;    // X R G B
                break;
            case MULTIBOOT_TAG_TYPE_ELF_SECTIONS:
                break;
            case MULTIBOOT_TAG_TYPE_APM:    // APM Table --> successor: ACPI
                break;
            case MULTIBOOT_TAG_TYPE_EFI32:
                break;
            case MULTIBOOT_TAG_TYPE_EFI64:
                break;
            case MULTIBOOT_TAG_TYPE_SMBIOS:
                break;
            case MULTIBOOT_TAG_TYPE_ACPI_OLD:
                break;    
            case MULTIBOOT_TAG_TYPE_ACPI_NEW:
                break;
            case MULTIBOOT_TAG_TYPE_NETWORK:
                break;
            // default is reserved
        }
        
        
        // padding @ 8 bytes
        tagHeaderLoc += tagHeader->size%8==0 ? tagHeader->size : tagHeader->size + 8 - tagHeader->size%8;
    }

    return tagHeaderLoc-header-totalsize;
}
