project(basic_math_operations C)

enable_language(ASM_NASM)
enable_language(C)

add_library(
    basic_math_operations

    basic_math_operations.c

    strlen.asm
    remove_leading_zeroes.asm

    add_whole.asm
    add_whole_same_length.asm

    subtract_whole.asm
    subtract_whole_same_length.asm

    multiply_whole.asm

    divide_whole_with_remainder.asm
)