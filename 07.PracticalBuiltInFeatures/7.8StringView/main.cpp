#include <print>
#include <string>
#include <string_view>

int main() {

    // std::string_view does not own characters - it is a (pointer, length)
    // pair pointing at characters owned by someone else: a std::string, a
    // string literal, part of either. No allocation, no copy.
    std::string color{"red"};
    std::string colorCopy{color};        // a real copy - owns its own data
    std::string_view colorView{color};   // a view - "sees" color's own data

    std::println("color: {}\ncolorCopy: {}\ncolorView: {}",
                  color, colorCopy, colorView);

    // Because colorView points at color's characters, a change to color
    // shows up through colorView. colorCopy, a separate string, does not
    // see it.
    color.at(0) = 'R';
    std::println("\nafter modifying color:");
    std::println("color: {}\ncolorCopy: {}\ncolorView: {}",
                  color, colorCopy, colorView);

    // A string_view compares directly with a string or another view.
    std::println("\ncolor == colorView: {}", color == colorView);
    std::println("colorCopy == colorView: {}", colorCopy == colorView);

    // remove_prefix/remove_suffix shrink the view's window without
    // touching the underlying characters - O(1), nothing is copied or
    // erased.
    colorView.remove_prefix(1);   // drop the leading 'R'
    colorView.remove_suffix(1);   // drop the trailing 'd'
    std::println("\ncolor: {}\ncolorView (after trimming): {}", color, colorView);

    // A string_view can also wrap a plain string literal - no std::string
    // is created at all here.
    std::string_view label{"C++ course"};
    std::print("\ncharacters in label: ");
    for (char c : label) {
        std::print("{} ", c);
    }
    std::println("");

    std::println("label.size(): {}", label.size());
    std::println("label.find(' '): {}", label.find(' '));
    std::println("label.starts_with(\"C++\"): {}", label.starts_with("C++"));

    return 0;
}
