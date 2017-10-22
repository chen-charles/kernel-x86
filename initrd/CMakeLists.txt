cmake_minimum_required(VERSION 3.0)
project(initrd)

set(CMAKE_VERBOSE_MAKEFILE off)
SET (CMAKE_C_FLAGS "-std=c11 -O0 -masm=intel -m32 -ffreestanding -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_C_FLAGS_DEBUG "-g3")
set(CMAKE_C_FLAGS_RELEASE "-O2")
SET (CMAKE_CXX_FLAGS "-std=c++11 -O0 -masm=intel -m32 -ffreestanding -fno-rtti -fno-exceptions -nostdlib -fno-stack-protector")
set(CMAKE_CXX_FLAGS_DEBUG "-g3")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

set(CMAKE_C_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_C_IMPLICIT_LINK_DIRECTORIES "")
set(CMAKE_CXX_IMPLICIT_LINK_LIBRARIES "")
set(CMAKE_CXX_IMPLICIT_LINK_DIRECTORIES "")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/initrd/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/initrd/)

add_subdirectory(binary)
add_subdirectory(proc)
