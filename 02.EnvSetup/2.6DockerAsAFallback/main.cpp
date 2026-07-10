// The same small program follows us through this entire chapter. It doesn't
// grow - the point isn't the code, it's watching one unchanged program get
// built by every tool we cover: Visual Studio, Qt Creator, and Docker.

#include <print>

int main() {

    std::println("Hello from your C++ environment!");

    // __cplusplus tells us which C++ standard the compiler is actually
    // targeting right now. 202302L means C++23 - the version this course
    // is written against.
    std::println("Compiling as C++ standard: {}", __cplusplus);

#if defined(__clang__)
    std::println("Compiler: Clang {}.{}.{}", __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined(__GNUC__)
    std::println("Compiler: GCC {}.{}.{}", __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__);
#elif defined(_MSC_VER)
    std::println("Compiler: MSVC (_MSC_VER {})", _MSC_VER);
#else
    std::println("Compiler: unknown");
#endif

    return 0;
}
