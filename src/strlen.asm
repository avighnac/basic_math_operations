section .text
global strlen
strlen:
  ; Input:
  ;   - char *str -> rdi

  ; Registers used:
  ;   - rcx

  xor    rcx, rcx
  mov    rax, -1
_strlen_loop:
  inc    rax
  mov    cl, byte[rdi + rax]
  test   cl, cl
  jnz    _strlen_loop
  ret