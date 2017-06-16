;/*  multiboot2.h - Multiboot 2 header file.  */
;/*  Copyright (C) 1999,2003,2007,2008,2009,2010  Free Software Foundation, Inc.
; *
; *  Permission is hereby granted, free of charge, to any person obtaining a copy
; *  of this software and associated documentation files (the "Software"), to
; *  deal in the Software without restriction, including without limitation the
; *  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
; *  sell copies of the Software, and to permit persons to whom the Software is
; *  furnished to do so, subject to the following conditions:
; *
; *  The above copyright notice and this permission notice shall be included in
; *  all copies or substantial portions of the Software.
; *
; *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL ANY
; *  DEVELOPER OR DISTRIBUTOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
; *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
; *  IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
; */


%ifndef MULTIBOOT_HEADER
%define MULTIBOOT_HEADER

;/* How many bytes from the start of the file we search for the header.  */
MULTIBOOT_SEARCH	EQU	32768
MULTIBOOT_HEADER_ALIGN	EQU	8


;/* The magic field should contain this.  */
MULTIBOOT2_HEADER_MAGIC	EQU	0xe85250d6


;/* This should be in %eax.  */
MULTIBOOT2_BOOTLOADER_MAGIC	EQU	0x36d76289


;/* Alignment of multiboot modules.  */
MULTIBOOT_MOD_ALIGN	EQU	0x00001000


;/* Alignment of the multiboot info structure.  */
MULTIBOOT_INFO_ALIGN	EQU	0x00000008


;/* Flags set in the 'flags' member of the multiboot header.  */
MULTIBOOT_TAG_ALIGN	EQU	8
MULTIBOOT_TAG_TYPE_END	EQU	0
MULTIBOOT_TAG_TYPE_CMDLINE	EQU	1
MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME	EQU	2
MULTIBOOT_TAG_TYPE_MODULE	EQU	3
MULTIBOOT_TAG_TYPE_BASIC_MEMINFO	EQU	4
MULTIBOOT_TAG_TYPE_BOOTDEV	EQU	5
MULTIBOOT_TAG_TYPE_MMAP	EQU	6
MULTIBOOT_TAG_TYPE_VBE	EQU	7
MULTIBOOT_TAG_TYPE_FRAMEBUFFER	EQU	8
MULTIBOOT_TAG_TYPE_ELF_SECTIONS	EQU	9
MULTIBOOT_TAG_TYPE_APM	EQU	10
MULTIBOOT_TAG_TYPE_EFI32	EQU	11
MULTIBOOT_TAG_TYPE_EFI64	EQU	12
MULTIBOOT_TAG_TYPE_SMBIOS	EQU	13
MULTIBOOT_TAG_TYPE_ACPI_OLD	EQU	14
MULTIBOOT_TAG_TYPE_ACPI_NEW	EQU	15
MULTIBOOT_TAG_TYPE_NETWORK	EQU	16


MULTIBOOT_HEADER_TAG_END	EQU	0
MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST	EQU	1
MULTIBOOT_HEADER_TAG_ADDRESS	EQU	2
MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS	EQU	3
MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS	EQU	4
MULTIBOOT_HEADER_TAG_FRAMEBUFFER	EQU	5
MULTIBOOT_HEADER_TAG_MODULE_ALIGN	EQU	6


MULTIBOOT_ARCHITECTURE_I386	EQU	0
MULTIBOOT_ARCHITECTURE_MIPS32	EQU	4
MULTIBOOT_HEADER_TAG_OPTIONAL	EQU	1


MULTIBOOT_CONSOLE_FLAGS_CONSOLE_REQUIRED	EQU	1
MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED	EQU	2


; usage: InformationRequestTag ignorable, count
;        ignorable:  bool
;        count:     dd
%macro InformationRequestTag 2
    align 8
    dw  1
    dw  (%1 | 1)
    dd  (%2)*4+8
%endmacro ; Follow by a list of required tags: dd


; usage: AddressTag ignorable, header_addr, load_addr, load_end_addr, bss_end_addr
;        ignorable: bool
;        header_addr:   dd  
;           the physical memory location at which the magic value is supposed to be loaded
;        load_addr: dd
;           the physical address of the beginning of the text segment
;        load_end_addr: dd
;           Contains the physical address of the end of the data segment. (load end addr
;- load addr) specifies how much data to load. This implies that the text and
;data segments must be consecutive in the OS image; this is true for existing
;a.out executable formats. If this field is zero, the boot loader assumes that the
;text and data segments occupy the whole OS image file.
;        bss_end_addr:  dd
;           Contains the physical address of the end of the bss segment. The boot loader
;initializes this area to zero, and reserves the memory it occupies to avoid placing
;boot modules and other data relevant to the operating system in that area. If
;this field is zero, the boot loader assumes that no bss segment is present.
%macro AddressTag 5
    align 8
    dw  2
    dw  %1 | 1
    dd  24
    dd  %2
    dd  %3
    dd  %4
    dd  %5
%endmacro

; usage: EntryAddressTag ignorable, entry_addr
;        ignorable: bool
;        entry_addr:    dd
;           The physical address to which the boot loader should jump in order to start
;running the operating system.
%macro EntryAddressTag 2
    align 8
    dw  3
    dw  %1 | 1
    dd  12
    dd  %2
%endmacro    

; usage: FlagsTag ignorable, b0, b1
;        ignorable: bool
;        b0, b1:    bool
;           If this tag is present and bit 0 of ‘console_flags’ is set at least one of supported
;consoles must be present and information about it must be available in mbi. If bit ‘1’ of
;‘console_flags’ is set it indicates that the OS image has EGA text support.
%macro EntryAddressTag 3
    align 8
    dw  4
    dw  %1 | 1
    dd  12
    dd  (%2 | 1) | ((%3 | 1) << 1)
%endmacro 

; usage: framebufferTag ignorable, width, height, depth
;        ignorable: bool
;        width, height, depth:    dw
%macro framebufferTag 4
    align 8
    dw  5
    dw  %1 | 1
    dd  20
    dd  %2
    dd  %3
    dd  %4
%endmacro
   
; usage: ModuleAlignmentTag ignorable
;        ignorable: bool
%macro ModuleAlignmentTag 1
    align 8
    dw  6
    dw  %1 | 1
    dd  8
%endmacro

%endif
