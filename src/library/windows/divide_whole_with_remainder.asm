extern _multiply_whole
extern remove_leading_zeroes
extern strlen
extern subtract_whole

section .text
global _divide_whole_with_remainder
_divide_whole_with_remainder:
  ; Input:
  ;   - const char *numerator   -> rcx
  ;   - const char *denominator -> rdx
  ;   - char *res               -> r8
  ;   - size_t bufsize          -> r9, set this to be strlen(numerator) + strlen(denominator) + 2
  ;   - char *buf               -> stack, allocate 5 * bufsize + 10 * (strlen(denominator) + 2) + 3 bytes for this using calloc.

  ; Output:
  ;   - Modular division of numerator / denominator in res
  ;   - A pointer to a part of buf pointing to the division remainder.

  ; Registers used:
  ;   - rax
  ;   - rbx
  ;   - r10
  ;   - r11
  ;   - rdi
  ;   - rsi
  ;   - r12
  ;   - r13
  ;   - r14
  ;   - r15

  mov    r10, qword [rsp+40] ; Retrieve the last argument from the stack.
  push   rbx
  push   rdi
  push   rsi
  push   r12
  push   r13
  push   r14
  push   r15
  call   strlen
  push   rax
  push   rcx
  mov    rcx, rdx
  call   strlen
  mov    rbx, rax
  pop    rcx
  pop    rax
  xor    r11, r11
  lea    r14, [rbx*9]
  add    r14, rbx
  lea    r15, [r9*5]
  add    r15, r14
  add    r15, 20
.loop_1:
  mov    byte [r10+r15], r11b
  add    byte [r10+r15], 48
  push   rcx
  push   r8
  push   r9
  push   r10
  push   rax
  push   rbx
  push   r11
  push   rdi
  push   r12
  push   r13
  push   r14
  push   r15
  lea    rcx, [r10+r15]
  lea    r8, [r9*5]
  add    r8, r10
  lea    rdi, [rbx+2]
  push   rax
  push   r8
  mov    rax, r11
  push   rdx
  mul    rdi
  pop    rdx
  mov    rsi, rax
  pop    r8
  pop    rax
  add    r8, rsi
  mov    r12, r9
  mov    r9, r10
  add    r10, r12
  push   r10 ; Passing the 5th argument via stack
  push   r9
  push   r8
  push   rdx
  push   rcx 
  call   _multiply_whole
  pop    rcx
  pop    rdx
  pop    r8
  pop    r9
  pop    r10
  mov    rcx, r8
  call   strlen
  lea    rsi, [rax-1]
  pop    r15
  pop    r14
  pop    r13
  pop    r12
  pop    rdi
  pop    r11
  pop    rbx
  pop    rax
  pop    r10
  pop    r9
  pop    r8
  pop    rcx
  cmp    rsi, rbx
  jge    .after_if_1
  lea    rsi, [rbx+2]
  mov    r12, rsi
  push   rax
  push   r8
  mov    rax, r11
  push   rdx
  mul    r12
  pop    rdx
  mov    rsi, rax
  pop    r8
  pop    rax
  lea    rdi, [rbx+rsi]
  xor    r13, r13
.loop_2:
  dec    rdi
  lea    r12, [r9*5]
  add    r12, rdi
  mov    r13b, byte [r10+r12]
  mov    byte [r10+r12+1], r13b
  cmp    rdi, rsi
  jg     .loop_2
  lea    rdi, [r9*5]
  add    rdi, rsi
  mov    byte [r10+rdi], 48
.after_if_1:
  xor    rdi, rdi
.loop_3:
  mov    byte [r10+rdi], 0
  lea    rsi, [rdi+r9] ; potential optimization
  mov    byte [r10+rsi], 0 ; move rsib out of loop and
  inc    rdi ; increment it
  lea    r12, [rbx+2]
  cmp    rdi, r12
  js     .loop_3
  inc    r11
  cmp    r11, 10
  js     .loop_1
  mov   r11b, byte [rcx]
  lea   rdi, [r9*3]
  add   rdi, r10
  mov   byte [rdi], r11b
  mov   byte [rdi+1], 0
  xor   rsi, rsi
.loop_4:
  xor   r11, r11
  mov   byte [r10+r15+2], r11b
.loop_5:
  xor   rdi, rdi
