extern strlen

section .text
global add_whole
add_whole:
  ; Input:
  ;   - char *a -> rdi
  ;   - char *b -> rsi
  ;   - char *res -> rdx

  ; Registers used:
  ;   - rax
  ;   - rcx
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11
  ;   - r12
  ;   - r13
  ;   - r14
  
  push   r12                  ; Save callee-saved registers used.
  push   r13                  ; In this case,
  push   r14                  ; r12, r13, and r14.
  call   strlen               ; Calculate the length of char *a and store it in rax.
  push   rax                  ; Save rax,
  push   rdi                  ; and rdi to make another call to strlen.
  mov    rdi, rsi             ; Move char *b into rdi.
  call   strlen               ; Calculate the length of char *b,
  mov    r8, rax              ; and store it in r8.
  pop    rdi                  ; Now, rax = strlen(a)
  pop    rax                  ;      r8  = strlen(b)
  mov    r9, r8               ; The next two lines of code
  cmp    rax, r8              ; put std::max(rax, r8) into
  cmovnc r9, rax              ; the r9 register.
  xor    r10b, r10b           ; r10b = false := carry_flag
  xor    ecx, ecx             ; rcx = 0 := loop_counter
.loop_1:
  lea    r13, [rcx+1]         ; r13 = loop_counter + 1
  mov    r11b, 48             ; r11b = '0', if there are no more digits in the number/s, 
  mov    r12b, r11b           ; r12b = '0'  then these default values will be used.
  cmp    rcx, rax             ; Compare loop_counter with strlen(a).
  jnb     .after_if_1         ; if (loop_counter < strlen(a)):
  lea    r14, [rdi+rax-1]     ;   r11b = a[strlen(a) - loop_counter - 1]
  sub    r14, rcx             ; These two lines execute 
  mov    r11b, byte [r14]     ; that if statement.
.after_if_1:
  cmp    r8, r13              ; Compare strlen(b) with loop_counter + 1.
  js     .after_if_2          ; if (loop_counter < strlen(b)):
  lea    r14, [rsi+r8]        ;   r12b = b[strlen(b) - loop_counter - 1]
  sub    r14, rcx             ; The next two lines 
  dec    r14                  ; execute that one
  mov    r12b, byte [r14]     ; line if statement.
.after_if_2:
  add    r11b, r12b           ; Add individual digits of the numbers.
  sub    r11b, 48
  add    r11b, r10b           ; Check for carry, if it exists,
  xor    r10b, r10b           ; then add it and reset it.
  cmp    r11b, 57             ; Compare the current addition result with '9'
  jle    .after_if_3          ; if (r11b > '9'):
  sub    r11b, 10             ;   r11b -= 10
  mov    r10b, 1              ;   carry_flag = true
.after_if_3:
  mov    byte [rdx+rcx], r11b ; res[loop_counter] = r11b
  inc    rcx                  ; Increment the loop counter, which now points to the end of res.
  cmp    rcx, r9              ; Keep looping,
  js     .loop_1              ; while (loop_counter < std::max(strlen(a), strlen(b))).
  test   r10b, r10b           ; Check for a final carry.
  jz     .after_if_4          ; if (carry_flag):
  mov    byte [rdx+rcx], 49   ;   res[loop_counter] = '1'
  inc    r9                   ;   Increment r9, which stores strlen(res).
.after_if_4:
  xor    rcx, rcx             ; rcx = 0 := loop_counter
  mov    r11, r9              ; Note that r9 = strlen(res).
  shr    r11, 1               ; r11 = strlen(res) / 2
.loop_2:
  lea    r12, [rdx+r9]        ; r12 = &res[strlen(res) - loop_counter - 1]
  sub    r12, rcx
  dec    r12
  mov    r8b, byte [rdx+rcx]  ; r8b = res[loop_counter]
  mov    r10b, byte [r12]     ; r10b = *r12 = res[strlen(res) - loop_counter - 1]
  mov    byte [rdx+rcx], r10b ; res[loop_counter] = r10b
  mov    byte [r12], r8b      ; res[strlen(res) - loop_counter - 1] = r8b
  inc    rcx
  cmp    rcx, r11             ; Keep looping while (loop_counter < strlen(res) / 2)
  js     .loop_2
  mov    byte [rdx+r9], 0     ; res should be null terminated.
  pop    r14                  ; Pop used callee-saved registers.
  pop    r13
  pop    r12
  ret