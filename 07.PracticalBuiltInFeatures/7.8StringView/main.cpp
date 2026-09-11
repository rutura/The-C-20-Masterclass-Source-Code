#include <print>
#include <string>
#include <string_view>

int main() {

    // std::string_view does not own characters - it is a (pointer, length)
    // pair pointing at characters owned by someone else: a std::string, a
    // string literal, part of either. No allocation, no copy.
    std::string color{"red"};
    std::string color_copy{color};        // a real copy - owns its own data
    std::string_view color_view{color};   // a view - "sees" color's own data

    std::println("color: {}\ncolor_copy: {}\ncolor_view: {}",
                  color, color_copy, color_view);

    // Because color_view points at color's characters, a change to color
    // shows up through color_view. color_copy, a separate string, does not
    // see it.
    color.at(0) = 'R';
    std::println("\nafter modifying color:");
    std::println("color: {}\ncolor_copy: {}\ncolor_view: {}",
                  color, color_copy, color_view);

    // A string_view compares directly with a string or another view.
    std::println("\ncolor == color_view: {}", color == color_view);
    std::println("color_copy == color_view: {}", color_copy == color_view);

    // remove_prefix/remove_suffix shrink the view's window without
    // touching the underlying characters - O(1), nothing is copied or
    // erased.
    color_view.remove_prefix(1);   // drop the leading 'R'
    color_view.remove_suffix(1);   // drop the trailing 'd'
    std::println("\ncolor: {}\ncolor_view (after trimming): {}", color, color_view);

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
