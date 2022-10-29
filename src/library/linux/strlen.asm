section .text
global strlen
strlen:
  ; Input:
  ;   - char *str -> rdi

  ; Registers used:
  ;   - rcx

  xor    ecx, ecx
  mov    rax, -1
.loop:
  inc    rax
  mov    cl, byte[rdi + rax]
  test   cl, cl
  jnz    .loop
  ret