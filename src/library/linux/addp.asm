extern  add_whole
extern  asmalloc
extern  strlen_asm

; This header file still has bugs, for example 3.14^3.14 in arithmetica does not 
; produce the correct result because of addp.asm.
; This is not being used right now.

section .text
global  addp
; Adds two positive rational numbers; stores the result in `rdx`.

; Registers used:
;   - rax
;   - rbx
;   - rcx
;   - r8
;   - r9
;   - r10
;   - r11
;   - r12
;   - r13
;   - r14
;   - r15
addp:

  ; Align the stack.
  push  rbp
  mov   rbp, rsp
  sub   rsp, 40 ; Amount of space to allocate on the stack.

  ; Push some registers that need to be saved.
  push  rbx
  push  r12
  push  r13
  push  r14
  push  r15

  ; Move input to r12, r13, and r15.
  ; This vacates rdi, rsi, and rdx.
  mov   r12, rdi
  mov   r13, rsi
  mov   r15, rdx

  ; Store the lengths of a (rdi) and b (rsi)
  ; in [rbp-8] and [rbp-16] respectively.
  ; Also, store sum+1 in r14
  call  strlen_asm wrt ..plt
  mov   [rbp-8], rax
  lea   r14, [rax+1]
  mov   rdi, r13
  call  strlen_asm wrt ..plt
  add   r14, rax
  mov   [rbp-16], rax

  ; Make two memory allocations with length = r14
  ; Store one memory pointer in [rbp-24],
  ; and the other one in rdx.
  mov   rdi, r14
  call  asmalloc wrt ..plt
  mov   [rbp-24], rax
  mov   rdi, r14
  call  asmalloc wrt ..plt
  mov   rdx, rax

  ; Declare variables ptr1, n1, flag, and i.
  ; - ptr1 = r8
  ; - n1 = r9
  ; - flag = al
  ; - i = ebx
  xor   r8d, r8d ; ptr1 = 0
  xor   r9d, r9d ; n1 = 0
  xor   eax, eax ; flag = 0
  xor   ebx, ebx ; i = 0

  ; Also, move a_len to r10 for the loop.
  mov   r10, [rbp-8]

  ; The first loop that detects the decimal
  ; point in a.
.loop_1:
  ; if (flag) then n1++
  test  al, al
  jz    .after_if_1
  inc   r9
.after_if_1:
  ; if (a[i] == '.') then flag = 1
  ;                  else new_a[ptr1++] = a[i]
  mov   cl, byte [r12+rbx]
  cmp   cl, '.'
  jne   .else_2
  mov   al, 1
  jmp   .after_else_2
.else_2:
  mov   byte [rdx+r8], cl
  inc   r8
.after_else_2:
  inc   rbx
  cmp   rbx, r10
  jb    .loop_1

  ; Exchange rdx and [rbp-24]. Now new_b is in rdx.
  mov   rcx, rdx
  mov   rdx, [rbp-24]
  mov   [rbp-24], rcx

  ; Reset 'flag' and 'i'.
  xor   eax, eax ; flag = 0
  xor   ebx, ebx ; i = 0

  ; Move 'n1' and 'ptr1' to memory.
  mov   [rbp-32], r9
  mov   [rbp-40], r8

  ; Replace r9 and r8 with 'n2' and 'ptr2' respectively.
  xor   r8d, r8d ; ptr2 = 0
  xor   r9d, r9d ; n2 = 0

  ; Move b_len to r10 for the loop.
  mov   r10, [rbp-16]

  ; The second loop that detects the decimal
  ; point in b.
.loop_2:
  test  al, al
  jz    .after_if_2
  inc   r9
.after_if_2:
  mov   cl, byte [r13+rbx]
  cmp   cl, '.'
  jne   .else_3
  mov   al, 1
  jmp   .after_else_3
.else_3:
  mov   byte [rdx+r8], cl
  inc   r8
.after_else_3:
  inc   rbx
  cmp   rbx, r10
  jb    .loop_2

  ; if n1 is 0 and n2 is 0
  test  r9, r9 ; n2
  setz  bl
  xchg  [rbp-32], r9
  test  r9, r9 ; n1
  setz  al
  and   al, bl
  test  al, al
  jz    .after_whole_check

  ; There was no decimal point in either input.
  ; Add them normally and free new_a and new_b.

  ; Free first.
  mov   rax, 11
  mov   rdi, rdx
  syscall
  mov   rax, 11
  mov   rdi, [rbp-24]
  syscall

  ; Now call add_whole
  mov   rdi, r12
  mov   rsi, r13
  mov   rdx, r15
  call  add_whole wrt ..plt

  jmp   .return

.after_whole_check:

  ; We will use rcx for 'displacement'
  mov   rcx, r9      ; displacement = n1
  xor   ebx, ebx     ; Initialize i to 0.
  ; Move n1 - n2 to r10.
  mov   r10, r9
  xchg  [rbp-32], r9 ; r9 = n2
  sub   r10, r9

  cmp   rcx, r9
  jae   .after_if_3
  ; if displacement < n2 then

  mov   rcx, r9       ; displacement = n2
  neg   r10           ; Negate r10 for how many times the loop should run.
  xchg  rdx, [rbp-24] ; Move new_a to rdx.
  xchg  r8, [rbp-40]  ; Move ptr1 to r8.
.loop_3:
  mov   byte [rdx+r8], '0'
  inc   r8
  inc   rbx
  cmp   rbx, r10
  jb    .loop_3
.after_if_3:
  cmp   r9, rcx
  jae   .after_if_4
  ; if n2 < displacement then

  xchg  [rbp-32], r9 ; r9 = n1
  mov   rcx, r9      ; displacement = n1
.loop_4:
  mov   byte [rdx+r8], '0'
  inc   r8
  inc   rbx
  cmp   rbx, r10
  jb    .loop_4

.after_if_4:
  
  ; Now call add_whole. Make sure that
  ; 'displacement' and 'new_a/b' are preserved.
  ; Basically, push rcx and rdx before the
  ; call.
  push  rcx
  push  rdx
  mov   rdi, rdx
  mov   rsi, [rbp-24]
  mov   rdx, r15
  call  add_whole wrt ..plt
  pop   rdx
  pop   rcx

  ; Move 'displacement' to r12.
  mov   r12, rcx

  ; r8 = reslength. We can reuse this register
  ; since it's never used again (in its
  ; old context) ahead this point.
  mov   rdi, r15
  call  strlen_asm wrt ..plt
  mov   r8, rax

  xor   ebx, ebx ; i = 0
.loop_5:
  mov   r9, r8
  sub   r9, rbx
  add   r9, r15
  mov   cl, byte [r9-1]
  mov   byte [r9], cl
  inc   rbx
  cmp   rbx, r12
  jb    .loop_5

  test  r12, r12 ; if displacement > 0
  jbe   .displacement_small
  mov   r9, r8
  sub   r9, r12
  add   r9, r15
  mov   byte [r9], '.'
.displacement_small:

  ; Free new_a and new_b
  mov   rax, 11
  mov   rdi, rdx
  syscall
  mov   rax, 11
  mov   rdi, [rbp-24]
  syscall

  ; Pop all saved registers and return.
.return:
  pop   r15
  pop   r14
  pop   r13
  pop   r12
  pop   rbx
  leave
  ret