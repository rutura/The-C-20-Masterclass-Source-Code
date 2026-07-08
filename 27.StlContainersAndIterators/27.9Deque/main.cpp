#include <deque>
#include <print>

class Item {
public:
    Item() : m_var(0) {
        std::println("Item default constructor called");
    }
    Item(int var) : m_var(var) {}
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
    auto it = collection.begin();
    std::print(" Collection [");
    while (it != collection.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println("]");
}

int main() {

    std::deque<int> numbers = {1, 2, 3, 4, 5, 6};
    std::deque<Item> items{Item(22), Item(33), Item(44), Item(55)};

    std::print("numbers : ");
    print_collection(numbers);
    std::print("items : ");
    print_collection(items);

    std::println("");
    std::println("Element access : ");
    std::println("numbers[3] : {}", numbers[3]);    // no bounds check
    std::println("numbers.at(3) : {}", numbers.at(3)); // bounds-checked

    // numbers[30] would be undefined behavior on a 6-element deque - no
    // bounds check, so it could read junk or crash. at(30) is the safe way
    // to ask the same "is index 30 valid?" question - it throws instead.
    try {
        std::println("numbers.at(30) : {}", numbers.at(30));
    } catch (std::exception& ex) {
        std::println("numbers.at(30) failed. Reason : {}", ex.what());
    }

    std::println("numbers.front() : {}", numbers.front());
    std::println("numbers.back() : {}", numbers.back());

    // deque has no data() method - unlike vector, its elements aren't
    // guaranteed to be contiguous in memory.

    std::println("");
    std::println("Iterators : ");
    auto it = numbers.begin();
    std::print("Deque(With iterators) : [ ");
    while (it != numbers.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println(" ]");

    auto it_reverse = numbers.rbegin();
    std::print("Deque(Reverse traversal with iterators) : [ ");
    while (it_reverse != numbers.rend()) {
        std::print(" {}", *it_reverse);
        ++it_reverse;
    }
    std::println(" ]");

    std::println("");
    std::println("capacity : ");
    std::println("numbers size : {}", numbers.size());
    std::println("numbers max_size : {}", numbers.max_size());
    std::println("numbers is empty : {}", numbers.empty());

    numbers.push_back(20);
    std::println("after pushing 20 to back : ");
    print_collection(numbers);
    std::println("numbers size : {}", numbers.size());

    std::println("");
    std::println("clear : ");
    print_collection(numbers);
    numbers.clear();
    print_collection(numbers);
    std::println("numbers size : {}", numbers.size());

    numbers = {10, 20, 30, 40, 50, 60};
    std::println("after reassignment : ");
    print_collection(numbers);

    // insert() places the new element in front of the given iterator.
    std::println("");
    std::println("insert : ");
    auto it_pos = numbers.begin() + 2;
    print_collection(numbers);

    numbers.insert(it_pos, 300);
    print_collection(numbers);
    // it_pos moves as elements are added, still pointing at the same
    // position (index 2) even though what's stored there has changed.
    numbers.insert(it_pos, 400);
    print_collection(numbers);

    std::println("");
    std::println("emplace : ");
    print_collection(numbers);
    auto it_item_pos = numbers.begin() + 2;
    numbers.emplace(it_item_pos, 45); // forwarded straight to a constructor
    print_collection(numbers);

    std::println("");
    std::println("erase : ");
    print_collection(numbers);
    numbers.erase(numbers.begin() + 4);
    print_collection(numbers);
    numbers.erase(numbers.begin() + 1, numbers.begin() + 4);
    print_collection(numbers);

    std::println("");
    std::println("emplace_back : ");
    print_collection(numbers);
    numbers.emplace_back(10);
    numbers.emplace_back(11);
    numbers.emplace_back(12);
    print_collection(numbers);

    std::println("");
    std::println("pop_back : ");
    print_collection(numbers);
    numbers.pop_back();
    print_collection(numbers);
    numbers.pop_back();
    print_collection(numbers);
    numbers.pop_back();
    print_collection(numbers);

    std::println("");
    std::println("resize : ");
    std::println("resize (Before) : ");
    print_collection(numbers);
    std::println("numbers size : {}", numbers.size());

    numbers.resize(30);
    print_collection(numbers);
    std::println("after resize : ");
    std::println("numbers size : {}", numbers.size());

    numbers.resize(10); // resizing down again - can even resize down
    print_collection(numbers);

    std::println("");
    std::println("swap : ");
    std::deque<Item> other_items = {Item(100), Item(200), Item(300)};

    std::print("items : ");
    print_collection(items);
    std::print("other_items : ");
    print_collection(other_items);

    other_items.swap(items);

    std::println("after swap : ");
    std::print("items : ");
    print_collection(items);
    std::print("other_items : ");
    print_collection(other_items);

    return 0;
}
