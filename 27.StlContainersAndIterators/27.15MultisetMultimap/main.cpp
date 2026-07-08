#include <format>
#include <map>
#include <print>
#include <set>
#include <string>
#include <utility>

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

template <typename T>
void print_multiset(const std::multiset<T>& m_set) {
    auto it = m_set.begin();
    std::print("multiset of elements : [");
    while (it != m_set.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println("]");
}

template <typename T, typename K>
void print_multimap(const std::multimap<T, K>& m_map) {
    auto it = m_map.begin();
    std::print("multimap of elements : [");
    while (it != m_map.end()) {
        std::print(" [{},{}]", it->first, it->second);
        ++it;
    }
    std::println("]");
}

int main() {

    // Unlike set/map, multiset/multimap allow duplicate keys - notice 2, 6,
    // and the 1930s Book both appear more than once here.
    std::multiset<int> numbers = {1, 2, 1, 6, 2, 8, 3, 9, 4, 24, 6, 2};
    std::multiset<Book> books = {Book(1734, "Cooking Food"), Book(1930, "Building Computers"), Book(1734, "Farming for Beginners")};

    std::print("numbers : ");
    print_multiset(numbers);
    std::print("books : ");
    print_multiset(books);

    std::println("");
    std::println("multimap : ");

    std::multimap<int, std::string> office_numbers = {
        std::make_pair(101, "Daniel Gray"),
        std::make_pair(102, "John Snow"),
        std::make_pair(103, "Jamie Lanister"),
        std::make_pair(102, "Van Gomir"),
        std::make_pair(101, "Kay Moris"),
        std::make_pair(102, "Zuba Loy"),
    };

    std::print("office_numbers : ");
    print_multimap(office_numbers);

    std::multimap<int, Book> other_books = {
        std::make_pair(0, Book(1734, "Cooking Food")),
        std::make_pair(1, Book(1930, "Building Computers")),
        std::make_pair(1, Book(1995, "Farming for Beginners"))};

    std::print("other_books : ");
    print_multimap(other_books);

    // Most other operations mirror std::set/std::map - see the standard
    // library reference for the full list.

    return 0;
}
