extern strlen

section .text
global add_whole
add_whole:
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
  ;   - r13
  ;   - r14
  
  push   r12
  push   r13
  push   r14
  call   strlen
  push   rax
  push   rdi
  mov    rdi, rsi
  call   strlen
  mov    r8, rax
  pop    rdi
  pop    rax
  mov    r9, r8
  cmp    rax, r8
  cmovnc r9, rax
  xor    r10b, r10b
  xor    rcx, rcx
.loop_1:
  lea    r13, [rcx + 1]
  mov    r11b, 48
  mov    r12b, r11b
  cmp    rax, r13
  js     .after_if_1
  lea    r14, [rdi + rax]
  sub    r14, rcx
  dec    r14
  mov    r11b, byte[r14]
.after_if_1:
  cmp    r8, r13
  js     .after_if_2
  lea    r14, [rsi + r8]
  sub    r14, rcx
  dec    r14
  mov    r12b, byte[r14]
.after_if_2:
  mov    r13b, r11b
  add    r13b, r12b
  sub    r13b, 48
  test   r10b, r10b
  jz     .after_if_3
  xor    r10b, r10b
  inc    r13b
.after_if_3:
  cmp    r13b, 57
  jle    .after_if_4
  sub    r13b, 10
  mov    r10b, 1
.after_if_4:
  mov    byte[rdx + rcx], r13b
  inc    rcx
  cmp    rcx, r9
  js     .loop_1
  test   r10b, r10b
  jz     .after_if_5
  mov    byte[rdx + rcx], 49
  inc    r9
.after_if_5:
  xor    rcx, rcx
  mov    r11, r9
  shr    r11, 1
.loop_2:
  lea    r12, [rdx + r9]
  sub    r12, rcx
  dec    r12
  mov    r8b, byte[rdx + rcx]
  mov    r10b, byte[r12]
  mov    byte[rdx + rcx], r10b
  mov    byte[r12], r8b
  inc    rcx
  cmp    rcx, r11
  js     .loop_2
  mov    byte[rdx + r9], 0
  pop    r14
  pop    r13
  pop    r12
  ret