#include <array>
#include <print>

class Item {
public:
    Item() : m_var(0) {
        std::println("Item default constructor called");
    }
    Item(int var) : m_var(var) {}
    Item(int var1, int var2) : m_var(var1 * var2) {}
    Item(const Item& source) : m_var{source.m_var} {}

    int get() const { return m_var; }

private:
    int m_var{0};
};

template <>
struct std::formatter<Item> : std::formatter<std::string> {
    auto format(const Item& item, std::format_context& ctx) const {
        return std::formatter<std::string>::format(
            std::format("Item [ value : {}]", item.get()), ctx);
    }
};

template <typename T>
void print_collection(const T& collection) {
    std::print(" Collection [");
    for (const auto& elt : collection) {
        std::print(" {}", elt);
    }
    std::println("]");
}

template <typename T>
void print_raw_array(const T* p, std::size_t size) {
    std::print(" data = ");
    for (std::size_t i = 0; i < size; ++i) {
        std::print("{} ", p[i]);
    }
    std::println("");
}

int main() {

    // A few different ways to construct a std::array.
    std::array<int, 3> int_array1;      // uninitialized - contains junk, deliberately shown here
    std::array<int, 3> int_array2{1, 2}; // {1, 2, 0} - remaining elements default to 0
    std::array<int, 3> int_array3{};     // {0, 0, 0}
    std::array int_array4{1, 2};         // CTAD deduces std::array<int, 2>
    // std::array<int, 3> int_array5{1,2,3,4,5}; // compiler error: too many elements

    // std::to_array deduces both the element type and the size from the
    // braced list - the modern replacement for the old, non-standard
    // std::experimental::make_array this lecture used to reach for.
    auto int_array6 = std::to_array({1, 2, 3, 4, 5});

    std::print("int_array1 : ");
    print_collection(int_array1);
    std::print("int_array2 : ");
    print_collection(int_array2);
    std::print("int_array3 : ");
    print_collection(int_array3);
    std::print("int_array4 : ");
    print_collection(int_array4);
    std::print("int_array6 : ");
    print_collection(int_array6);

    // A std::array has a fixed size decided at compile time - you can't add
    // or remove elements, only overwrite what's already there.
    std::println("");
    std::println("Filling the array : ");
    int_array1.fill(321);
    int_array4.fill(500);
    std::print("int_array1 : ");
    print_collection(int_array1);
    std::print("int_array4 : ");
    print_collection(int_array4);

    std::println("");
    std::println("Accessing elements in an array: ");
    std::println("int_array2[0] : {}", int_array2[0]);
    std::println("int_array2.at(1) : {}", int_array2.at(1));
    std::println("int_array2.front() : {}", int_array2.front());
    std::println("int_array2.back() : {}", int_array2.back());
    print_raw_array(int_array2.data(), int_array2.size());

    std::println("");
    std::println("Collection creation and element access : ");

    // If you supply fewer elements than the declared size, the rest are
    // default-constructed (0 for int). Supplying more is a compile error.
    std::array<int, 10> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::print("numbers : ");
    print_collection(numbers);

    std::println("Element at index 3 (at()) : {}", numbers.at(3));   // bounds-checked
    std::println("Element at index 3 ([])   : {}", numbers[3]);      // not bounds-checked

    // at() throws when the index is out of range; [] has no such check.
    try {
        std::println("Element at index 20 (at()) : {}", numbers.at(20));
    } catch (std::exception& ex) {
        std::println("Access failed. Reason : {}", ex.what());
    }

    // numbers[20] would be undefined behavior here - deliberately left out
    // rather than executed, unlike the at() case above which fails safely.

    std::println("numbers front : {}", numbers.front());
    std::println("numbers back : {}", numbers.back());

    // front()/back() return references, so they can modify in place too.
    numbers.front() = 22;
    numbers.back() = 33;
    std::println("numbers front : {}", numbers.front());
    std::println("numbers back : {}", numbers.back());

    int raw_array[]{4, 5, 6, 7, 8, 9};
    std::println("Showing raw array data : ");
    print_raw_array(raw_array, 6);

    std::println("Showing numbers.data() as a raw array : ");
    print_raw_array(numbers.data(), numbers.size());

    std::println("");
    std::println("Iterators : ");

    auto it = numbers.begin();
    std::print(" std::array(with iterators) : [ ");
    while (it != numbers.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println(" ]");

    auto it_reverse = numbers.rbegin();
    std::print(" std::array(Reverse traversal with iterators) : [ ");
    while (it_reverse != numbers.rend()) {
        std::print(" {}", *it_reverse);
        ++it_reverse;
    }
    std::println(" ]");

    std::println("");
    std::println("capacity : ");
    std::println(" numbers size : {}", numbers.size());
    std::println(" numbers max_size : {}", numbers.max_size());
    std::println(" numbers is empty : {}", numbers.empty());
    // numbers.capacity() doesn't exist - a std::array's size never changes,
    // so there's no growth to reserve capacity for.

    std::println("");
    std::println("filling : ");
    std::print(" numbers : ");
    print_collection(numbers);
    numbers.fill(1000);
    std::print(" numbers : ");
    print_collection(numbers);

    // Swapping requires both arrays to be the exact same type (same element
    // type and same size) - they're genuinely different types otherwise.
    std::println("");
    std::println("Swapping : ");
    std::array<int, 10> other_numbers{5, 5, 5, 5, 5, 5, 5, 5, 5, 5};

    std::print(" numbers : ");
    print_collection(numbers);
    std::print(" other_numbers : ");
    print_collection(other_numbers);

    numbers.swap(other_numbers);

    std::print(" numbers : ");
    print_collection(numbers);
    std::print(" other_numbers : ");
    print_collection(other_numbers);

    // Unlike a raw C-style array, a std::array can be assigned wholesale.
    std::println("");
    std::println("Assigning arrays to each other :");
    numbers = other_numbers; // calls std::array's copy assignment operator

    std::print(" numbers : ");
    print_collection(numbers);
    std::print(" other_numbers : ");
    print_collection(other_numbers);

    std::println("");
    std::println("Storing custom objects in std::array : ");

    std::array<Item, 5> items = {};
    std::print(" default initialized items : ");
    print_collection(items);

    items.fill(Item(5));
    std::print(" items : ");
    print_collection(items);

    return 0;
}
