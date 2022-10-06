extern strlen

section .text
global add_whole
add_whole:
; optimized with the help of https://codereview.stackexchange.com/questions/279863/add-two-huge-base-10-numbers.
  push   rbx              ; The only callee-saved register to preserve

  push   rdx              ; (1)
  push   rsi              ; (2)
  push   rdi              ; (3)
  call   strlen           ; -> RAX is strlen(a)
  mov    ebx, eax         ; For sure less than 4GB
  mov    rdi, [rsp+8]
  call   strlen           ; -> RAX is strlen(b)
  pop    rdi              ; (3)
  pop    rsi              ; (2)
  pop    rdx              ; (1)

  ; At RDI are RBX bytes, at RSI are RAX bytes

  cmp    ebx, eax
  jae    .NoSwap
  xchg   rdi, rsi         ; Make (RDI:RBX) refer to the longer input
  xchg   ebx, eax
.NoSwap:
  mov    ecx, eax         ; RAX is length of the shorter input
  lea    r8, [rdi+rbx]    ; R8 points at the terminating zero
  lea    r9, [rsi+rax]    ; R9 points at the terminating zero
  add    rdx, rbx         ; RBX is length of the longer input
  push   rdx              ; (4) "in case there's a final carry"
  xor    ebx, ebx         ; BL is carry [0,1]
  mov    [rdx], bl        ; Zero-terminating the result
  jecxz  .NoLoopA

.LoopA:                   ; Deals with the common positions
  movzx  eax, byte [r8-1]
  add    al, [r9-1]
  sub    al, '0'
  add    al, bl           ; Plus carry
  xor    ebx, ebx         ; Clear carry
  cmp    al, '9'
  jbe    .CharOK
  sub    al, 10
  inc    ebx              ; Set carry
.CharOK:
  mov    [rdx-1], al
  dec    r9
  dec    r8
  dec    rdx
  dec    rcx
  jnz    .LoopA

.NoLoopA:
  cmp    r8, rdi
  jna    .NoLoopB

.LoopB:                   ; Deals with remainder of the longer input
  movzx  eax, byte [r8-1]
  add    al, bl           ; Plus carry
  xor    ebx, ebx         ; Clear carry
  cmp    al, '9'
  jbe    .CharOK_
  sub    al, 10
  inc    ebx              ; Set carry
.CharOK_:
  mov    [rdx-1], al
  dec    r8
  dec    rdx
  cmp    r8, rdi
  ja     .LoopB

.NoLoopB:
  pop    rcx              ; (4)
  test   bl, bl           ; Check for a final carry.
  jz     .Done
.CopyUp:
  mov    al, [rcx]
  mov    [rcx+rbx], al    ; RBX=1
  dec    rcx
  cmp    rcx, rdx
  jae    .CopyUp
  mov    byte [rdx], '1'

.Done:
  pop    rbx              ; Unchanged RDX is ptr to zero-terminated result
  ret