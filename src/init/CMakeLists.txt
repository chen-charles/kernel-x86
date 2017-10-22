file(GLOB_RECURSE init_SRC
	"*.h"
	"*.c"
	"*.cpp"
	"*.inc"
	"*.nasm"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(init ${init_SRC})
SET_TARGET_PROPERTIES(init PROPERTIES LINKER_LANGUAGE C)
target_link_libraries(init klib_sl klib_ad-x86 libmalloc libelfff libmm libramfs )
