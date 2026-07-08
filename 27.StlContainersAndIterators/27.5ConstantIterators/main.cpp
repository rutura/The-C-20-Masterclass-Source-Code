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

    std::vector<int> numbers{11, 22, 33, 44, 55, 66, 77};

    std::print("numbers : ");
    print_collection(numbers);

    // A regular iterator (numbers.begin()) can modify what it points to:
    // *it = 100; would be legal here.

    std::print("numbers : ");
    print_collection(numbers);

    std::println("-------");

    // cbegin()/cend() give a const_iterator - it can read but not write
    // through the container, even though numbers itself isn't const.
    auto c_it = numbers.cbegin();
    while (c_it != numbers.cend()) {
        // *c_it = 100; // compiler error: can't assign through a const_iterator
        ++c_it;
    }

    // Same idea, reversed: crbegin()/crend() give a const_reverse_iterator.
    auto it1 = numbers.crbegin();
    while (it1 != numbers.crend()) {
        // *it1 = 600; // compiler error: it1 is a const iterator
        ++it1;
    }

    return 0;
}