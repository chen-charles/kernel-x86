file(GLOB start_SRC
	"*.h"
	"*.c"
	"*.inc"
	"*.nasm"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(start ${start_SRC})
SET_TARGET_PROPERTIES(start PROPERTIES LINKER_LANGUAGE KERNELLD)
target_link_libraries(start klib_sl klib_ad-x86 init libmm libmalloc libramfs libelfff)
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker.ld")
set_target_properties(start PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
SET_TARGET_PROPERTIES(start PROPERTIES LINK_FLAGS "-q -m elf_i386 -T ${LINKER_SCRIPT} -nodefaultlibs")
