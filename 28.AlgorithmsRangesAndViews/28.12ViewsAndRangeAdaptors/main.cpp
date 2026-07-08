#include <print>
#include <algorithm>
#include <format>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

void print(auto view) {
    for (auto i : view) { // Computation happens here.
        std::print("{} ", i);
    }
    std::println("");
}

struct Student {
    auto operator<=>(const Student& s) const = default;
    std::string m_name;
    unsigned int m_age;
};

template <>
struct std::formatter<Student> : std::formatter<std::string> {
    auto format(const Student& s, std::format_context& ctx) const {
        return std::formatter<std::string>::format(
            std::format("Student [ name : {}, age : {}]", s.m_name, s.m_age), ctx);
    }
};

int main() {

    std::vector<int> vi{1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::println("");
    std::println("std::ranges::filter_view : ");
    auto evens = [](int i) { return (i % 2) == 0; };
    std::print("vi : ");
    print(vi);
    std::ranges::filter_view v_evens = std::ranges::filter_view(vi, evens); // no computation yet
    std::print("vi evens : ");
    print(v_evens); // computation happens inside print()
    std::print("vi evens : ");
    print(std::ranges::filter_view(vi, evens));
    std::print("vi odds : ");
    print(std::ranges::filter_view(vi, [](int i) { return (i % 2) != 0; }));

    std::print("vi : ");
    print(vi);

    std::println("");
    std::println("std::ranges::transform_view : ");
    std::ranges::transform_view v_transformed = std::ranges::transform_view(vi, [](int i) { return i * 10; });
    std::print("vi : ");
    print(vi);
    std::print("vi transformed : ");
    print(v_transformed);
    std::print("vi : ");
    print(vi);

    std::println("");
    std::println("std::ranges::take_view : ");
    std::ranges::take_view v_taken = std::ranges::take_view(vi, 5);
    std::print("vi : ");
    print(vi);
    std::print("vi taken : ");
    print(v_taken);

    std::println("");
    std::println("std::views::take_while : ");
    vi = {1, 11, 23, 131, 2, 3, 4, 5, 6, 7, 8, 9};
    std::ranges::take_while_view v_taken_while = std::ranges::take_while_view(vi, [](int i) { return (i % 2) != 0; });
    std::print("vi : ");
    print(vi);
    std::print("vi taken_while : ");
    print(v_taken_while);

    std::println("");
    std::println("std::ranges::drop_view : ");
    vi = {1, 11, 23, 131, 2, 3, 4, 5, 6, 7, 8, 9};
    std::ranges::drop_view v_drop = std::ranges::drop_view(vi, 5);
    std::print("vi : ");
    print(vi);
    std::print("vi_drop : ");
    print(v_drop);

    std::println("");
    std::println("std::ranges::drop_while_view : ");
    vi = {1, 11, 23, 4, 2, 3, 4, 5, 6, 7, 8, 9};
    std::ranges::drop_while_view v_drop_while = std::ranges::drop_while_view(vi, [](int i) { return (i % 2) != 0; });
    std::print("vi : ");
    print(vi);
    std::print("v_drop_while : ");
    print(v_drop_while);

    std::println("");
    using pair = std::pair<int, std::string>;
    std::vector<pair> numbers{{1, "one"}, {2, "two"}, {3, "tree"}};

    // elements_view's (the type behind keys_view/values_view) constructor
    // requires its argument to already model view - a lightweight,
    // cheap-to-copy range. A plain std::vector doesn't model view (it owns
    // its storage), so constructing keys_view/values_view directly on one
    // fails to compile. std::views::all wraps the container in a ref_view
    // first, which does model view - and that's exactly what the
    // std::views::keys/values adaptor form below does internally, which is
    // why reaching for the adaptor is the idiomatic way to do this instead
    // of naming the _view type explicitly.
    auto k_view_direct = std::ranges::keys_view(std::views::all(numbers));
    auto v_view_direct = std::ranges::values_view(std::views::all(numbers));
    print(k_view_direct);
    print(v_view_direct);

    auto k_view = std::views::keys(numbers);
    auto v_view = std::views::values(numbers);
    print(k_view);
    print(v_view);

    vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::println("");
    std::println("std::views::filter : ");
    auto evens1 = [](int i) { return (i % 2) == 0; };
    std::print("vi : ");
    print(vi);
    std::ranges::filter_view v_evens1 = std::views::filter(vi, evens1); // no computation yet
    std::print("vi evens : ");
    print(v_evens1); // computation happens inside print()
    std::print("vi evens : ");
    print(std::views::filter(vi, evens1));
    std::print("vi odds : ");
    print(std::views::filter(vi, [](int i) { return (i % 2) != 0; }));

    std::println("");
    std::println("students example : ");

    std::vector<Student> class_room{{"Mike", 12}, {"John", 17}, {"Drake", 14}, {"Mary", 16}};

    std::println("");
    std::println("classroom : ");
    for (auto& s : class_room) {
        std::println("   {}", s);
    }

    std::ranges::sort(class_room, std::less<>{}, &Student::m_age);

    std::println("");
    std::println("classroom (after sort) : ");
    for (auto& s : class_room) {
        std::println("   {}", s);
    }

    std::print("students under 15 : ");
    print(std::views::take_while(class_room, [](const Student& s) { return (s.m_age < 15); }));

    return 0;
}