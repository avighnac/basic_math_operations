extern strlen_asm

section .text
global subtract_whole
subtract_whole:
  ; Input:
  ;   - char *a -> rdi
  ;   - char *b -> rsi
  ;   - char *res -> rdx, rdx will contain a - b

  ; Registers used:
  ;   - rax
  ;   - rbx
  ;   - rcx
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11
  ;   - r12

  push   rbx
  push   r12
  call   strlen_asm wrt ..plt
  mov    r10, rax
  push   rdi
  mov    rdi, rsi
  call   strlen_asm wrt ..plt
  mov    r8, rax
  pop    rdi
  mov    rax, r10
  dec    r10
  lea    r11, [r8-1]
  cmp    r8, rax
  cmovg  rax, r8
  lea    r8, [rax-1]
  xor    ecx, ecx
.loop_1:
  mov    r9b, 48
  mov    bl, 48
  lea    r12, [r10+1]
  test   r12, r12
  jle    .after_if_1
  mov    r9b, byte [rdi+r10]
  dec    r10
.after_if_1:
  lea    r12, [r11+1]
  test   r12, r12
  jle    .after_if_2
  mov    bl, byte [rsi+r11]
  dec    r11
.after_if_2:
  sub    r9b, cl
  cmp    r9b, bl
  js     .else_1
  mov    byte [rdx+r8], r9b
  sub    byte [rdx+r8], bl
  add    byte [rdx+r8], 48
  jmp    .after_else_1
.else_1:
  mov    byte [rdx+r8], 58
  add    byte [rdx+r8], r9b
  sub    byte [rdx+r8], bl
.after_else_1:
  cmp    r9b, bl
  setl   cl
  mov    r9, r8
  dec    r8
  test   r9, r9
  jg     .loop_1
  mov    byte [rdx+rax], 0
  cmp    byte [rdx], 48
  jge    .after_if_3
  mov    r8, 1
.loop_2:
  mov    r9b, byte [rdx+r8]
  mov    byte [rdx+r8-1], r9b
  inc    r8
  cmp    r8, rax
  js     .loop_2
  mov    byte [rdx+rax-1], 0
  mov    cl, 1
.after_if_3:
  push   rdi
  push   rcx
  mov    rdi, rdx
  call   strlen_asm wrt ..plt
  pop    rcx
  pop    rdi
  test   cl, cl
  jz     .ret
  mov    byte [rdx+rax+1], 0
  lea    r8, [rax-1]
  xor    ecx, ecx
.loop_3:
  mov    r10b, byte [rdx+r8]
  cmp    r10b, 48
  jg     .else_2
  test   cl, cl
  jz     .after_else_2
  mov    r10b, 57
  jmp    .after_else_2
.else_2:
  mov    r12b, 106
  sub    r12b, cl
  sub    r12b, r10b
  mov    r10b, r12b
  mov    cl, 1
.after_else_2:
  mov    byte [rdx+r8+1], r10b
  mov    r9, r8
  dec    r8
  test   r9, r9
  jg     .loop_3
  mov    byte [rdx], 2DH
.ret:
  pop    r12
  pop    rbx
  ret