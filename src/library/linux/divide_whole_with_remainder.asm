extern _multiply_whole
extern remove_leading_zeroes
extern strlen
extern subtract_whole

section .text
global _divide_whole_with_remainder
_divide_whole_with_remainder:
  ; Input:
  ;   - const char *numerator -> rdi
  ;   - const char *denominator -> rsi
  ;   - char *res -> rdx
  ;   - size_t bufsize -> rcx, set this to be strlen(numerator) + strlen(denominator) + 2
  ;   - char *buf -> r8, allocate 5 * bufsize + 10 *  (strlen(denominator) + 2) + 3 bytes for this using calloc.

  ; Output:
  ;   - Modular division of numerator / denominator in res
  ;   - A pointer to a part of buf pointing to the division remainder.

  ; Registers used:
  ;   - rax
  ;   - rbx
  ;   - r9
  ;   - r10
  ;   - r11
  ;   - r12
  ;   - r13
  ;   - r14
  ;   - r15

  push   rbx
  push   r12
  push   r13
  push   r14
  push   r15
  push   rcx
  call   strlen
  pop    rcx
  push   rax
  push   rdi
  push   rcx
  mov    rdi, rsi
  call   strlen
  mov    rbx, rax
  pop    rcx
  pop    rdi
  pop    rax
  xor    r9, r9
  lea    r14, [rbx * 9]
  add    r14, rbx
  lea    r15, [rcx * 5]
  add    r15, r14
  add    r15, 20
.loop_1:
  mov    byte [r8 + r15], r9b
  add    byte [r8 + r15], 48
  push   rdi
  push   rdx
  push   rcx
  push   r8
  push   rax
  push   rbx
  push   r9
  push   r10
  push   r12
  push   r13
  push   r14
  push   r15
  lea    rdi, [r8 + r15]
  lea    rdx, [rcx * 5]
  add    rdx, r8
  lea    r10, [rbx + 2]
  push   rax
  push   rdx
  mov    rax, r9
  mul    r10
  mov    r11, rax
  pop    rdx
  pop    rax
  add    rdx, r11
  mov    r12, rcx
  mov    rcx, r8
  add    r8, r12
  call   _multiply_whole
  mov    rdi, rdx
  call   strlen
  lea    r11, [rax - 1]
  pop    r15
  pop    r14
  pop    r13
  pop    r12
  pop    r10
  pop    r9
  pop    rbx
  pop    rax
  pop    r8
  pop    rcx
  pop    rdx
  pop    rdi
  cmp    r11, rbx
  jge    .after_if_1
  lea    r11, [rbx + 2]
  mov    r12, r11
  push   rax
  push   rdx
  mov    rax, r9
  mul    r12
  mov    r11, rax
  pop    rdx
  pop    rax
  lea    r10, [rbx + r11]
  xor    r13, r13
.loop_2:
  dec    r10
  lea    r12, [rcx * 5]
  add    r12, r10
  mov    r13b, byte [r8 + r12]
  mov    byte [r8 + r12 + 1], r13b
  cmp    r10, r11
  jg     .loop_2
  lea    r10, [rcx * 5]
  add    r10, r11
  mov    byte [r8 + r10], 48
.after_if_1:
  xor    r10, r10
.loop_3:
  mov    byte [r8 + r10], 0
  lea    r11, [r10 + rcx] ; potential optimization
  mov    byte [r8 + r11], 0 ; move r11b out of loop and
  inc    r10 ; increment it
  lea    r12, [rbx + 2]
  cmp    r10, r12
  js     .loop_3
  inc    r9
  cmp    r9, 10
  js     .loop_1
  mov   r9b, byte [rdi]
  lea   r10, [rcx * 3]
  add   r10, r8
  mov   byte [r10], r9b
  mov   byte [r10 + 1], 0
  xor   r11, r11
.loop_4:
  xor   r9, r9
  mov   byte [r8 + r15 + 2], r9b
.loop_5:
  xor   r10, r10
