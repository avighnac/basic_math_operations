extern strlen

section .text
global subtract_whole_same_length
subtract_whole_same_length:
  ; Input:
  ;   - char *a -> rdi
  ;   - char *b -> rsi
  ;   - char *res -> rdx, will contain a - b
  ; strlen(a) has to be equal to strlen(b)

  ; Registers used:
  ;   - rax
  ;   - rcx
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11

  call   strlen
  xor    cl, cl
  lea    r8, [rax - 1]
_subtract_whole_same_length_loop_1:
  mov    r9b, byte [rdi + r8]
  sub    r9b, cl
  cmp    r9b, byte [rsi + r8]
  js     _subtract_whole_same_length_else_1
  mov    byte [rdx + r8], r9b
  mov    r10b, byte [rsi + r8]
  sub    byte [rdx + r8], r10b
  add    byte [rdx + r8], 48
  jmp    _after_subtract_whole_same_length_else_1
_subtract_whole_same_length_else_1:
  mov    byte [rdx + r8], 58
  add    byte [rdx + r8], r9b
  mov    r10b, byte [rsi + r8]
  sub    byte [rdx + r8], r10b
_after_subtract_whole_same_length_else_1:
  xor    cl, cl
  cmp    r9b, byte [rsi + r8]
  setl   cl
  dec    r8
  lea    r9, [r8 + 1]
  cmp    r9, 0
  jg     _subtract_whole_same_length_loop_1
  mov    byte [rdx + rax], 0
  cmp    byte [rdx], 48
  jge    _after_subtract_whole_same_length_if_2
  mov    r8, 1
_subtract_whole_same_length_loop_2:
  mov    r9b, byte [rdx + r8]
  mov    byte [rdx + r8 - 1], r9b
  inc    r8
  cmp    r8, rax
  js     _subtract_whole_same_length_loop_2
  mov    byte [rdx + rax - 1], 0
  mov    cl, 1
_after_subtract_whole_same_length_if_2:
  push   rdi
  push   rcx
  mov    rdi, rdx
  call   strlen
  pop    rcx
  pop    rdi
  test   cl, cl
  jz     _subtract_whole_same_length_return
  mov    byte [rdx + rax + 1], 0
  lea    r8, [rax - 1]
  xor    cl, cl
_subtract_whole_same_length_loop_3:
  mov    r10b, byte [rdx + r8]
  cmp    r10b, 48
  jg     _subtract_whole_same_length_else_2
  test   cl, cl
  jz     _after_subtract_whole_same_length_else_2
  mov    r10b, 57
  jmp    _after_subtract_whole_same_length_else_2
_subtract_whole_same_length_else_2:
  mov    r11b, 106
  sub    r11b, cl
  sub    r11b, r10b
  mov    r10b, r11b
  mov    cl, 1
_after_subtract_whole_same_length_else_2:
  mov    byte [rdx + r8 + 1], r10b
  mov    r9, r8
  dec    r8
  test   r9, r9
  jg     _subtract_whole_same_length_loop_3
  mov    byte [rdx], 2DH
_subtract_whole_same_length_return: ret