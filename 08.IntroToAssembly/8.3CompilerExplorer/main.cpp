#include <print>

// This lecture is about the TOOL, not new C++. Paste just square's body
// (no #include, no main needed) into godbolt.org - "Compiler Explorer" -
// and watch the assembly pane on the right fill in as you type. Set the
// compiler dropdown to "x86-64 gcc" or "x86-64 clang", and the options
// box to "-O0" (MSVC's equivalent flag is "/Od") - that keeps the
// assembly a close, literal translation of the source, which is what
// the rest of this chapter relies on.
//
// NOTES.md shows the -O0 assembly for this exact function, and also
// shows the SAME function compiled for ARM64 (what an Apple Silicon
// Mac's own CPU actually runs) side by side with x86-64 - same source,
// two genuinely different instruction sets.
int square(int num) {
    return num * num;
}

int main() {
    std::println("square(6) = {}", square(6));
    return 0;
}
