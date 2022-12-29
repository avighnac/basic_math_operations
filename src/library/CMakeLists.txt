project(basic_math_operations C)

enable_language(ASM_NASM)
enable_language(C)

if (UNIX)
add_library(
    basic_math_operations

    basic_math_operations.c

    linux/strlen.asm
    linux/remove_leading_zeroes.asm

    linux/add_whole.asm
    linux/add_whole_same_length.asm

    linux/subtract_whole.asm
    linux/subtract_whole_same_length.asm

    linux/_multiply_whole.asm

    linux/divide_whole_with_remainder.asm

    linux/asmalloc.asm
    linux/multiply_whole.asm
    linux/addp.asm
)
endif (UNIX)

if (WIN32)
add_library(
    basic_math_operations

    basic_math_operations.c

    windows/strlen.asm
    windows/remove_leading_zeroes.asm

    windows/add_whole.asm
    linux/add_whole_same_length.asm

    windows/subtract_whole.asm
    linux/subtract_whole_same_length.asm

    windows/_multiply_whole.asm

    windows/divide_whole_with_remainder.asm

    windows/multiply_whole.c
    windows/addp.c
)
endif (WIN32)