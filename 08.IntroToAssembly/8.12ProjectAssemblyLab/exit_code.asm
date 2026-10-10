; The smallest possible program: it does exactly one thing and exits with
; status code 42. No C++ compiler is involved at all.
;
;   nasm -f elf64 exit_code.asm -o exit_code.o
;   ld exit_code.o -o exit_code
;   ./exit_code ; echo $?        <- prints 42
;
; "Exit" here is a raw Linux system call: 60 goes in rax, the exit code goes
; in rdi, and "syscall" triggers it. Windows and macOS end a process through
; a different mechanism, which is why this lab runs in the Linux containers.
section .text
    global _start

_start:
    mov rax, 60      ; system call number for "exit" on Linux x86-64
    mov rdi, 42      ; the exit code reported back to the shell
    syscall
