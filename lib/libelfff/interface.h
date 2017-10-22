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

#ifndef LIB_ELFFF_INTERFACE
#define LIB_ELFFF_INTERFACE

// standard library functions
int memcmp ( const void * ptr1, const void * ptr2, size_t num );
void * memcpy ( void * destination, const void * source, size_t num );
void * memset ( void * ptr, int value, size_t num );

int elfff_dprintf(const char *format, ...);

// mmap
typedef struct
{
    bool read;
    bool write;
    bool execute;
}
elfff_page_property;
void *elfff_mmap(void* addr, size_t len, elfff_page_property* usage);

#endif
