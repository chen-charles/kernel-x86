/*
library ramfs --- Ramdisk File System
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

#ifndef LIB_RAMFS
#define LIB_RAMFS

#include	<stdbool.h>
#include	<stdint.h>
#include	<stddef.h>

#include    "type.h"

#include    "tar.h"

EXTERN_C

#ifndef strcmp
int strcmp(const char *str1, const char *str2);
#endif

memblock fs_loc_buf(memblock fs_buf, const char* filename);

EXTERN_C_END

#endif
