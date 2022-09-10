extern strlen

section .text
global add_whole_same_length
add_whole_same_length:
  ; Input:
  ;   - char *a -> rdi
  ;   - char *b -> rsi
  ;   - char *res -> rdx

  ; Registers used:
  ;   - rax
  ;   - rcx
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11
  ;   - r12

  push   r12
  call   strlen
  lea    rcx, [rax - 1]
  xor    r11, r11
  xor    r10b, r10b
_add_whole_same_length_loop_1:
  mov    r12b, byte[rdi + rcx]
  add    r12b, byte[rsi + rcx]
  sub    r12b, 48
  test   r10b, r10b
  jz     _after_add_whole_same_length_if_1
  xor    r10b, r10b
  inc    r12b
_after_add_whole_same_length_if_1:
  cmp    r12b, 57
  jle    _after_add_whole_same_length_if_2
  mov    r10b, 1
  sub    r12b, 10
_after_add_whole_same_length_if_2:
  mov    byte[rdx + r11], r12b
  inc    r11
  mov    r8, rcx
  dec    rcx
  cmp    r8, 0
  jg     _add_whole_same_length_loop_1
  test   r10b, r10b
  jz     _after_add_whole_same_length_if_3
  mov    byte[rdx + r11], 49
  inc    rax
_after_add_whole_same_length_if_3:
  xor    r11, r11
  mov    rcx, rax
  shr    rcx, 1
_add_whole_same_length_loop_2:
  mov    r8b, byte[rdx + r11]
  mov    r12, rax
  sub    r12, r11
  lea    r12, [r12 + rdx - 1]
  mov    r9b, byte[r12]
  mov    byte[rdx + r11], r9b
  mov    byte[r12], r8b
  inc    r11
  cmp    r11, rcx
  js     _add_whole_same_length_loop_2
  mov    byte[rdx + rax], 0
  pop    r12
  ret