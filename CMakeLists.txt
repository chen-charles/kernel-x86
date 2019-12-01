cmake_minimum_required(VERSION 3.0)
project(kernel-x86)

set(CMAKE_VERBOSE_MAKEFILE off)
SET (CMAKE_C_FLAGS "-D DEBUG -D DO_CHECK -g -std=c11 -O0 -masm=intel -m32 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "-O2")
SET (CMAKE_CXX_FLAGS "-D DEBUG -D DO_CHECK -g -std=c++11 -O0 -masm=intel -m32 -ffreestanding -fno-rtti -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "")
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")

#MESSAGE(STATUS "clink: " ${CMAKE_C_LINK_EXECUTABLE})
set(CMAKE_KERNELLD_LINK_EXECUTABLE "ld <LINK_FLAGS> -o <TARGET> <OBJECTS> <LINK_LIBRARIES>")

SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
ENABLE_LANGUAGE (ASM_NASM)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/lib/klib)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(initrd)
