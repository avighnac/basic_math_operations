extern add_whole
extern strlen_asm

section .text
global _multiply_whole
_multiply_whole:
  ; Input:
  ;   - char *a    -> rdi
  ;   - char *b    -> rsi
  ;   - char *res  -> rdx  (allocate strlen_asm(a) + strlen_asm(b) + 1 (for null terminator) bytes)
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
  
  push   rbx                  ; Push used callee-saved registers.
  push   r12
  push   r13
  push   r14
  push   r15
  mov    r9, rdi               ; Move char* a to r9.
  mov    r10, rcx              ; Save rcx since strlen_asm() doesn't preserve it.
  call   strlen_asm wrt ..plt      ; rax = strlen_asm(a)
  mov    rbx, rax              ; Save rax in order to prevent it from being overwritten.
  mov    rdi, rsi              ; strlen_asm's first argument is now b.
  call   strlen_asm wrt ..plt      ; Call strlen_asm with b.
  dec    rax
  xchg   rax, rbx              ; rbx = strlen_asm(b) - 1
  mov    rdi, r9               ; Restore rdi.
  mov    rcx, r10              ; Restore rcx.
  xor    r10d, r10d            ; r10b is the carry.
  mov    byte [rdx], '0'       ; Set the default value of the result string to '0'.
  xor    r14d, r14d            ; The number of leading zeroes to add.
.loop_1:
  lea    r13, [rax+1]          ; r13 = strlen_asm(a) + 1
  add    rcx, rax              ; rcx = &a[strlen_asm(a)]
  mov    r9, rax               ; r9 = strlen_asm(a)
  mov    r15d, 10              ; The number we're dividing by.
  push   rax                   ; Save rax since we use it for mul and div later.
.loop_2:
  movzx  r11d, byte [rsi+rbx]  ; r11b is a byte of char *b
  sub    r11b, '0'
  movzx  eax, byte [rdi+r9-1]  ; al is a byte of char *a
  sub    al, '0'
  mul    r11b
  mov    r11b, al              ; r11b is the multiplication of char *a and char *b.
  add    r11b, r10b            ; Add carry.
  push   rdx
  mov    al, r11b
  div    r15b
  mov    r10b, al              ; carry = r11b / 10
  mov    al, ah
  add    eax, '0'
  mov    byte [rcx], al        ; Add the remainder to the result string.
  pop    rdx
  dec    rcx
  dec    r9
  jnz    .loop_2               ; Loop r9 times.
  add    r10d, '0'
  mov    byte [rcx], r10b      ; Add the final carry (might be 0) to the string.
  xor    r10d, r10d            ; Reset carry.
  xor    r11d, r11d            ; r11 = 0
  test   r14, r14
  jle    .after_loop_3         ; if r14 <= 0 then skip loop_3
.loop_3:                       ; Adds r14 trailing zeroes to buf1, r14 is the amount of times loop_1 has run.
  mov    byte [rcx+r13], '0'   ; buf1[r13] = '0'
  inc    r13                   ; r13++
  inc    r11                   ; r11++
  cmp    r11, r14
  js     .loop_3               ; Loop r14 times.
.after_loop_3:
  mov    byte [rcx+r13], 0     ; Zero-terminate the string to pass it to add_whole().
  push   rcx                   ; Save used caller-saved registers.
  push   rdi
  push   rsi
  push   rdx
  mov    rdi, rdx              ; param1 = rdx (char *res)
  mov    rsi, rcx              ; param2 = rcx (char *buf1)
  mov    rdx, r8               ; param3 = r8 (char *buf2)
  mov    r15, r8               ; Saving the r8 register.
  call   add_whole wrt ..plt   ; buf2 = add_whole(res, buf1) (this doesn't actually return anything)
  mov    r8, r15               ; Restoring the r8 register.
  pop    rdx
  pop    rsi
  xor    r11d, r11d
  mov    rdi, r8
  call   strlen_asm wrt ..plt                ; r9 = strlen_asm(buf2) (length of the addition result)
  mov    r9, rax
  pop    rdi
  pop    rcx
  pop    rax
.loop_4:
  mov    r15b, byte [r8+r11]
  mov    byte [rdx+r11], r15b
  inc    r11
  cmp    r11, r9
  js     .loop_4
  mov    byte [rdx+r9], 0
  xor    r11d, r11d
.loop_5:
  mov    byte [rcx+r11], 0
  mov    byte [r8+r11], 0
  inc    r11
  cmp    r11, r13
  js     .loop_5
  inc    r14
  mov    r15, rbx
  dec    rbx
  test   r15, r15
  jg     .loop_1
  mov    rdi, rdx
  call   strlen_asm wrt ..plt
  mov    byte [rdx+rax], 0
  pop    r15
  pop    r14
  pop    r13
  pop    r12
  pop    rbx
  ret