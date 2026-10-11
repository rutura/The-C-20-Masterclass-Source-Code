#include <print>                   // this header happens to bring std::string in, on these three compilers

#include "report.h"                // uses std::string without including <string>
#include "settings.h"

// Three problems of the header model, all in this one small program.
//
// 1. A header is not self-contained. report.h works here only because <print>
//    was included before it. Move the line `#include "report.h"` above
//    `#include <print>` and it stops compiling. Nothing in report.h says what it
//    needs, and a different library may order its includes differently.
//
// 2. A header leaks everything. settings.h defines the macro WARM, and from that
//    line on every WARM in every file is the number 25. Uncomment this enum and
//    read the error: the compiler sees `enum class Mode { COLD, 25, HOT };`.
//
//        enum class Mode { COLD, WARM, HOT };
//
// 3. A header is pasted, again and again. Every .cpp file that includes <print>
//    gets about 65,000 lines of text to read before its own first line (17.2's
//    notes measure it), and the compiler reads them again for every file.

int main() {
    std::println("limit for warm is {}", WARM);                // the macro doing its job
    std::println("21.5 is {}", label_for(21.5));
    std::println("12.0 is {}", label_for(12.0));
    return 0;
}
