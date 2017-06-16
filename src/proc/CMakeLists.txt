file(GLOB proc_SRC
	"*.h"
	"*.c"
	"*.inc"
	"*.asm"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(proc ${proc_SRC})
SET_TARGET_PROPERTIES(proc PROPERTIES LINKER_LANGUAGE KERNELLD)
target_link_libraries(proc klib_sl)
SET_TARGET_PROPERTIES(proc PROPERTIES LINK_FLAGS "-q -m elf_i386 -nodefaultlibs")
