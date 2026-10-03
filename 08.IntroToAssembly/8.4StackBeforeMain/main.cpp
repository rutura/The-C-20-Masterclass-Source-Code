// The smallest possible C++ program - nothing to run and nothing to
// print, on purpose. The entire point of this lecture is what happens
// in the few lines of assembly BEFORE this body even starts: the stack
// that already exists by the time main's first instruction runs, and
// the two-line "prologue" every function opens with to claim its own
// slice of it.
//
// Try it: paste this exact function into Compiler Explorer (gcc or
// clang, -O0) and confirm you see five lines of assembly for something
// this short. NOTES.md walks through all five, plus everything that
// happened on the stack before this point.
int main() {
    return 0;
}
