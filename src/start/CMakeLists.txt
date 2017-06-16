file(GLOB start_SRC
	"*.h"
	"*.c"
	"*.inc"
	"*.asm"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(start ${start_SRC})
SET_TARGET_PROPERTIES(start PROPERTIES LINKER_LANGUAGE KERNELLD)
target_link_libraries(start klib_sl klib_ad-x86 init libmm libmalloc)
SET_TARGET_PROPERTIES(start PROPERTIES LINK_FLAGS "-q -m elf_i386 -Ttext 0x100000 -nodefaultlibs")
