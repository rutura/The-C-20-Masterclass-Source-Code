#include <print>

int main() {

    int scores[]{1, 2, 5};

    // std::size() (C++17) is the safe, generic way to get an array's
    // element count - no more error-prone sizeof(arr)/sizeof(arr[0]) math.
    int count{std::size(scores)};

    std::println("sizeof(scores) : {}", sizeof(scores));
    std::println("sizeof(scores[0]) : {}", sizeof(scores[0]));
    std::println("count : {}", count);

    /*
    int count{sizeof(scores) / sizeof(scores[0])}; // the old, manual way

    for (size_t i{0}; i < count; ++i) {
        std::println("scores[{}] : {}", i, scores[i]);
    }

    for (auto i : scores) {
        std::println("value : {}", i);
    }
    */

    return 0;
}
