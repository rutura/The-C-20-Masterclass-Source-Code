#include <algorithm>
#include <print>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// You have already used the pipe: 7.6 wrote  numbers | views::filter(...) |
// views::transform(...). The | there is an OVERLOADED operator: the standard
// library defines it so that data can flow left to right through steps,
// instead of being wrapped in nested calls.
//
//     nested:   border(bold(text("north")))        read from the inside out
//     piped:    text("north") | bold | border      read left to right
//
// Here we build a small version of the idea, to see how it works.
// ---------------------------------------------------------------------------

// The thing that flows through the pipeline: a block of text lines.
struct Panel {
    std::vector<std::string> lines;

    Panel() = default;
    explicit Panel(const std::string& text) : lines{text} {}
};

// A DECORATOR is a function object (12.6) that takes a Panel and returns a new,
// decorated one. Each is a tiny struct with an operator().
struct Bold {
    Panel operator()(Panel panel) const {
        for (std::string& line : panel.lines) {
            line = "*" + line + "*";
        }
        return panel;
    }
};

struct Pad {
    int amount;

    Panel operator()(Panel panel) const {
        for (std::string& line : panel.lines) {
            line = std::string(static_cast<std::size_t>(amount), ' ') + line + std::string(static_cast<std::size_t>(amount), ' ');
        }
        return panel;
    }
};

struct Border {
    Panel operator()(Panel panel) const {
        std::size_t width{0};
        for (const std::string& line : panel.lines) {
            width = std::max(width, line.size());
        }

        Panel framed;
        framed.lines.push_back("+" + std::string(width, '-') + "+");
        for (const std::string& line : panel.lines) {
            framed.lines.push_back("|" + line + std::string(width - line.size(), ' ') + "|");
        }
        framed.lines.push_back("+" + std::string(width, '-') + "+");
        return framed;
    }
};

// THE PIPE OPERATOR ITSELF. Four lines. It takes a Panel on the left and any
// callable on the right, and CALLS the callable with the panel. Because it
// returns a Panel, the next | can take over: that is all a pipeline is.
// (The "template" makes it accept any decorator type: chapter 16.)
template <typename Decorator>
Panel operator|(Panel panel, Decorator decorator) {
    return decorator(std::move(panel));
}

void print(const Panel& panel) {
    for (const std::string& line : panel.lines) {
        std::println("{}", line);
    }
}

int main() {

    // Read left to right: start with the text, make it bold, pad it, frame it.
    Panel station{"north station"};
    print(station | Bold{} | Pad{1} | Border{});

    std::println("");

    // The order matters, just as the order of shell commands in a pipeline does.
    print(Panel{"alert"} | Border{} | Bold{});

    // The same shape with the standard library's views (7.6, chapter 15): a
    // different pipe operator, built the same way.
    std::vector<int> readings{68, 71, 59, 81, 90, 55};
    auto hot_celsius = readings
        | std::views::filter([](int f) { return f > 70; })
        | std::views::transform([](int f) { return (f - 32) * 5.0 / 9.0; });

    std::println("\nreadings above 70 F, in Celsius:");
    for (double c : hot_celsius) {
        std::println("  {:.1f}", c);
    }

    // Precedence: | is LOWER than + - * /, so arithmetic on the left-hand
    // side happens before the pipe. When mixing with other operators, use
    // parentheses.
    //
    // The same idea is the heart of a library you will use in the project:
    // ftxui builds screens with  text("hello") | bold | border.
    return 0;
}
