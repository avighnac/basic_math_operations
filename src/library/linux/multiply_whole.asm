extern  _multiply_whole
extern  asmalloc
extern  strlen

section .text
global multiply_whole
multiply_whole:
  push  rbx
  push  r12
  push  r13
  push  rdx
  mov   rbx, rdi     ; Moving input variables
  mov   r12, rsi     ; Moving input variables
  call  strlen       ; Calling strlen on a
  lea   r13, [rax+1]
  mov   rdi, r12
  call  strlen       ; Calling strlen on b
  add   r13, rax     ; r13 = a_len + b_len + 1
  mov   rdi, r13
  call  asmalloc
  mov   r8, rax
  mov   rdi, r13
  push  r8
  call  asmalloc
  pop   r8
  mov   rcx, rax
  mov   rdi, rbx
  mov   rsi, r12
  pop   rdx
  push  r13
  push  r8
  push  rcx
  call  _multiply_whole
  pop   rcx
  pop   r8
  pop   r13
  mov   rax, 11
  mov   rdi, rcx
  mov   rsi, r13
  syscall
  mov   rax, 11
  mov   rdi, r8
  mov   rsi, r13
  syscall
  pop   r13
  pop   r12
  pop   rbx
  ret