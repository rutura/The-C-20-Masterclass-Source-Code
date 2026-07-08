#include <algorithm>
#include <format>
#include <functional>
#include <print>
#include <set>
#include <string>

class Book {
public:
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

    // A set keeps its data ordered internally and rejects duplicates - it
    // needs operator< to know how to order elements.
    std::set<int> numbers{11, 16, 2, 912, 15, 6, 15, 2};
    std::println("");
    std::println("building sets (Need < operator for ordering) : ");
    print_collection(numbers);

    std::set<Book> books{Book(2000, "Cooking Food"), Book(1930, "Building Computers"), Book(1995, "Farming for Beginners")};
    print_collection(books);
    std::println("---------------------");

    std::println("");
    std::println("iterators : ");
    auto it = numbers.begin();
    std::print("set of numbers : [");
    while (it != numbers.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println("]");

    auto it_back = numbers.rbegin();
    std::print("set of numbers (reverse) : [");
    while (it_back != numbers.rend()) {
        std::print(" {}", *it_back);
        ++it_back;
    }
    std::println("]");

    auto it_back_books = books.rbegin();
    std::print("set of books (reverse) : [");
    while (it_back_books != books.rend()) {
        std::print(" {}", *it_back_books);
        ++it_back_books;
    }
    std::println("]");

    std::println("---------------------");
    std::println("");
    std::println("capacity : ");
    std::print("numbers : ");
    print_collection(numbers);
    std::println("set max_size : {}", numbers.max_size());
    std::println("set is empty : {}", numbers.empty());
    std::println("set size : {}", numbers.size());

    std::println("---------------------");

    std::println("");
    std::println("clear :");
    print_collection(numbers);
    numbers.clear();
    print_collection(numbers);
    std::println("numbers is empty : {}", numbers.empty());

    // Insert returns a pair with an iterator and a bool telling you whether
    // it actually inserted anything - a set silently does nothing on a
    // duplicate rather than raising an error.
    std::println("");
    std::println("Insert : ");
    numbers = {11, 12, 13, 14, 15};
    print_collection(numbers);

    numbers.insert(14); // won't insert - 14 is already there
    std::print("After insert 14 : ");
    print_collection(numbers);

    std::println("-------");
    auto result = numbers.insert(20);

    std::println("first : {}", *result.first);
    std::println("second : {}", result.second);

    std::println("------");
    if (result.second) {
        std::println("Insertion of {} successful", *result.first);
    } else {
        std::println("Couldn't insert {} in the set. It's a duplicate!", *result.first);
    }
    print_collection(numbers);

    std::println("");
    std::println("emplace : ");
    print_collection(numbers);
    auto result_emplace = numbers.emplace(13); // fails - 13 is already there

    if (result_emplace.second) {
        std::println("Emplace of {} successful", *result_emplace.first);
    } else {
        std::println("Emplace of {} FAILED", *result_emplace.first);
    }
    print_collection(numbers);

    std::println("");
    std::println("erase : ");
    print_collection(numbers);
    auto it_erase = std::find(numbers.begin(), numbers.end(), 13);

    if (it_erase != numbers.end()) {
        std::println("Found 13 !");
    } else {
        std::println("Couldn't find 13 !");
    }

    if (it_erase != numbers.end())
        numbers.erase(it_erase);
    print_collection(numbers);

    std::println("");
    std::println("swap : ");
    std::set<int> other_numbers{200, 400, 600};

    std::print("numbers : ");
    print_collection(numbers);
    std::print("other_numbers : ");
    print_collection(other_numbers);

    numbers.swap(other_numbers);

    std::print("numbers : ");
    print_collection(numbers);
    std::print("other_numbers : ");
    print_collection(other_numbers);

    // A set's comparator is part of its type - std::less (default),
    // std::greater, a custom functor, or a lambda captured through
    // std::function (the most flexible, but the slowest option, since it
    // adds a layer of indirection every comparison has to go through).
    std::println("");
    std::println("change comparator : ");
    std::set<int, std::function<bool(int, int)>> numbers1([](int left, int right) { return left > right; });
    numbers1.insert({11, 16, 2, 9, 12, 15, 6, 15, 2});

    std::print("numbers1 :[ ");
    for (const auto& elt : numbers1) {
        std::print(" {}", elt);
    }
    std::println("]");

    return 0;
}
