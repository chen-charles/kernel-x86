cmake_minimum_required(VERSION 3.0)
project(libproc)

set(CMAKE_VERBOSE_MAKEFILE off)

SET (CMAKE_C_FLAGS "-std=c11 -masm=intel -m32 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "-O2")
SET (CMAKE_CXX_FLAGS "-std=c++11 -masm=intel -m32 -ffreestanding -fno-rtti -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

#MESSAGE(STATUS "clink: " ${CMAKE_C_LINK_EXECUTABLE})
set(CMAKE_KERNELLD_LINK_EXECUTABLE "ld <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")

SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
ENABLE_LANGUAGE (ASM_NASM)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)


file(GLOB libramfs_SRC
	"*.h"
	"*.c"
	"*.hpp"
	"*.cc"
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(libramfs ${libramfs_SRC})
SET_TARGET_PROPERTIES(libramfs PROPERTIES LINKER_LANGUAGE C)
SET_TARGET_PROPERTIES(libramfs PROPERTIES PREFIX "")
target_link_libraries(libramfs klib_sl)
