extern strlen

section .text
global subtract_whole
subtract_whole:
  ; Input:
  ;   - char *a -> rcx
  ;   - char *b -> rdx
  ;   - char *res -> r8, r8 will contain a - b

  ; Registers used:
  ;   - rax
  ;   - rbx
  ;   - r9
  ;   - r10
  ;   - r11
  ;   - r12
  ;   - r13
  ;   - r14

  push   rbx
  push   r12
  push   r13
  push   r14
  call   strlen
  mov    r12, rax
  push   rcx
  mov    rcx, rdx
  call   strlen
  mov    r10, rax
  pop    rcx
  mov    rax, r12
  dec    r12
  lea    r13, [r10-1]
  cmp    r10, rax
  cmovg  rax, r10
  lea    r10, [rax-1]
  xor    r9d, r9d
.loop_1:
  mov    r11b, 48
  mov    bl, 48
  lea    r14, [r12+1]
  test   r14, r14
  jle    .after_if_1
  mov    r11b, byte [rcx+r12]
  dec    r12
.after_if_1:
  lea    r14, [r13+1]
  test   r14, r14
  jle    .after_if_2
  mov    bl, byte [rdx+r13]
  dec    r13
.after_if_2:
  sub    r11b, r9b
  cmp    r11b, bl
  js     .else_1
  mov    byte [r8+r10], r11b
  sub    byte [r8+r10], bl
  add    byte [r8+r10], 48
  jmp    .after_else_1
.else_1:
  mov    byte [r8+r10], 58
  add    byte [r8+r10], r11b
  sub    byte [r8+r10], bl
.after_else_1:
  cmp    r11b, bl
  setl   r9b
  mov    r11, r10
  dec    r10
  test   r11, r11
  jg     .loop_1
  mov    byte [r8+rax], 0
  cmp    byte [r8], 48
  jge    .after_if_3
  mov    r10, 1
.loop_2:
  mov    r11b, byte [r8+r10]
  mov    byte [r8+r10-1], r11b
  inc    r10
  cmp    r10, rax
  js     .loop_2
  mov    byte [r8+rax-1], 0
  mov    r9b, 1
.after_if_3:
  push   rcx
  push   r11
  mov    rcx, r8
  call   strlen
  pop    r11
  pop    rcx
  test   r9b, r9b
  jz     .ret
  mov    byte [r8+rax+1], 0
  lea    r10, [rax-1]
  xor    r9d, r9d
.loop_3:
  mov    r12b, byte [r8+r10]
  cmp    r12b, 48
  jg     .else_2
  test   r9b, r9b
  jz     .after_else_2
  mov    r12b, 57
  jmp    .after_else_2
.else_2:
  mov    r14b, 106
  sub    r14b, r9b
  sub    r14b, r12b
  mov    r12b, r14b
  mov    r9b, 1
.after_else_2:
  mov    byte [r8+r10+1], r12b
  mov    r11, r10
  dec    r10
  test   r11, r11
  jg     .loop_3
  mov    byte [r8], 2DH
.ret:
  pop    r14
  pop    r13
  pop    r12
  pop    rbx
  ret