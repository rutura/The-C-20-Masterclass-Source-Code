#include <array>
#include <print>
#include <vector>

// Iterators support arithmetic (begin() + n, end() - n), which lets a
// single function print any contiguous slice of a container instead of
// always starting at begin() and ending at end().
template <typename T>
void print_collection(const T& collection, size_t begin_adjustment, size_t end_adjustment) {
    auto start_point = collection.begin() + begin_adjustment;
    auto end_point = collection.end() - end_adjustment;

    std::print(" [");
    while (start_point != end_point) {
        std::print(" {}", *start_point);
        ++start_point;
    }
    std::println("]");
}

int main() {

    std::vector<int> ints1{11, 22, 33, 44, 55, 66, 77};
    std::array<int, 6> ints2{100, 200, 300, 400, 500, 600};

    print_collection(ints1, 1, 3);
    print_collection(ints2, 1, 1);

    return 0;
}