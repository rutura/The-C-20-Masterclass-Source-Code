; Solutions for the chapter 8 assignment. Same statements as exercises.asm,
; with the stubs filled in. Built as the second program, rooster_solution.

section .text

global abs_i32
global max_i32
global count_above
global factorial
global sum_to

; Exercise 1 - int abs_i32(int x)
abs_i32:
    mov eax, edi
    test eax, eax           ; set the flags from eax itself (shorter than cmp eax, 0)
    jns .done               ; "not signed": zero or positive, keep it
    neg eax                 ; negative: flip the sign
.done:
    ret

; Exercise 2 - int max_i32(int a, int b)
max_i32:
    mov eax, edi            ; assume a is the larger
    cmp eax, esi
    jge .done               ; a >= b: the guess was right
    mov eax, esi            ; otherwise b wins
.done:
    ret

; Exercise 3 - std::size_t count_above(const int* data, std::size_t count, int threshold)
count_above:
    xor eax, eax            ; matches = 0
    xor ecx, ecx            ; i = 0
.next:
    cmp rcx, rsi
    jae .done               ; unsigned test: i is a size_t
    cmp dword [rdi + rcx*4], edx    ; data[i] against threshold, as signed ints
    jle .skip               ; not strictly greater: do not count it
    inc rax
.skip:
    inc rcx
    jmp .next
.done:
    ret

; Exercise 4 - std::uint64_t factorial(unsigned n)
factorial:
    mov eax, 1              ; result = 1
    mov ecx, edi            ; counter = n (writing ecx clears the top half of rcx)
.loop:
    cmp ecx, 1
    jbe .done               ; stop when the counter is 1 or 0
    imul rax, rcx           ; result *= counter
    dec ecx
    jmp .loop
.done:
    ret

; Exercise 5 - int sum_to(int n)
sum_to:
    test edi, edi
    jg .recurse             ; n > 0: do the real work
    xor eax, eax            ; n <= 0: base case, the sum is 0
    ret
.recurse:
    push rbx                ; rbx is the caller's: save it. This also aligns the stack for the call
    mov ebx, edi            ; keep n, because edi is about to change
    dec edi                 ; argument for sum_to(n - 1)
    call sum_to             ; the answer comes back in eax
    add eax, ebx            ; n + sum_to(n - 1)
    pop rbx                 ; give rbx back
    ret

; Provided for Exercise 6 (the C++ twin is mystery_solution.cpp).
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
