<<<<<<< HEAD
section .text
global  strlen
strlen:
  ; Input:
  ;   - char *str -> rcx

  ; Registers used:
  ;   - r11

  xor    r11d, r11d
  mov    rax, -1
.loop:
  inc    rax
  mov    r11b, byte[rcx + rax]
  test   r11b, r11b
  jnz    .loop
=======
section .text
global  strlen
strlen:
  ; Input:
  ;   - char *str -> rcx

  ; Registers used:
  ;   - r11

  xor    r11d, r11d
  mov    rax, -1
.loop:
  inc    rax
  mov    r11b, byte[rcx + rax]
  test   r11b, r11b
  jnz    .loop
>>>>>>> two/main
  ret