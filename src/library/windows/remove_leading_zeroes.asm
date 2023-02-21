<<<<<<< HEAD
extern strlen

section .text
global remove_leading_zeroes
remove_leading_zeroes:
  ; Input:
  ;   - const char *string -> rcx
  ;   - char *res -> rdx

  ; Registers used:
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11
  ;   - r12
  ;   - r13

  push   r12
  push   r13
  call   strlen
  lea    r12, [rax-1]
  xor    r10b, r10b
  cmp    byte [rcx], 2DH
  sete   r8b
  movzx  r11, r8b
  mov    r9, r11
  test   r8b, r8b
  jz     .loop_1
  mov    byte [rdx], 2DH
.loop_1:
  cmp    byte [rcx+r9], 48
  jz     .after_if_1
  mov    r10b, 1
.after_if_1:
  cmp    r9, r12
  sete   r13b
  or     r13b, r10b
  test   r13b, r13b
  jz     .after_if_2
  mov    r13b, byte [rcx+r9]
  mov    byte [rdx+r11], r13b
  inc    r11
.after_if_2:
  inc    r9
  cmp    r9, rax
  js     .loop_1
  mov    byte [rdx+r11], 0
  pop    r13
  pop    r12
  ret
global remove_leading_zeroes_inplace
remove_leading_zeroes_inplace:
  ; Input:
  ;   - char *number -> rcx, removes the leading zeroes in [number] in-place.
  ;                          Note that [number] has to be non negative.

  ; Registers used:
  ;   - rax
  ;   - r8d
  ;   - r9d
  ;   - r10

  lea    rax, [rcx-1]
.loop_1:
  inc    rax
  cmp    byte [rax], 48
  jz     .loop_1
  cmp    byte [rax], 0
  sete   r8b
  cmp    rax, rcx
  setg   r9b
  and    r8d, r9d
  test   r8d, r8d
  jz     .after_if_1
  dec    rax
.after_if_1:
  cmp    rax, rcx
  jz     .end
  push   rax
  push   rcx
  mov    rcx, rax
  call   strlen
  lea    r8, [rax+1]
  pop    rcx
  pop    rax
  xor    r10d, r10d
.loop_2:
  mov    r9b, byte [rax+r10]
  mov    byte [rcx+r10], r9b
  inc    r10
  cmp    r10, r8
  js     .loop_2
.end:
=======
extern strlen

section .text
global remove_leading_zeroes
remove_leading_zeroes:
  ; Input:
  ;   - const char *string -> rcx
  ;   - char *res -> rdx

  ; Registers used:
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11
  ;   - r12
  ;   - r13

  push   r12
  push   r13
  call   strlen
  lea    r12, [rax-1]
  xor    r10b, r10b
  cmp    byte [rcx], 2DH
  sete   r8b
  movzx  r11, r8b
  mov    r9, r11
  test   r8b, r8b
  jz     .loop_1
  mov    byte [rdx], 2DH
.loop_1:
  cmp    byte [rcx+r9], 48
  jz     .after_if_1
  mov    r10b, 1
.after_if_1:
  cmp    r9, r12
  sete   r13b
  or     r13b, r10b
  test   r13b, r13b
  jz     .after_if_2
  mov    r13b, byte [rcx+r9]
  mov    byte [rdx+r11], r13b
  inc    r11
.after_if_2:
  inc    r9
  cmp    r9, rax
  js     .loop_1
  mov    byte [rdx+r11], 0
  pop    r13
  pop    r12
  ret
global remove_leading_zeroes_inplace
remove_leading_zeroes_inplace:
  ; Input:
  ;   - char *number -> rcx, removes the leading zeroes in [number] in-place.
  ;                          Note that [number] has to be non negative.

  ; Registers used:
  ;   - rax
  ;   - r8d
  ;   - r9d
  ;   - r10

  lea    rax, [rcx-1]
.loop_1:
  inc    rax
  cmp    byte [rax], 48
  jz     .loop_1
  cmp    byte [rax], 0
  sete   r8b
  cmp    rax, rcx
  setg   r9b
  and    r8d, r9d
  test   r8d, r8d
  jz     .after_if_1
  dec    rax
.after_if_1:
  cmp    rax, rcx
  jz     .end
  push   rax
  push   rcx
  mov    rcx, rax
  call   strlen
  lea    r8, [rax+1]
  pop    rcx
  pop    rax
  xor    r10d, r10d
.loop_2:
  mov    r9b, byte [rax+r10]
  mov    byte [rcx+r10], r9b
  inc    r10
  cmp    r10, r8
  js     .loop_2
.end:
>>>>>>> two/main
  ret