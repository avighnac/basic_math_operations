extern strlen_asm

section .text
global add_whole
add_whole:
  ; Input:
  ;   - char *a -> rcx
  ;   - char *b -> rdx
  ;   - char *res -> r8

  ; Registers used:
  ;   - rax
  ;   - r9
  ;   - rcx
  ;   - rdx
  ;   - r10
  ;   - r11

  push   rbx               ; The only callee-saved register to preserve.
  push   rcx               ; Preserving rcx since it's gonna have to be overwritten.
  call   strlen_asm
  mov    ebx, eax          ; ebx = strlen_asm(a)
  mov    rcx, rdx          ; To prepare another call to strlen_asm.
  call   strlen_asm            ; eax = strlen_asm(b)
  pop    rcx               ; Restoring rcx.
  cmp    ebx, eax
  jae    .no_swap
  xchg   rcx, rdx          ; Make rcx refer to the longer input.
  xchg   ebx, eax          ; Make ebx refer to the longer strlen_asm().
.no_swap:
  mov    r9d, eax          ; r9d now has the length of the shorter string.
  lea    r10, [rcx+rbx]    ; r10 points at the terminating zero of the longer input.
  lea    r11, [rdx+rax]    ; r11 points at the terminating zero of the shorter input.
  add    r8, rbx           ; r8 now points to the end, since addition is performed backwards.
  push   r8                ; In case there's a final carry.
  xor    ebx, ebx          ; bl stores the carry flag.
  mov    [r8], bl          ; Zero-terminating the result.
  test   r9, r9
  jz     .no_loop_a        ; If the minimum length is 0, skip loop A.
.loop_a:                   ; Deals with the common positions.
  movzx  eax, byte [r10-1] ; al is the back character of rcx.
  add    al, [r11-1]       ; al += the back character of rdx.
  sub    al, '0'           ; For addition.
  add    al, bl            ; Add carry.
  xor    ebx, ebx          ; Clear carry.
  cmp    al, '9'           ; Check whether to set a new carry.
  jbe    .char_ok
  sub    al, 10
  inc    ebx               ; Set carry.
.char_ok:
  mov    [r8-1], al        ; Move the addition into the result string.
  dec    r10               ; Go back both
  dec    r11               ; inputs.
  dec    r8                ; Move the output string back too.
  dec    r9                ; Loop till the length of the shorter input is exhausted.
  jnz    .loop_a
.no_loop_a:
  cmp    r10, rcx
  jna    .no_loop_b        ; If there's no more left to add, skip loop b.
.loop_b:                   ; Deals with remainder of the longer input.
  movzx  eax, byte [r10-1] ; al is the back character of rcx.
  add    al, bl            ; Add carry.
  xor    ebx, ebx          ; Clear carry.
  cmp    al, '9'           ; If number produces a carry, set it.
  jbe    .char_ok_         ; Else, skip setting it.
  sub    al, 10
  inc    ebx               ; Set carry.
.char_ok_:
  mov    [r8-1], al        ; Move the addition into the result string.
  dec    r10               ; Go back the longer input.
  dec    r8                ; Move the output string back too.
  cmp    r10, rcx
  ja     .loop_b           ; Keep looping till the longer string is exhausted.
.no_loop_b:
  pop    r9                ; r9 is the back of the output string now.
  test   bl, bl            ; Check for a final carry.
  jz     .done
.copy_up:
  mov    al, [r9]
  mov    [r9+rbx], al      ; rbx is the carry flag, which turns out to be 1 whenever this runs.
  dec    r9
  cmp    r9, r8
  jae    .copy_up
  mov    byte [r8], '1'
.done:
  pop    rbx
  ret