.loop_6:
  lea   r12, [rcx * 2]
  add   r12, r10
  mov   byte [r8 + r12], 0
  inc   r10
  lea   r12, [rax + 2]
  cmp   r10, r12
  js    .loop_6
  push  r15
  push  rdi
  push  rsi
  push  rdx
  push  rax
  push  rbx
  push  r9
  push  r11
  push  r8
  push  rcx
  lea   rdi, [rcx * 3]
  add   rdi, r8
  lea   rsi, [rcx * 5]
  add   rsi, r8
  push  rax
  push  rdx
  lea   rax, [rbx + 2]
  mul   r9
  add   rsi, rax
  pop   rdx
  pop   rax
  lea   rdx, [rcx * 2]
  add   rdx, r8
  call  subtract_whole
  pop   rcx
  pop   r8
  lea   r12, [rcx * 4]
  add   r12, r8
  mov   rdi, rdx
  mov   rsi, r12
  push  rcx
  push  r8
  call  remove_leading_zeroes
  pop   r8
  mov   rdi, r12
  call  strlen
  mov   r15, rax
  pop   rcx
  pop   r11
  pop   r9
  pop   rbx
  pop   rax
  pop   rdx
  pop   rsi
  pop   rdi
  xor   r10, r10
.loop_7:
  lea   r13, [rcx * 4]
  add   r13, r10
  lea   r14, [rcx * 2]
  add   r14, r10
  mov   r13b, byte [r8 + r13]
  mov   byte [r8 + r14], r13b
  inc   r10
  cmp   r10, r15
  js    .loop_7
  pop   r15
  lea   r12, [rcx * 2]
  cmp   byte [r8 + r12], 2DH
  jz    .after_loop_5
  mov   byte [r8 + r15 + 2], r9b
  xor   r10, r10
.loop_8:
  mov   byte [r8 + r10], 0
  inc   r10
  lea   r12, [rbx + 2]
  cmp   r10, r12
  js    .loop_8
  push  rax
  push  rdi
  push  rcx
  lea   rdi, [rcx * 5]
  add   rdi, r8
  push  rdx
  lea   rax, [rbx + 2]
  mul   r9
  add   rdi, rax
  pop   rdx
  call  strlen
  mov   r12, rax
  pop   rcx
  pop   rdi
  pop   rax
  xor   r10, r10
.loop_9:
  lea   r13, [rcx * 5]
  add   r13, r10
  push  rax
  push  rdx
  lea   rax, [rbx + 2]
  mul   r9
  add   r13, rax
  pop   rdx
  pop   rax
  mov   r14b, byte [r8 + r13]
  mov   byte [r8 + r10], r14b
  inc   r10
  cmp   r10, r12
  js    .loop_9
  inc   r9
  cmp   r9, 10
  js    .loop_5
.after_loop_5:
  xor   r10, r10
.loop_10:
  lea   r12, [rcx * 2]
  add   r12, r10
  mov   byte [r8 + r12], 0
  inc   r10
  lea   r12, [rax + 2]
  cmp   r10, r12
  js    .loop_10
  mov   r14b, byte [r8 + r15 + 2]
  mov   byte [rdx + r11], r14b
  add   byte [rdx + r11], 48
  push  rdi
  push  rsi
  push  rdx
  push  rax
  push  rbx
  push  rcx
  push  r8
  push  r9
  push  r11
  lea   rdi, [rcx * 3]
  add   rdi, r8
  mov   rsi, r8
  lea   rdx, [rcx * 2]
  add   rdx, r8
  call  subtract_whole
  mov   rdi, rdx
  call  strlen
  mov   r10, rax
  pop   r11
  pop   r9
  pop   r8
  pop   rcx
  pop   rbx
  pop   rax
  pop   rdx
  pop   rsi
  pop   rdi
  xor   r12, r12
.loop_11:
  lea   r13, [rcx * 2]
  add   r13, r12
  mov   r13b, byte [r8 + r13]
  lea   r14, [rcx * 3]
  add   r14, r12
  mov   byte [r8 + r14], r13b
  inc   r12
  cmp   r12, r10
  js    .loop_11
  lea   r12, [rax - 1]
  lea   r13, [rcx * 3]
  add   r13, r10
  lea   r14, [rcx * 3]
  add   r14, r8
  cmp   r11, r12
  jle   .add_whole_else_1
  mov   byte [r8 + r13], 48
  jmp   .after_add_else_1
.add_whole_else_1:
  mov   r12b, byte [rdi + r11 + 1]
  mov   byte [r8 + r13], r12b
.after_add_else_1:
  lea   r12, [rcx * 3]
  add   r12, r10
  mov   byte [r8 + r12 + 1], 0
  inc   r11
  cmp   r11, rax
  js    .loop_4
  mov   byte [rdx + rax], 0
  mov   rax, r14
  pop   r15
  pop   r14
  pop   r13
  pop   r12
  pop   rbx
  ret