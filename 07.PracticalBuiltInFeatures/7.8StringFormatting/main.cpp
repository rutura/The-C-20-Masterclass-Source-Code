#include <print>
#include <format>
#include <string>
#include <vector>
#include <iterator>

int main() {

    // std::print/println WRITE a formatted result straight to stdout.
    // std::format builds the SAME formatted text but hands it back as a
    // std::string instead - useful when the text is not going straight
    // to the console (a log line, a file, a GUI label, ...).
    std::string greeting{std::format("Hello, {}! You are {} years old.",
                                      "Ada", 36)};
    std::println("{}", greeting);

    // --- the format-spec grammar: {:fill align width.precision type} ------
    // Every {} can carry a colon-introduced spec describing exactly how
    // to lay out that one argument.

    //Width and alignment
    std::println("[{:10}]", 42);       // width 10, default-aligned
    std::println("[{:<10}]", 42);      // < left-align
    std::println("[{:>10}]", 42);      // > right-align (default for numbers)
    std::println("[{:^10}]", 42);      // ^ center

    // A fill character goes right before the align character.
    std::println("[{:*^10}]", 42);     // '*' as fill, centered

    // Precision after the '.': for floating point, digits after the
    // decimal point; for a string, the maximum characters printed.
    std::println("{:.2f}", 3.14159);   // "3.14"
    std::println("{:.3}", "abcdefg");  // "abc" - precision on a string

    // --- sign flags -----------------------------------------------------
    // '+' always shows a sign; '-' (the default) only shows '-' for
    // negatives; ' ' reserves a space where '+' would go, so positives
    // and negatives line up in a column.
    std::println("{:+d}  {:+d}", 42, -42);   // "+42  -42"
    std::println("{: d}  {: d}", 42, -42);   // " 42  -42"

    // --- alternate form '#': make the base visible ------------------------
    std::println("{:#x}", 255);   // "0xff" - hex with the 0x prefix
    std::println("{:#o}", 8);     // "010"  - octal with the 0 prefix
    std::println("{:#b}", 5);     // "0b101" - binary with the 0b prefix

    // --- positional arguments: {0}, {1}, ... reuse or reorder args --------
    // Handy when the same value appears more than once, or a translated
    // sentence needs to reorder words relative to English.
    std::println("{0} bought {1} for {0}'s {2}.", "Ada", "flowers", "mother");

    // --- combining pieces into one spec: index, fill/align/width, type ----
    std::println("{0:>8.2f} | {1:>8.2f}", 4.5, 128.375);

    // --- format_to: write straight into an existing buffer -----------------
    // std::format allocates a brand new std::string every call. format_to
    // writes into somewhere that already exists, through an output
    // iterator - useful for building up one buffer across many calls
    // without a fresh allocation each time.
    std::string buffer;
    std::format_to(std::back_inserter(buffer), "{}={} ", "width", 400);
    std::format_to(std::back_inserter(buffer), "{}={}", "height", 300);
    std::println("{}", buffer);

    return 0;
}
