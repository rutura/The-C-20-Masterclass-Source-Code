#include <charconv>
#include <optional>
#include <print>
#include <span>
#include <string_view>

// A program can receive arguments from whoever launches it. main() has a
// second form that hands them over:
//
//   int main(int argc, char* argv[])
//
//   argc - the argument COUNT (always >= 1)
//   argv - the argument VALUES, as C strings
//
//   argv[0] is the program's own name/path.
//   argv[1] .. argv[argc-1] are what the user typed after it.
//
// Run this as:  rooster add 3 4
//               rooster mul 6 7

std::optional<int> to_int(std::string_view text) {
    int value{0};
    auto [ptr, ec]{std::from_chars(text.data(), text.data() + text.size(), value)};
    if (ec != std::errc{} || ptr != text.data() + text.size()) {
        return std::nullopt;    // not a number, or trailing junk
    }
    return value;
}

int main(int argc, char* argv[]) {
    // Wrap the raw (count, pointer) pair in a std::span so it is a proper
    // range - then range-for and .size() just work.
    std::span<char*> args{argv, static_cast<std::size_t>(argc)};

    std::println("program : {}", args[0]);
    std::println("argc    : {}", argc);

    std::println("all arguments:");
    for (std::size_t i{0}; i < args.size(); ++i) {
        std::println("  argv[{}] = \"{}\"", i, args[i]);
    }

    // Treat argv[1] as a command and argv[2], argv[3] as its operands.
    if (argc < 4) {
        std::println("\nusage: {} <add|sub|mul> <a> <b>", args[0]);
        return 1;
    }

    std::string_view op{args[1]};
    auto a{to_int(args[2])};
    auto b{to_int(args[3])};

    if (!a || !b) {
        std::println("both operands must be integers");
        return 1;
    }

    int result{0};
    if (op == "add") {
        result = *a + *b;
    } else if (op == "sub") {
        result = *a - *b;
    } else if (op == "mul") {
        result = *a * *b;
    } else {
        std::println("unknown operation: {}", op);
        return 1;
    }

    std::println("{} {} {} = {}", *a, op, *b, result);
    return 0;
}
