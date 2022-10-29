section .text
global  strlen
strlen:
  ; Input:
  ;   - char *str -> rcx

  ; Registers used:
  ;   - rdx

  xor    edx, edx
  mov    rax, -1
.loop:
  inc    rax
  mov    dl, byte[rcx + rax]
  test   dl, dl
  jnz    .loop
  ret