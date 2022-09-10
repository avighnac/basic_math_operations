project(basic_math_operations)

enable_language(ASM_NASM)
enable_language(C)

add_library(
    basic_math_operations.c

    strlen.asm

    add_whole.asm
    add_whole_same_length.asm

    subtract_whole.asm
    subtract_whole_same_length.asm
)