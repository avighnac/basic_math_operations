extern add_whole
extern strlen

section .text
global _multiply_whole
_multiply_whole:
  ; Input:
  ;   - char *a    -> rcx
  ;   - char *b    -> rdx
  ;   - char *res  -> r8  (allocate strlen(a) + strlen(b) + 1 (for null terminator) bytes)
  ;   - char *buf1 -> r9  (temporary buffer for program to use)
  ;   - char *buf2 -> stack (both buf1 and buf2 have the same length as res)

  ; Registers used:
  ;   - rax
  ;   - rbx
  ;   - r11
  ;   - r12
  ;   - r13
  ;   - r14
  ;   - r15
  ;   - rdi
  ;   - rsi
  
  mov    r10, qword [rsp+40]  ; Retrieve the last argument from the stack.
  push   rbx                  ; Push used callee-saved registers.
  push   r12
  push   r13
  push   r14
  push   r15
  push   rdi
  push   rsi
  mov    r12, rcx              ; Move char* a to r12.
  call   strlen                ; rax = strlen(a)
  mov    rbx, rax              ; Save rax in order to prevent it from being overwritten.
  mov    rcx, rdx              ; strlen's first argument is now b.
  call   strlen                ; Call strlen with b.
  dec    rax
  xchg   rax, rbx              ; rbx = strlen(b) - 1
  mov    rcx, r12              ; Restore rcx.
  xor    r12d, r12d            ; r12b is the carry.
  mov    byte [r8], '0'        ; Set the default value of the result string to '0'.
  xor    edi, edi              ; The number of leading zeroes to add.
.loop_1:
  lea    r15, [rax+1]          ; r15 = strlen(a) + 1
  add    r9, rax               ; r9 = &a[strlen(a)]
  mov    r11, rax              ; r11 = strlen(a)
  mov    esi, 10               ; The number we're dividing by.
  push   rax                   ; Save rax since we use it for mul and div later.
.loop_2:
  movzx  r13d, byte [rdx+rbx]  ; r13b is a byte of char *b
  sub    r13b, '0'
  movzx  eax, byte [rcx+r11-1] ; al is a byte of char *a
  sub    al, '0'
  mul    r13b
  mov    r13b, al              ; r13b is the multiplication of char *a and char *b.
  add    r13b, r12b            ; Add carry.
  push   r8
  mov    al, r13b
  div    sil
  mov    r12b, al              ; carry = r13b / 10
  mov    al, ah
  add    eax, '0'
  mov    byte [r9], al         ; Add the remainder to the result string.
  pop    r8
  dec    r9
  dec    r11
  jnz    .loop_2               ; Loop r11 times.
  add    r12d, '0'
  mov    byte [r9], r12b       ; Add the final carry (might be 0) to the string.
  xor    r12d, r12d            ; Reset carry.
  xor    r13d, r13d            ; r13 = 0
  test   rdi, rdi
  jle    .after_loop_3         ; if rdi <= 0 then skip loop_3
.loop_3:                       ; Adds rdi trailing zeroes to buf1, rdi is the amount of times loop_1 has run.
  mov    byte [r9+r15], '0'    ; buf1[r15] = '0'
  inc    r15                   ; r15++
  inc    r13                   ; r13++
  cmp    r13, rdi
  js     .loop_3               ; Loop rdi times.
.after_loop_3:
  mov    byte [r9+r15], 0      ; Zero-terminate the string to pass it to add_whole().
  push   r9                    ; Save used caller-saved registers.
  push   rcx
  push   rdx
  push   r8
  mov    rcx, r8               ; param1 = r8 (char *res)
  mov    rdx, r9               ; param2 = r9 (char *buf1)
  mov    r8, r10               ; param3 = r10 (char *buf2)
  mov    rsi, r10              ; Saving the r10 register.
  call   add_whole             ; buf2 = add_whole(res, buf1) (this doesn't actually return anything)
  mov    r10, rsi              ; Restoring the r10 register.
  pop    r8
  pop    rdx
  xor    r13d, r13d
  mov    rcx, r10
  call   strlen                ; r11 = strlen(buf2) (length of the addition result)
  mov    r11, rax
  pop    rcx
  pop    r9
  pop    rax
.loop_4:
  mov    sil, byte [r10+r13]
  mov    byte [r8+r13], sil
  inc    r13
  cmp    r13, r11
  js     .loop_4
  mov    byte [r8+r11], 0
  xor    r13d, r13d
.loop_5:
  mov    byte [r9+r13], 0
  mov    byte [r10+r13], 0
  inc    r13
  cmp    r13, r15
  js     .loop_5
  inc    rdi
  mov    rsi, rbx
  dec    rbx
  test   rsi, rsi
  jg     .loop_1
  mov    rcx, r8
  call   strlen
  mov    byte [r8+rax], 0
  pop    rsi
  pop    rdi
  pop    r15
  pop    r14
  pop    r13
  pop    r12
  pop    rbx
  ret