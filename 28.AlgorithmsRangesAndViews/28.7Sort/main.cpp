#include <print>
#include <algorithm>
#include <format>
#include <string>
#include <vector>

class Book {
public:
    Book(int year, std::string title) : m_year(year), m_title(title) {}

    bool operator<(const Book& right_operand) const { return this->m_year < right_operand.m_year; }
    bool operator>(const Book& right_operand) const { return this->m_year > right_operand.m_year; }
    bool operator==(const Book& right_operand) const { return this->m_year == right_operand.m_year; }

    int m_year;
    std::string m_title;
};

// std::print/std::format need a std::formatter specialization to know how
// to render a custom type - there's no automatic fallback to operator<<.
template <>
struct std::formatter<Book> : std::formatter<std::string> {
    auto format(const Book& book, std::format_context& ctx) const {
        return std::formatter<std::string>::format(
            std::format("Book [{}, {}]", book.m_year, book.m_title), ctx);
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

    // Sorting with the type's own operator<
    std::vector<int> collection{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    std::print("collection(unsorted) : ");
    print_collection(collection);

    std::sort(collection.begin(), collection.end());

    std::print("collection(sorted) : ");
    print_collection(collection);

    std::println("---------------------------");

    // Sorting with an explicit comparator
    collection = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3};

    std::print("collection(unsorted) : ");
    print_collection(collection);

    std::sort(collection.begin(), collection.end(), [](int x, int y) { return x < y; });

    std::print("collection(sorted) : ");
    print_collection(collection);

    std::println("--------------------------");

    // Sorting a collection of custom objects requires either operator< on
    // the type or an explicit comparator - here a comparator, since sorting
    // by year is only one of several orderings Book could reasonably have.
    std::vector<Book> books{Book(1734, "Cooking Food"),
                             Book(2000, "Building Computers"),
                             Book(1995, "Farming for Beginners")};

    std::println("books(before sort) : ");
    print_collection(books);

    auto cmp = [](const Book& book1, const Book& book2) { return book1.m_year < book2.m_year; };

    std::sort(books.begin(), books.end(), cmp);

    std::println("books(after sort) : ");
    print_collection(books);

    return 0;
}