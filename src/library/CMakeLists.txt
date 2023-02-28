cmake_minimum_required(VERSION 3.16)

project(basic_math_operations C)

enable_language(ASM_NASM)
enable_language(C)
enable_language(CXX)

if(UNIX)
    set(sources_linux
        basic_math_operations.c
        basic_math_operations.cpp

        linux/strlen_asm.asm
        linux/remove_leading_zeroes.asm

        linux/add_whole.asm
        linux/add_whole_same_length.asm
        cross-platform/add.c

        linux/subtract_whole.asm
        linux/subtract_whole_same_length.asm
        cross-platform/subtractp.c
        cross-platform/subtract.c

        linux/_multiply_whole.asm
        cross-platform/multiplyp.c
        cross-platform/multiply.c

        linux/_divide_whole_with_remainder.asm
        cross-platform/divide_whole_with_remainder.c
        cross-platform/divide_whole.c
        cross-platform/dividep.c
        cross-platform/divide.c

        linux/asmalloc.asm
        linux/multiply_whole.asm
        cross-platform/addp.c
        cross-platform/remove_zeroes.c

        cross-platform/increment_whole.c
    )
    add_library(basic_math_operations STATIC ${sources_linux})
    add_library(basic_math_operations_so SHARED ${sources_linux})
    set_target_properties(basic_math_operations_so PROPERTIES OUTPUT_NAME basic_math_operations)
endif(UNIX)

if(WIN32)
    set(sources_windows
        basic_math_operations.c
        basic_math_operations.cpp

        windows/strlen_asm.asm
        windows/remove_leading_zeroes.asm

        windows/add_whole.asm
        windows/add_whole_same_length.asm
        cross-platform/add.c

        windows/subtract_whole.asm
        windows/subtract_whole_same_length.asm
        cross-platform/subtractp.c
        cross-platform/subtract.c

        windows/_multiply_whole.asm
        cross-platform/multiplyp.c
        cross-platform/multiply.c

        windows/divide_whole_with_remainder.asm
        cross-platform/divide_whole_with_remainder.c
        cross-platform/divide_whole.c
        cross-platform/dividep.c
        cross-platform/divide.c

        cross-platform/multiply_whole.c
        cross-platform/addp.c
        cross-platform/remove_zeroes.c

        cross-platform/increment_whole.c
    )
    add_library(basic_math_operations STATIC ${sources_windows})
    add_library(basic_math_operations_dll SHARED ${sources_windows})
    set_target_properties(basic_math_operations_dll PROPERTIES OUTPUT_NAME basic_math_operations)
endif(WIN32)