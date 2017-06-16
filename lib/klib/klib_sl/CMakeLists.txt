project(klib_sl)
file(GLOB_RECURSE klib_sl_SRC
	"*.h"
	"*.c"
	"*.hpp"
	"*.cc"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(klib_sl ${klib_sl_SRC})
SET_TARGET_PROPERTIES(klib_sl PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(klib_sl PROPERTIES PREFIX "")
