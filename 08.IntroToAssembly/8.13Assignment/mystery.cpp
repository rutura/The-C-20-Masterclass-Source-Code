/*
    Exercise 6 - Reading assembly: what does `mystery` do?

    exercises.asm contains this function, written by someone else:

        mystery:
            mov eax, edi
            imul eax, edi
            test edi, 1
            jz .even
            inc eax
        .even:
            ret

    Do not run it first. Read it, work out what it computes for the int in
    edi (the argument), then write the same behaviour in C++ below.
    main.cpp will call both versions on a range of inputs and tell you if any
    answer differs.

    Hints: imul multiplies, "test edi, 1" looks at the lowest bit of the
    number, jz jumps when the result of the test was zero, inc adds one.
    Check your version on negative numbers too: the inputs tested include them.
*/

int mystery_cpp(int n) {
    // TODO
    return 0;
}
