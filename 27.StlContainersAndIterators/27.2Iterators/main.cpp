#include <array>
#include <print>
#include <vector>

template <typename T>
void print_collection(const T& collection) {
    auto it = collection.begin();
    std::print(" [");
    while (it != collection.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println("]");
}

int main() {

    std::vector<int> ints1{11, 22, 33, 44};
    std::array<int, 4> ints2{100, 200, 300, 400};

    std::vector<int>::iterator it_begin = ints1.begin();
    std::vector<int>::iterator it_end = ints1.end();

    std::println("first elt : {}", *it_begin);
    std::println("it == end_it : {}", (it_begin == it_end));

    ++it_begin;
    std::println("second elt : {}", *it_begin);
    std::println("it == end_it : {}", (it_begin == it_end));

    ++it_begin;
    std::println("third elt : {}", *it_begin);
    std::println("it == end_it : {}", (it_begin == it_end));

    ++it_begin;
    std::println("fourth elt : {}", *it_begin);
    std::println("it == end_it : {}", (it_begin == it_end));

    // One past the last valid element - it_begin now equals end(), and
    // dereferencing it here would be undefined behavior, so we stop instead
    // of showing what "junk elt" would print.
    ++it_begin;
    std::println("it == end_it : {}", (it_begin == it_end));

    std::println("--------");
    std::print("ints1 : ");
    print_collection(ints1);

    std::print("ints2 : ");
    print_collection(ints2);

    return 0;
}