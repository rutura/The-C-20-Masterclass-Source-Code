; Two functions written by hand and called from C++ (see main.cpp).
;
; Calling convention: Linux x86-64 "System V". It is the same one the compiler
; used in the listings of lectures 8.7 and 8.8.
;   - integer arguments arrive in rdi, rsi, rdx, rcx, r8, r9, in that order
;   - an integer result goes back in rax (eax for a 32-bit int)
;   - rbx, rbp and r12 to r15 belong to the caller. We only use scratch
;     registers (rax, rcx, rdx), so there is nothing to save or restore.

section .text

global add_i32
global sum_array

; int add_i32(int a, int b)
add_i32:
    mov eax, edi            ; a arrives in edi, the low half of rdi
    add eax, esi            ; b arrives in esi
    ret

; std::int64_t sum_array(const int* data, std::size_t count)
sum_array:
    xor eax, eax            ; total = 0. Writing eax also clears the top half of rax
    xor ecx, ecx            ; i = 0
.next:
    cmp rcx, rsi            ; compare i with count
    jae .done               ; "above or equal" is the UNSIGNED test: i is a size_t
    movsxd rdx, dword [rdi + rcx*4]   ; data[i]: address = data + i * 4 bytes, widened to 64 bits
    add rax, rdx            ; total += data[i]
    inc rcx                 ; ++i
    jmp .next
.done:
    ret

; Without this note the linker warns that the stack might need to be
; executable. Our code never runs from the stack, so say so.
section .note.GNU-stack noalloc noexec nowrite progbits
