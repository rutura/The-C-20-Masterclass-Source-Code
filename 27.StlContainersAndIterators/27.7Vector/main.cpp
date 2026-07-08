#include <print>
#include <vector>

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

int main() {

    // A few different ways to construct a vector.
    std::vector<std::string> vec_str{"The", "sky", "is", "blue", "my", "friend"};
    std::println("vec_str[1] : {}", vec_str[1]);
    print_collection(vec_str);

    std::println("------");

    std::vector<int> ints1; // empty, no elements at all
    std::print("ints1 : ");
    print_collection(ints1);

    std::vector<int> ints2 = {1, 2, 3, 4};
    std::vector<int> ints3{11, 22, 33, 44};

    std::print("ints2 : ");
    print_collection(ints2);
    std::print("ints3 : ");
    print_collection(ints3);

    std::vector<int> ints4(20, 55); // 20 elements, all initialized to 55 - the (count, value) constructor
    std::print("ints4 : ");
    print_collection(ints4);

    // Brace-init reads differently here: {20, 55} is a 2-element vector
    // containing 20 and 55, not "20 elements of 55" like the constructor above.
    std::vector<int> ints5{20, 55};
    std::print("ints5 : ");
    print_collection(ints5);

    std::println("");
    std::println("Element access : ");
    std::println("vec_str[2] : {}", vec_str[2]);
    std::println("vec_str.at(3) : {}", vec_str.at(3));
    std::println("vec_str.front() : {}", vec_str.front());
    std::println("vec_str.back() : {}", vec_str.back());

    std::println("");
    std::println("Iterators : ");

    auto it = ints2.begin();
    std::print(" Vector(With iterators) : [ ");
    while (it != ints2.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println(" ]");

    auto it_reverse = ints2.rbegin(); // non-const reverse iterator
    std::print(" Vector(Reverse traversal with iterators) : [ ");
    while (it_reverse != ints2.rend()) {
        std::print(" {}", *it_reverse);
        ++it_reverse; // increments towards the first element
    }
    std::println(" ]");

    std::println("");
    std::println("capacity : ");
    std::print(" ints2 : ");
    print_collection(ints2);
    std::println(" ints2 size : {}", ints2.size());
    std::println(" ints2 max_size : {}", ints2.max_size());
    std::println(" ints2 is empty : {}", ints2.empty());
    std::println(" ints2 capacity : {}", ints2.capacity());

    ints2.push_back(20);
    std::print(" ints2 (after push_back) : ");
    print_collection(ints2);
    std::println(" ints2 capacity : {}", ints2.capacity());

    ints2.shrink_to_fit();
    std::print(" ints2 (after shrink_to_fit) : ");
    print_collection(ints2);
    std::println(" ints2 capacity : {}", ints2.capacity());

    ints2.reserve(20);
    std::print(" ints2 (after reserve) : ");
    print_collection(ints2);
    std::println(" ints2 size : {}", ints2.size());
    std::println(" ints2 capacity : {}", ints2.capacity());

    std::println("");
    std::println("clear : ");
    print_collection(ints2);

    ints2.clear();
    print_collection(ints2);
    std::println(" ints2 size : {}", ints2.size());
    std::println(" ints2 capacity : {}", ints2.capacity());

    ints2 = {10, 20, 30, 40, 50, 60};
    print_collection(ints2);

    // insert()'s second argument is inserted right before the position
    // referred to by the iterator passed as its first argument.
    std::println("");
    std::println("insert : ");
    std::print(" ints2(before insert) : ");
    print_collection(ints2);

    auto it_pos = ints2.begin() + 2;
    std::println("*it_pos : {}", *it_pos);

    ints2.insert(it_pos, 300);
    // it_pos still points at position 2, but as elements are inserted before
    // it, what's actually stored there keeps changing - originally 30, now
    // whatever ends up landing at that position.
    ints2.insert(it_pos, 400);
    std::print(" ints2 (after insert 300,400) : ");
    print_collection(ints2);
    std::println("*it_pos : {}", *it_pos);

    // Emplace: everything after the iterator is forwarded straight to a
    // constructor of the stored type, instead of building a temporary first.
    std::println("");
    std::println("emplace : ");
    std::vector<Item> items{Item(6), Item(7), Item(8), Item(9), Item(10)};
    print_collection(items);

    auto it_item_pos = items.begin() + 2;
    items.emplace(it_item_pos, 45, 10);
    print_collection(items);

    std::println("");
    std::println("erase : ");
    print_collection(items);
    items.erase(items.begin() + 4);
    print_collection(items);

    items.erase(items.begin() + 1, items.begin() + 4);
    print_collection(items);

    std::println("");
    std::println("emplace_back : ");
    print_collection(items);
    items.emplace_back(10, 10); // equivalent to items.emplace(items.end(), 10, 10)
    items.emplace_back(10, 11);
    items.emplace_back(10, 12);
    print_collection(items);

    std::println("");
    std::println("pop_back : ");
    print_collection(items);
    items.pop_back();
    print_collection(items);

    std::println("");
    std::println("resize (Before) : ");
    print_collection(items);
    std::println("items size : {}", items.size());
    std::println("items capacity : {}", items.capacity());

    items.resize(11); // note the default constructors called to fill the new slots
    print_collection(items);
    std::println("after resize : ");
    std::println("items size : {}", items.size());
    std::println("items capacity : {}", items.capacity());

    std::println("");
    std::println("swap : ");
    std::vector<Item> other_items = {Item(22), Item(33), Item(44)};

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
