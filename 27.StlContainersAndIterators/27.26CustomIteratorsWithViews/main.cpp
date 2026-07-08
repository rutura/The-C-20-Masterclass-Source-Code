#include <algorithm>
#include <format>
#include <print>
#include <ranges>
#include <string>
#include "boxcontainer.h"

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

    BoxContainer<int> vi;
    vi.add(5);
    vi.add(1);
    vi.add(4);
    vi.add(8);
    vi.add(5);
    vi.add(3);
    vi.add(7);
    vi.add(9);
    vi.add(6);

    // Now that BoxContainer's iterator satisfies a real iterator category
    // (random access, by this point in the chapter), the standard ranges
    // views work on it directly, the same way they work on std::vector.

    // std::ranges::filter_view
    /*
    std::println("");
    std::println("std::ranges::filter_view : ");
    auto evens = [](int i){
        return (i %2) == 0;
    };
    std::print("vi : ");
    print(vi);

    std::ranges::filter_view v_evens = std::ranges::filter_view(vi,evens); // no computation yet
    std::print("vi evens : ");
    print(v_evens); // computation happens inside print()

    std::print("vi evens : ");
    print(std::ranges::filter_view(vi,evens));
    */

    // std::ranges::transform_view
    /*
    std::println("");
    std::println("std::ranges::transform_view : ");
    std::ranges::transform_view v_transformed = std::ranges::transform_view(vi,[](int i){
        return i * 10;
    });
    std::print("vi : ");
    print(vi);
    std::print("vi transformed : ");
    print(v_transformed);
    std::print("vi : ");
    print(vi);
    */

    // std::ranges::take_view
    /*
    std::println("");
    std::println("std::ranges::take_view : ");
    std::ranges::take_view v_taken = std::ranges::take_view(vi,5);
    std::print("vi : ");
    print(vi);
    std::print("vi taken : ");
    print(v_taken);
    */

    // std::ranges::take_while_view
    /*
    std::println("");
    std::println("std::views::take_while : ");
    std::ranges::take_while_view v_taken_while = std::ranges::take_while_view(vi,[](int i){
        return (i%2)!=0;
    });
    std::print("vi : ");
    print(vi);
    std::print("vi taken_while : ");
    print(v_taken_while);
    */

    // std::ranges::drop_view : drop n first elements
    /*
    std::println("");
    std::println("std::ranges::drop_view : ");
    std::ranges::drop_view v_drop = std::ranges::drop_view(vi,5);
    std::print("vi : ");
    print(vi);
    std::print("vi_drop : ");
    print(v_drop);
    */

    // std::views::drop_while_view : drops elements as long as the predicate is met
    /*
    std::println("");
    std::println("std::ranges::drop_while_view : ");
    std::ranges::drop_while_view v_drop_while = std::ranges::drop_while_view(vi,[](int i){
        return (i%2)!=0;
    });
    std::print("vi : ");
    print(vi);
    std::print("v_drop_while : ");
    print(v_drop_while);
    */

    // Range adaptors: std::views::filter()
    /*
    std::println("");
    std::println("std::views::filter : ");
    auto evens1 = [](int i){
        return (i %2) == 0;
    };
    std::print("vi : ");
    print(vi);
    std::ranges::filter_view v_evens1 = std::views::filter(vi,evens1); // no computation yet
    std::print("vi evens : ");
    print(v_evens1); // computation happens inside print()
    std::print("vi evens : ");
    print(std::views::filter(vi,evens1));
    std::print("vi odds : ");
    print(std::views::filter(vi,[](int i){
        return (i%2)!=0;
    }));
    */

    std::println("");
    std::println("students example : ");

    BoxContainer<Student> class_room;
    class_room.add(Student("Mike", 12));
    class_room.add(Student("John", 17));
    class_room.add(Student("Drake", 14));
    class_room.add(Student("Mary", 16));

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

    /*
    auto less_than_15_v = class_room | std::views::take_while([](const Student& s){return (s.m_age <15);});
    print(less_than_15_v);
    */

    std::println("End!");

    return 0;
}
