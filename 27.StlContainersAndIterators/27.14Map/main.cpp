#include <format>
#include <functional>
#include <map>
#include <print>
#include <string>

class Book {
public:
    Book() = default;
    Book(int year, std::string title) : m_year(year), m_title(title) {}
    bool operator<(const Book& right_operand) const { return this->m_year < right_operand.m_year; }

    int m_year;
    std::string m_title;
};

template <>
struct std::formatter<Book> : std::formatter<std::string> {
    auto format(const Book& book, std::format_context& ctx) const {
        return std::formatter<std::string>::format(
            std::format("Book [{}, {}]", book.m_year, book.m_title), ctx);
    }
};

template <typename T, typename K>
void print_map(const std::map<T, K>& map) {
    auto it = map.begin();
    std::print(" map of elements : [");
    while (it != map.end()) {
        std::print(" [{},{}]", it->first, it->second);
        ++it;
    }
    std::println(" ]");
}

int main() {

    // Elements are always stored ordered by key, regardless of insertion order.
    std::println("");
    std::println("Creating maps : ");
    std::map<int, int> numbers{{1, 11}, {0, 12}, {4, 13}, {2, 14}, {3, 15}};
    std::print("numbers : ");
    print_map(numbers);

    std::map<int, Book> books{
        {2, Book(1734, "Cooking Food")},
        {0, Book(1930, "Building Computers")},
        {1, Book(1995, "Farming for Beginners")}};
    std::print("books : ");
    print_map(books);

    std::println("--------------------------------------");

    // A std::map is really a collection of std::pair's - these three loops
    // all traverse it the same way, in increasing key order.
    std::println("");
    std::println("Looping around printing stuff : ");
    std::println("");
    std::println("printing books with structured bindings (C++17) :");
    for (const auto& [key, value] : books) {
        std::println("  book [ {} ]:{}", key, value);
    }

    std::println("");
    std::println("Traverse map with C++11 loop syntax : ");
    for (const auto& elt : books) {
        std::println("  book [{} ] : {}", elt.first, elt.second);
    }

    std::println("");
    std::println("traverse map with loop (with explicit types) : ");
    for (const std::pair<const int, Book>& elt : books) {
        std::println("  book [{} ] : {}", elt.first, elt.second);
    }

    std::println("--------------------------------------");

    std::println("");
    std::println("keys can be anything : std::string in this case (stored by key) : ");
    std::map<std::string, std::string> address_book;

    address_book["Daniel Gray"] = "Kigali, KG St 334 #56";
    address_book["Steve Moris"] = "Huye, SH St 27 #78";
    address_book["John Snow"] = "Musanze, NM St 33 #89";
    address_book["Henry King"] = "Muhanga, SM St 128 #3";

    for (const auto& [key, value] : address_book) {
        std::println(" {} lives at address : {}", key, value);
    }

    std::println("--------------------------------------");

    std::println("");
    std::println("Iterators : ");
    auto it_access = numbers.begin();
    std::print("numbers (forward iterators) : [");
    while (it_access != numbers.end()) {
        std::print(" {}", numbers[it_access->first]);
        ++it_access;
    }
    std::println("]");

    std::println("");
    std::println("modifying elements through iterators : ");
    print_map(numbers);

    auto it_modify = numbers.begin();
    while (it_modify != numbers.end()) {
        numbers[it_modify->first] = 222;
        ++it_modify;
    }
    print_map(numbers);

    // operator[] default-constructs a value if the key isn't already
    // present - this loop only ever reads existing keys, but operator[]
    // can't tell that at compile time, so Book still needs a default
    // constructor to satisfy it.
    std::println("");
    std::println("(iterators) set of books (reverse) :");
    auto it_back_books = books.rbegin();
    while (it_back_books != books.rend()) {
        std::println(" {} - {}", it_back_books->first, books[it_back_books->first]);
        ++it_back_books;
    }

    std::println("---------------------");
    std::println("");
    std::println("capacity : ");
    std::print("numbers : ");
    print_map(numbers);
    std::println("map max_size : {}", numbers.max_size());
    std::println("map is empty : {}", numbers.empty());
    std::println("map size : {}", numbers.size());

    std::println("---------------------");

    std::println("");
    std::println("clear :");
    std::print("numbers : ");
    print_map(numbers);
    numbers.clear();
    std::print("numbers : ");
    print_map(numbers);
    std::println("numbers is empty : {}", numbers.empty());

    std::println("");
    std::println("insert : ");
    numbers = {{0, 11}, {1, 12}, {2, 13}, {3, 14}, {4, 15}};
    print_map(numbers);

    numbers.insert({2, 44}); // won't insert - key 2 already exists, maps don't allow duplicate keys
    std::print("After insert {{2,44}} : ");
    print_map(numbers);

    auto result = numbers.insert({6, 17});
    std::println("result.second : {}", result.second);

    if (result.second) {
        std::println("Insertion successful");
    } else {
        std::println("Couldn't insert in the map. It's a duplicate!");
    }
    print_map(numbers);

    std::println("");
    std::println("emplace : ");
    std::print("before emplace : ");
    print_map(numbers);

    auto result_emplace = numbers.emplace(std::make_pair(7, 18));

    if (result_emplace.second) {
        std::println("Emplace  successful");
    } else {
        std::println("Emplace  FAILED");
    }

    std::print("after emplace : ");
    print_map(numbers);

    std::println("");
    std::println("erase : ");
    print_map(numbers);

    auto it_erase = numbers.find(3); // find the element with key 3

    if (it_erase != numbers.end()) {
        std::println("Found element with key {} ! : {}", it_erase->first, it_erase->second);
    } else {
        std::println("Couldn't find element with key 3 !");
    }

    if (it_erase != numbers.end())
        numbers.erase(it_erase);
    print_map(numbers);

    // A map's comparator is part of its type, same as set's - std::less
    // (default), std::greater, a custom functor, or a captured lambda
    // through std::function.
    std::println("");
    std::println("Changing comparators : ");
    std::map<int, int, std::function<bool(int, int)>> numbers2([](int left, int right) { return left > right; });
    numbers2.insert({{1, 11}, {0, 12}, {4, 13}, {2, 14}, {3, 15}});

    std::print("numbers2 : [ ");
    for (const auto& [key, value] : numbers2) {
        std::print(" ({},{})", key, value);
    }
    std::println("]");

    return 0;
}
