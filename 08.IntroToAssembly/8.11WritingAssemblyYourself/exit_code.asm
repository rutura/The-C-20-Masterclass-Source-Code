; A tiny, hand-written program - no C++ compiler involved at all. It
; does exactly one thing: exit with status code 42.
;
; Assemble and link on Linux (the course's own containers, chapter 2):
;
;   nasm -f elf64 exit_code.asm -o exit_code.o
;   ld exit_code.o -o exit_code
;   ./exit_code ; echo $?        <- prints 42
;
; NASM itself is the same tool, same syntax, on Windows and macOS too -
; but the three instructions below are Linux-specific: "exit" here is a
; raw Linux system call, reached by putting 60 in rax and the exit code
; in rdi, then triggering it with "syscall". Windows and macOS exit a
; process through a different mechanism entirely (a call into a system
; library, not a raw syscall number), so this exact file will not
; assemble-and-run unchanged there - see NOTES.md for what that
; difference means and where to look if you want to take it further.
section .text
    global _start

_start:
    mov rax, 60      ; syscall number for "exit" on Linux x86-64
    mov rdi, 42      ; the exit code to report back to the shell
    syscall
