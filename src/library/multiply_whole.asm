extern add_whole
extern strlen

section .text
global _multiply_whole
_multiply_whole:
  ; Input:
  ;   - char *a    -> rdi
  ;   - char *b    -> rsi
  ;   - char *res  -> rdx  (allocate strlen(a) + strlen(b) + 1 (for null terminator) bytes)
  ;   - char *buf1 -> rcx  (temporary buffer for program to use)
  ;   - char *buf2 -> r8   (both buf1 and buf2 have the same length as res)

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
  
  push   rbx                 ; Push used callee-saved registers.
  push   r12
  push   r13
  push   r14
  push   r15
  mov    r9, rdi             ; Move char* a to r9.
  mov    r10, rcx            ; Save rcx since strlen() doesn't preserve it.
  call   strlen              ; rax = strlen(a)
  mov    rbx, rax            ; Save rax in order to prevent it from being overwritten.
  mov    rdi, rsi            ; strlen's first argument is now b.
  call   strlen              ; Call strlen with b.
  dec    rax
  xchg   rax, rbx            ; rbx = strlen(b) - 1
  mov    rdi, r9             ; Restore rdi.
  mov    rcx, r10            ; Restore rcx.
  xor    r10d, r10d          ; r10b is the carry.
  mov    byte [rdx], '0'     ; Set the first character of the result string to '0'
  xor    r14d, r14d          ; Set r14 to 0.
.loop_1:
  xor    r13, r13
  mov    r9, rax
.loop_2:
  mov    r15d, 10
  mov    r11b, byte [rsi+rbx]
  sub    r11b, '0'
  mov    r12b, byte [rdi+r9-1]
  sub    r12b, '0'
  push   rax
  push   rbx
  push   rcx
  push   rdx
  mov    al, r11b
  mul    r12b
  mov    r11b, al
  pop    rdx
  pop    rcx
  pop    rbx
  pop    rax
  add    r11b, r10b
  push   rax
  push   rdx
  push   rcx
  push   rbx
  mov    ax, 0
  mov    al, r11b
  div    r15b
  pop    rbx
  pop    rcx
  mov    r10b, al
  mov    al, ah
  mov    byte [rcx+r13], al
  add    byte [rcx+r13], '0'
  pop    rdx
  pop    rax
  inc    r13
  dec    r9
  jnz    .loop_2
  cmp    r10b, 0
  jle    .after_if_1
  mov    byte [rcx+r13], r10b
  add    byte [rcx+r13], '0'
  xor    r10b, r10b
  inc    r13
.after_if_1:
  xor    r11, r11
  push   rax ; optimize this too, MOVE INPUT!!
  push   rdi
  push   rcx
  mov    rdi, rcx
  call   strlen
  mov    r13, rax
  pop    rcx
  pop    rdi
  mov    r9, r13
  shr    r9, 1
.loop_3:
  mov    al, byte [rcx+r11]
  lea    r15, [rcx+r13-1]
  sub    r15, r11
  mov    r12b, byte [r15]
  mov    byte [rcx+r11], r12b
  mov    byte [r15], al
  inc    r11
  cmp    r11, r9
  js     .loop_3
  pop    rax
  xor    r11, r11
  test   r14, r14
  jle    .after_loop_4
.loop_4:
  mov    byte [rcx+r13], '0'
  inc    r13
  inc    r11
  cmp    r11, r14
  js     .loop_4
.after_loop_4:
  mov    byte [rcx+r13], 0
  push   rdi
  push   rsi
  push   rdx
  mov    rdi, rdx
  mov    rsi, rcx
  mov    rdx, r8
  push   rax
  push   rcx
  push   r8
  call   add_whole
  pop    r8
  pop    rcx
  pop    rax
  pop    rdx
  pop    rsi
  pop    rdi
  xor    r11, r11
  push   rax
  push   rcx
  push   rdi
  mov    rdi, r8
  call   strlen
  mov    r9, rax
  pop    rdi
  pop    rcx
  pop    rax
.loop_5:
  mov    r15b, byte [r8+r11]
  mov    byte [rdx+r11], r15b
  inc    r11
  cmp    r11, r9
  js     .loop_5
  mov    byte [rdx+r9], 0
  xor    r11, r11
.loop_6:
  mov    byte [rcx+r11], 0
  mov    byte [r8+r11], 0
  inc    r11
  cmp    r11, r13
  js     .loop_6
  inc    r14
  mov    r15, rbx
  dec    rbx
  test   r15, r15
  jg     .loop_1
  mov    rdi, rdx
  call   strlen
  mov    byte [rdx+rax], 0
  pop    r15
  pop    r14
  pop    r13
  pop    r12
  pop    rbx
  ret