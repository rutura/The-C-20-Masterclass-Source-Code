#include <print>

// Compiler Explorer has been the main tool all chapter, and it is
// enough for everything so far - but you do not need a website to see
// a function's assembly. Your own compiler can write it straight to a
// text file, locally, offline. Build this file normally first, then
// try the commands in NOTES.md to get square's assembly as a plain
// file sitting right next to this one.
int square(int num) {
    return num * num;
}

int main() {
    std::println("square(7) = {}", square(7));
    return 0;
}
