; Chapter 8 assignment: five functions to write in assembly (Linux x86-64,
; NASM syntax, run in the course's containers). Exercise 6 is in mystery.cpp.
;
; How it works: main.cpp calls these functions and checks the answers. Every
; function below starts as a stub that just returns 0, so every check fails
; until you write the real thing. Replace "xor eax, eax" with your code, keep
; the "ret", and run the program again.
;
; Rules of the road (System V x86-64, see 8.7, 8.8 and the project):
;   - integer arguments arrive in rdi, rsi, rdx, rcx (use edi, esi, edx for
;     32-bit ints, the low halves of the same registers)
;   - the result goes back in rax (eax for a 32-bit int)
;   - you may use rax, rcx, rdx, rsi, rdi freely
;   - rbx and rbp belong to the caller: if you want to use rbx, push it first
;     and pop it before ret
;   - in NASM, a label starting with "." belongs to the function above it, so
;     two functions can each have their own ".done"

section .text

global abs_i32
global max_i32
global count_above
global factorial
global sum_to

; ---------------------------------------------------------------------------
; Exercise 1 - int abs_i32(int x)
;
; Return the absolute value of x: x itself if it is zero or positive, -x if it
; is negative. Do not use the abs instruction (there is none). You need a
; comparison and a conditional jump, plus "neg".
;
;   abs_i32(-5) = 5     abs_i32(7) = 7     abs_i32(0) = 0
; ---------------------------------------------------------------------------
abs_i32:
    xor eax, eax            ; TODO: replace this line
    ret

; ---------------------------------------------------------------------------
; Exercise 2 - int max_i32(int a, int b)
;
; Return the larger of the two. Think of it as the C++ "a > b ? a : b", and
; remember from 8.6 that an if is "cmp, then jump over the part you skip".
;
;   max_i32(3, 9) = 9     max_i32(9, 3) = 9     max_i32(-4, -8) = -4
; ---------------------------------------------------------------------------
max_i32:
    xor eax, eax            ; TODO: replace this line
    ret

; ---------------------------------------------------------------------------
; Exercise 3 - std::size_t count_above(const int* data, std::size_t count, int threshold)
;
; Return how many of the `count` ints at `data` are strictly greater than
; `threshold`. The pointer is in rdi, count in rsi, threshold in edx. Look at
; sum_array in the project: this is the same loop with an if inside it.
;
;   data = {68, 72, 59, 81, 90, 55, 77, 64}, threshold 70  ->  4
; ---------------------------------------------------------------------------
count_above:
    xor eax, eax            ; TODO: replace this line
    ret

; ---------------------------------------------------------------------------
; Exercise 4 - std::uint64_t factorial(unsigned n)
;
; Return n! (n * (n-1) * ... * 2 * 1), with 0! = 1. Use a loop and the imul
; instruction (imul rax, rcx multiplies rax by rcx). The answer is 64 bits
; wide, so use the 64-bit registers for the product. n will not be above 20.
;
;   factorial(0) = 1     factorial(5) = 120     factorial(10) = 3628800
; ---------------------------------------------------------------------------
factorial:
    xor eax, eax            ; TODO: replace this line
    ret

; ---------------------------------------------------------------------------
; Exercise 5 - int sum_to(int n)
;
; Return n + (n-1) + ... + 1, written as a RECURSIVE function, like in 8.10:
; if n is zero or negative the answer is 0, otherwise it is n + sum_to(n - 1).
; You will need "call sum_to" inside sum_to itself.
;
; Hint: the call will overwrite edi and eax, so n must be kept somewhere that
; survives the call. rbx is the register for that, but it belongs to the
; caller: push rbx at the start, pop rbx before ret. (The push also leaves
; the stack the right way up for the call. At entry rsp is 8 off a multiple
; of 16, and the push makes up the difference.)
;
;   sum_to(0) = 0     sum_to(10) = 55     sum_to(100) = 5050
; ---------------------------------------------------------------------------
sum_to:
    xor eax, eax            ; TODO: replace this line
    ret

; ---------------------------------------------------------------------------
; Provided for Exercise 6. Do not change it: read it, then write the same
; behaviour in C++ in mystery.cpp.
; ---------------------------------------------------------------------------
global mystery
mystery:
    mov eax, edi
    imul eax, edi
    test edi, 1
    jz .even
    inc eax
.even:
    ret

section .note.GNU-stack noalloc noexec nowrite progbits
