#include <print>
#include <algorithm>
#include <vector>

int main() {

    int n{24};
    std::vector<int> collection{14, 24, 72, 8, 98, 112};

    auto result = std::find(collection.begin(), collection.end(), n);

    if (result != collection.end()) {
        std::println("collection contains: {}", n);
    } else {
        std::println("collection does not contain: {}", n);
    }

    std::println("------------");

    auto odd = [](int x) { return (x % 2) != 0; };

    auto odd_n_position = std::find_if(collection.begin(), collection.end(), odd);

    if (odd_n_position != collection.end()) {
        std::println("collection contains at least one odd number : {}", *odd_n_position);
    } else {
        std::println("collection does not contain any odd number");
    }

    return 0;
}