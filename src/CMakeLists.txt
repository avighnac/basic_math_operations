project(basic_math_operations)

enable_language(ASM_NASM)

add_library(basic_math_operations.c

            strlen.asm

            add_whole.asm
            add_whole_same_length.asm)