.loop_6:
  lea   r12, [r9*2]
  add   r12, rdi
  mov   byte [r10+r12], 0
  inc   rdi
  lea   r12, [rax+2]
  cmp   rdi, r12
  js    .loop_6
  push  r15
  push  r13
  push  r14
  push  rcx
  push  rdx
  push  r8
  push  rax
  push  rbx
  push  r11
  push  rsi
  push  r12
  push  r10
  push  r9
  lea   rcx, [r9*3]
  add   rcx, r10
  lea   rdx, [r9*5]
  add   rdx, r10
  push  rax
  push  r8
  lea   rax, [rbx+2]
  push  rdx
  mul   r11
  pop   rdx
  add   rdx, rax
  pop   r8
  pop   rax
  lea   r8, [r9*2]
  add   r8, r10
  call  subtract_whole
  pop   r9
  pop   r10
  lea   r12, [r9*4]
  add   r12, r10
  mov   rcx, r8
  mov   rdx, r12
  push  r9
  push  r10
  push  r12
  push  r13
  call  remove_leading_zeroes
  pop   r13
  pop   r12
  pop   r10
  mov   rcx, r12
  call  strlen
  mov   r15, rax
  pop   r9
  pop   r12
  pop   rsi
  pop   r11
  pop   rbx
  pop   rax
  pop   r8
  pop   rdx
  pop   rcx
  pop   r14
  pop   r13
  xor   rdi, rdi
.loop_7:
  lea   r13, [r9*4]
  add   r13, rdi
  lea   r14, [r9*2]
  add   r14, rdi
  mov   r13b, byte [r10+r13]
  mov   byte [r10+r14], r13b
  inc   rdi
  cmp   rdi, r15
  js    .loop_7
  pop   r15
  lea   r12, [r9*2]
  cmp   byte [r10+r12], 2DH
  jz    .after_loop_5
  mov   byte [r10+r15+2], r11b
  xor   rdi, rdi
.loop_8:
  mov   byte [r10+rdi], 0
  inc   rdi
  lea   r12, [rbx+2]
  cmp   rdi, r12
  js    .loop_8
  push  rax
  push  rcx
  push  r9
  lea   rcx, [r9*5]
  add   rcx, r10
  push  r8
  lea   rax, [rbx+2]
  push  rdx
  mul   r11
  pop   rdx
  add   rcx, rax
  pop   r8
  push  r11
  call  strlen
  pop   r11
  mov   r12, rax
  pop   r9
  pop   rcx
  pop   rax
  xor   rdi, rdi
.loop_9:
  lea   r13, [r9*5]
  add   r13, rdi
  push  rax
  push  r8
  lea   rax, [rbx+2]
  push  rdx
  mul   r11
  pop   rdx
  add   r13, rax
  pop   r8
  pop   rax
  mov   r14b, byte [r10+r13]
  mov   byte [r10+rdi], r14b
  inc   rdi
  cmp   rdi, r12
  js    .loop_9
  inc   r11
  cmp   r11, 10
  js    .loop_5
.after_loop_5:
  xor   rdi, rdi
.loop_10:
  lea   r12, [r9*2]
  add   r12, rdi
  mov   byte [r10+r12], 0
  inc   rdi
  lea   r12, [rax+2]
  cmp   rdi, r12
  js    .loop_10
  mov   r14b, byte [r10+r15+2]
  mov   byte [r8+rsi], r14b
  add   byte [r8+rsi], 48
  push  rcx
  push  rdx
  push  r8
  push  rax
  push  rbx
  push  r9
  push  r10
  push  r11
  push  rsi
  lea   rcx, [r9*3]
  add   rcx, r10
  mov   rdx, r10
  lea   r8, [r9*2]
  add   r8, r10
  push  r12
  push  r13
  push  r14
  call  subtract_whole ; check push and pop of regs
  pop   r14
  pop   r13
  pop   r12
  mov   rcx, r8
  call  strlen
  mov   rdi, rax
  pop   rsi
  pop   r11
  pop   r10
  pop   r9
  pop   rbx
  pop   rax
  pop   r8
  pop   rdx
  pop   rcx
  xor   r12, r12
.loop_11:
  lea   r13, [r9*2]
  add   r13, r12
  mov   r13b, byte [r10+r13]
  lea   r14, [r9*3]
  add   r14, r12
  mov   byte [r10+r14], r13b
  inc   r12
  cmp   r12, rdi
  js    .loop_11
  lea   r12, [rax-1]
  lea   r13, [r9*3]
  add   r13, rdi
  lea   r14, [r9*3]
  add   r14, r10
  cmp   rsi, r12
  jle   .add_whole_else_1
  mov   byte [r10+r13], 48
  jmp   .after_add_else_1
.add_whole_else_1:
  mov   r12b, byte [rcx+rsi+1]
  mov   byte [r10+r13], r12b
.after_add_else_1:
  lea   r12, [r9*3]
  add   r12, rdi
  mov   byte [r10+r12+1], 0
  inc   rsi
  cmp   rsi, rax
  js    .loop_4
  mov   byte [r8+rax], 0
  mov   rax, r14
  pop   r15
  pop   r14
  pop   r13
  pop   r12
  pop   rsi
  pop   rdi
  pop   rbx
  ret