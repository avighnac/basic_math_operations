extern strlen

section .text
global add_whole
add_whole:
  push   rbx              ; The only callee-saved register to preserve.
  push   rdi              ; Preserving rdi since it's gonna have to be overwritten.
  call   strlen
  mov    ebx, eax         ; ebx = strlen(a)
  mov    rdi, rsi         ; To prepare another call to strlen.
  call   strlen           ; eax = strlen(b)
  pop    rdi              ; Restoring rdi.
  cmp    ebx, eax
  jae    .no_swap
  xchg   rdi, rsi         ; Make rdi refer to the longer input.
  xchg   ebx, eax         ; Make ebx refer to the longer strlen().
.no_swap:
  mov    ecx, eax         ; ecx now has the length of the shorter string.
  lea    r8, [rdi+rbx]    ; r8 points at the terminating zero of the longer input.
  lea    r9, [rsi+rax]    ; r9 points at the terminating zero of the shorter input.
  add    rdx, rbx         ; rdx now points to the end, since addition is performed backwards.
  push   rdx              ; In case there's a final carry.
  xor    ebx, ebx         ; bl stores the carry flag.
  mov    [rdx], bl        ; Zero-terminating the result.
  jecxz  .no_loop_a       ; If the minimum length is 0, skip loop A.
.loop_a:                  ; Deals with the common positions.
  movzx  eax, byte [r8-1] ; al is the back character of rdi.
  add    al, [r9-1]       ; al += the back character of rsi.
  sub    al, '0'          ; For addition.
  add    al, bl           ; Add carry.
  xor    ebx, ebx         ; Clear carry.
  cmp    al, '9'          ; Check whether to set a new carry.
  jbe    .char_ok
  sub    al, 10
  inc    ebx              ; Set carry.
.char_ok:
  mov    [rdx-1], al      ; Move the addition into the result string.
  dec    r8               ; Go back both
  dec    r9               ; inputs.
  dec    rdx              ; Move the output string back too.
  dec    rcx              ; Loop till the length of the shorter input is exhausted.
  jnz    .loop_a
.no_loop_a:
  cmp    r8, rdi
  jna    .no_loop_b       ; If there's no more left to add, skip loop b.
.loop_b:                  ; Deals with remainder of the longer input.
  movzx  eax, byte [r8-1] ; al is the back character of rdi.
  add    al, bl           ; Add carry.
  xor    ebx, ebx         ; Clear carry.
  cmp    al, '9'          ; If number produces a carry, set it.
  jbe    .char_ok_        ; Else, skip setting it.
  sub    al, 10
  inc    ebx              ; Set carry.
.char_ok_:
  mov    [rdx-1], al      ; Move the addition into the result string.
  dec    r8               ; Go back the longer input.
  dec    rdx              ; Move the output string back too.
  cmp    r8, rdi
  ja     .loop_b          ; Keep looping till the longer string is exhausted.
.no_loop_b:
  pop    rcx              ; rcx is the back of the output string now.
  test   bl, bl           ; Check for a final carry.
  jz     .done
.copy_up:
  mov    al, [rcx]
  mov    [rcx+rbx], al    ; rbx is the carry flag, which turns out to be 1 whenever this runs.
  dec    rcx
  cmp    rcx, rdx
  jae    .copy_up
  mov    byte [rdx], '1'
.done:
  pop    rbx
  ret