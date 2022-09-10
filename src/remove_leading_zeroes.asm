extern strlen

section .text
global remove_leading_zeroes
remove_leading_zeroes:
  ; Input:
  ;   - const char *string -> rdi
  ;   - char *res -> rsi

  ; Registers used:
  ;   - rcx
  ;   - rdx
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11

  call   strlen
  lea    r10, [rax - 1]
  xor    r8b, r8b
  cmp    byte [rdi], 2DH
  sete   cl
  movzx  r9, cl
  mov    rdx, r9
  test   cl, cl
  jz     _remove_leading_zeroes_loop_1
  mov    byte [rsi], 2DH
_remove_leading_zeroes_loop_1:
  cmp    byte [rdi + rdx], 48
  jz     _after_remove_leading_zeroes_if_1
  mov    r8b, 1
_after_remove_leading_zeroes_if_1:
  cmp    rdx, r10
  sete   r11b
  or     r11b, r8b
  test   r11b, r11b
  jz     _after_remove_leading_zeroes_if_2
  mov    r11b, byte [rdi + rdx]
  mov    byte [rsi + r9], r11b
  inc    r9
_after_remove_leading_zeroes_if_2:
  inc    rdx
  cmp    rdx, rax
  js     _remove_leading_zeroes_loop_1
  mov    byte [rsi + r9], 0
  ret