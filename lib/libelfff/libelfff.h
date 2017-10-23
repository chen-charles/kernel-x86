/*
library ELF freestanding --- freestanding elf loader
Copyright (C) 2017  Jianye Chen
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LIB_ELFFF
#define LIB_ELFFF

#include    "type.h"

EXTERN_C

#ifndef uintreg_t
typedef uintptr_t uintreg_t;
#endif

#ifndef IMMEDIATE_SETBIT
#define IMMEDIATE_SETBIT(pos) (1<<pos)
#endif

#ifndef memset
void* memset(void* ptr, int value, size_t num);
#endif
#ifndef memcpy
void* memcpy(void* destination, const void* source, size_t num);
#endif



#include    "elf.h"

// you must implement all functions declared in interface.h
#include    "interface.h"

typedef struct _elfff_context
{
    memblock    raw;

    #ifdef __x86_64__
    Elf64_Ehdr* header;
    Elf64_Phdr* pheader;
    Elf64_Shdr* sheader;
    #else
    Elf32_Ehdr* header;
    Elf32_Phdr* pheader;
    Elf32_Shdr* sheader;
    #endif

    char*   strtab;
    
    uintptr_t   prog_entry;
}
elfff_ctx;

typedef unsigned int ELFFF_STATUS;
#define ELFFF_SUCCESS   0
#define ELFFF_HEADER_INVALID    1
#define ELFFF_MMAP_FAIL 2
#define ELFFF_VADDR_INVALID 3

ELFFF_STATUS elfff_load(elfff_ctx* context);

EXTERN_C_END

#endif
