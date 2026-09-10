#include <print>
#include <stdexcept>
#include <string>
#include <vector>

// std::vector<T> is the workhorse collection: a sequence of T, stored
// back-to-back like std::array, but its size can change at run time.
// When in doubt about which container to use, the answer is std::vector.

void print_vec(const std::string& label, const std::vector<int>& v) {
    std::print("{} (size {}):", label, v.size());
    for (const int& n : v) {
        std::print(" {}", n);
    }
    std::println("");
}

int main() {
    // Braced list of elements.
    std::vector<int> primes{2, 3, 5, 7, 11};
    print_vec("primes", primes);

    // Parenthesized (count, value) constructor: 5 elements, all 0.
    // Note the different meaning of {} vs () here - a classic gotcha.
    std::vector<int> zeros(5, 0);
    print_vec("zeros", zeros);

    // Grow the vector one element at a time.
    std::vector<int> collected{};          // starts empty
    for (int n{1}; n <= 5; ++n) {
        collected.push_back(n * n);        // append a copy
    }
    print_vec("collected", collected);

    // emplace_back builds the element in place from its constructor args -
    // handy for types that are expensive to copy, like std::string.
    std::vector<std::string> names{};
    names.emplace_back("Ada");
    names.emplace_back("Grace");
    std::println("names holds {} entries, last is \"{}\"",
                 names.size(), names.back());

    // size() is the element count; capacity() is how many it can hold
    // before it has to reallocate. reserve() sets capacity up front when
    // you know roughly how many you will add.
    std::vector<int> buffer{};
    buffer.reserve(100);
    std::println("buffer size {}, capacity {}", buffer.size(), buffer.capacity());

    // Element access, same as std::array: [] is unchecked, at() throws.
    std::println("primes[2]     : {}", primes[2]);
    primes.at(0) = 99;                     // at() also works as an lvalue
    print_vec("primes after at(0)=99", primes);

    // Vectors compare element-by-element with == and !=.
    std::vector<int> a{1, 2, 3};
    std::vector<int> b{1, 2, 3};
    std::vector<int> c{1, 2, 4};
    std::println("a == b : {}", a == b);
    std::println("a == c : {}", a == c);

    // Copying a vector copies all its elements.
    std::vector<int> copy{a};
    copy.push_back(4);
    print_vec("a   ", a);                  // unchanged
    print_vec("copy", copy);

    // clear() removes every element; the vector is empty but still usable.
    collected.clear();
    std::println("after clear(): size {}, empty() {}",
                 collected.size(), collected.empty());

    try {
        std::println("buffer.at(0): {}", buffer.at(0));   // empty - out of range
    } catch (const std::out_of_range& ex) {
        std::println("caught out_of_range: {}", ex.what());
    }

    return 0;
}
