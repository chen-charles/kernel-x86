file(GLOB_RECURSE klib_ad-x86_SRC
	"*.h"
	"*.c"
	"*.inc"
	"*.asm"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(klib_ad-x86 ${klib_ad-x86_SRC})
SET_TARGET_PROPERTIES(klib_ad-x86 PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(klib_ad-x86 PROPERTIES PREFIX "")
target_link_libraries(klib_ad-x86 klib_sl)
