section .text
global  asmalloc
asmalloc:
  ; Dynamically allocates memory (without any zeroing gurantee)
  ; Honestly this is just an mmap wrapper.

  ; Input:
  ;   - rdi -> the amount of bytes to allocate

  ; Registers used:
  ;   - rax
  ;   - rcx (clobbered after syscall)
  ;   - rsi
  ;   - rdx
  ;   - r8
  ;   - r9
  ;   - r10
  ;   - r11 (clobbered after syscall)

  ; Returns:
  ;   - rax -> a memory address to the newly allocated memory

  mov   rax, 9    ; mmap system call number
  mov   rsi, rdi  ; length of buffer
  xor   edi, edi  ; address (0 means allocate anywhere)
  mov   rdx, 3    ; read/write/execute protection
  mov   r10, 0x22 ; flags
  mov   r8, -1    ; file descriptor (use -1 to allocate anonymous memory) 
  xor   r9d, r9d  ; offset
  syscall         ; allocate memory

  ret