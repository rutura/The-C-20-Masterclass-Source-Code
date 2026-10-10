; Prints one line and exits, with no C++ and no C library involved.
;
;   nasm -f elf64 hello.asm -o hello.o
;   ld hello.o -o hello
;   ./hello
;
; Both jobs are raw Linux system calls. The number goes in rax and the
; arguments go in rdi, rsi, rdx. "syscall" then hands control to the kernel.

section .data
message: db "Hello from assembly", 10      ; 10 is the newline character
length:  equ $ - message                   ; the assembler counts the bytes for us

section .text
global _start

_start:
    mov rax, 1              ; system call 1 = write(fd, buffer, count)
    mov rdi, 1              ; fd 1 = standard output
    mov rsi, message        ; address of the first byte
    mov rdx, length         ; how many bytes
    syscall

    mov rax, 60             ; system call 60 = exit(status)
    xor rdi, rdi            ; status 0
    syscall
