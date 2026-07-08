#include <print>
#include <algorithm>
#include <vector>

template <typename T>
void print_collection(const T& collection) {
    std::print(" Collection [");
    for (const auto& elt : collection) {
        std::print(" {}", elt);
    }
    std::println("]");
}

int main() {

    int source[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> dest{15, 21, 12, 53, 30, 40};

    std::print("source : ");
    print_collection(source);
    std::print("dest : ");
    print_collection(dest);

    // Copies source[0..4) into dest starting at dest.begin() - the caller
    // is responsible for making sure the destination range is large enough.
    std::copy(std::begin(source), std::begin(source) + 4, dest.begin());

    std::print("source(after copy) : ");
    print_collection(source);
    std::print("dest(after copy) : ");
    print_collection(dest);

    std::println("---------------------------");

    std::vector<int> dest1{100, 200, 300, 400, 500, 600};

    std::print("source : ");
    print_collection(source);
    std::print("dest1 : ");
    print_collection(dest1);

    auto odd = [](int n) { return (n % 2) != 0; };

    // If source has more matching elements than dest1 has room for, the
    // surplus is simply not written - same caller responsibility as copy().
    std::copy_if(std::begin(source), std::end(source), dest1.begin(), odd);

    std::print("source(after copy) : ");
    print_collection(source);
    std::print("dest1(after copy) : ");
    print_collection(dest1);

    return 0;
}