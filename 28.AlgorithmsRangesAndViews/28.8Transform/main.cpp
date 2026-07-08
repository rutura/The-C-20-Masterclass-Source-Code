#include <print>
#include <algorithm>
#include <iterator>
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

    std::vector<int> input{5, 7, 4, 2, 8, 6, 1, 9, 0, 3, 11, 45, 6, 23};
    std::vector<int> output{11, 22, 33};

    std::println("output size : {}", output.size());
    std::println("output capacity : {}", output.capacity());

    print_collection(input);
    print_collection(output);

    // std::transform(input.begin(), input.end(), output.begin(), ...) would
    // only overwrite whatever slots already exist in output, without
    // growing it. std::back_inserter appends instead, extending output's
    // capacity as needed.
    std::transform(input.begin(), input.end(), std::back_inserter(output), [](int n) { return n * 2; });

    print_collection(output);
    std::println("output size : {}", output.size());
    std::println("output capacity : {}", output.capacity());

    std::println("Done!");

    return 0;
}