%include "defines.asm"

extern Strlen_asm

section .text
global Remove_leading_zeroes
Remove_leading_zeroes:
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

  CALL(Strlen_asm)
  lea    r10, [rax-1]
  xor    r8b, r8b
  cmp    byte [rdi], 2DH
  sete   cl
  movzx  r9, cl
  mov    rdx, r9
  test   cl, cl
  jz     .loop_1
  mov    byte [rsi], 2DH
.loop_1:
  cmp    byte [rdi+rdx], 48
  jz     .after_if_1
  mov    r8b, 1
.after_if_1:
  cmp    rdx, r10
  sete   r11b
  or     r11b, r8b
  test   r11b, r11b
  jz     .after_if_2
  mov    r11b, byte [rdi+rdx]
  mov    byte [rsi+r9], r11b
  inc    r9
.after_if_2:
  inc    rdx
  cmp    rdx, rax
  js     .loop_1
  mov    byte [rsi+r9], 0
  ret
global Remove_leading_zeroes_inplace
Remove_leading_zeroes_inplace:
  ; Input:
  ;   - char *number -> rdi, removes the leading zeroes in [number] in-place.
  ;                          Note that [number] has to be non negative.

  ; Registers used:
  ;   - rax
  ;   - ecx
  ;   - edx
  ;   - r8

  lea    rax, [rdi-1]
.loop_1:
  inc    rax
  cmp    byte [rax], 48
  jz     .loop_1
  cmp    byte [rax], 0
  sete   cl
  cmp    rax, rdi
  setg   dl
  and    ecx, edx
  test   ecx, ecx
  jz     .after_if_1
  dec    rax
.after_if_1:
  cmp    rax, rdi
  jz     .end
  push   rax
  push   rdi
  mov    rdi, rax
  CALL(Strlen_asm)
  lea    rcx, [rax+1]
  pop    rdi
  pop    rax
  xor    r8d, r8d
.loop_2:
  mov    dl, byte [rax+r8]
  mov    byte [rdi+r8], dl
  inc    r8
  cmp    r8, rcx
  js     .loop_2
.end:
  ret