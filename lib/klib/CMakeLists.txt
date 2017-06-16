cmake_minimum_required(VERSION 3.0)
project(klib)

set(CMAKE_VERBOSE_MAKEFILE off)

SET (CMAKE_C_FLAGS "-std=c11 -masm=intel -m32 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "-O2")
SET (CMAKE_CXX_FLAGS "-std=c++11 -masm=intel -m32 -ffreestanding -fno-rtti -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

SET (CMAKE_ASM_NASM_OBJECT_FORMAT "elf")
ENABLE_LANGUAGE (ASM_NASM)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(klib_sl)
add_subdirectory(klib_ad)
