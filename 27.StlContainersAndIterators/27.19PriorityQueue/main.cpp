#include <format>
#include <functional>
#include <print>
#include <queue>
#include <string>
#include <vector>

class Book {
public:
    Book() = default;
    Book(int year, std::string title) : m_year(year), m_title(title) {}
    bool operator<(const Book& right_operand) const {
        return this->m_year < right_operand.m_year; // original priority: bigger year comes to the top
        // return this->m_year > right_operand.m_year; // reversed: smaller year comes to the top
        // return this->m_title < right_operand.m_title; // ordered by title, reverse alphabetical
    }

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

template <typename T,
          typename Container = std::vector<T>,
          typename Compare = std::less<typename Container::value_type>>
void print_priority_queue(std::priority_queue<T, Container, Compare> p_queue) {
    std::print("priority queue of elements : [");
    while (!p_queue.empty()) {
        std::print(" {}", p_queue.top());
        p_queue.pop();
    }
    std::println("]");
}

template <typename T,
          typename Container = std::vector<T>,
          typename Compare = std::less<typename Container::value_type>>
void clear_queue(std::priority_queue<T, Container, Compare>& p_queue) {
    std::println("Clearing priority queue of size : {}", p_queue.size());
    while (!p_queue.empty()) {
        p_queue.pop();
    }
}

int main() {

    std::priority_queue<int> numbers1; // the greatest value has the highest priority

    std::print(" numbers1 : ");
    print_priority_queue(numbers1);

    numbers1.push(10);
    numbers1.push(8);
    numbers1.push(12);

    std::print(" numbers1 : ");
    print_priority_queue(numbers1);

    numbers1.push(11);
    numbers1.push(3);

    std::print(" numbers1 : ");
    print_priority_queue(numbers1);

    std::println(" numbers1.top() : {}", numbers1.top());

    // top() returns a const reference - unlike stack/queue, there's no way
    // to modify the top element in place, since doing so could silently
    // break the heap's internal ordering.
    std::println("");
    std::println("modify top element through top():");
    std::print(" numbers1 (before modification) : ");
    print_priority_queue(numbers1);

    // numbers1.top() = 500; // compiler error: top() returns a const reference

    std::print(" numbers1 (after modification) : ");
    print_priority_queue(numbers1);

    std::println("");
    std::println("poping data : ");
    std::print(" numbers1 : ");
    print_priority_queue(numbers1);

    numbers1.pop(); // pops the highest-priority element
    std::print(" numbers1 : ");
    print_priority_queue(numbers1);

    numbers1.pop();
    std::print(" numbers1 : ");
    print_priority_queue(numbers1);

    std::println("");
    std::println("clearing a priority queue : ");
    std::println(" priority queue initial size : {}", numbers1.size());
    std::print(" numbers1 (before) : ");
    print_priority_queue(numbers1);

    clear_queue(numbers1);

    std::println(" priority_queue final size : {}", numbers1.size());
    std::print(" numbers1(after) : ");
    print_priority_queue(numbers1);

    // Changing Book::operator< changes what "priority" means for this type -
    // the print order below starts from the top, so it directly reflects
    // whichever comparison Book::operator< currently implements.
    std::println("");
    std::println("priority queue of user defined type :");
    std::priority_queue<Book> books;

    books.push(Book(1921, "Art of War"));
    books.push(Book(2020, "Building Social Media Marketing Strategies"));
    books.push(Book(1990, "Converging Lines of Modern Economy"));
    books.push(Book(1998, "Driving Current Triggered Transistors"));

    std::print("books : ");
    print_priority_queue(books);
    std::println("books size : {}", books.size());
    std::println("top book : {}", books.top());

    // A custom comparator (here, a lambda) changes the ordering without
    // touching Book::operator< at all - this constructor overload takes the
    // comparator instance directly.
    std::println("");
    std::println("changing the comparator and underlying container : ");
    auto cmp = [](int left, int right) { return left < right; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> numbers2(cmp);

    numbers2.push(10);
    numbers2.push(8);
    numbers2.push(12);

    std::print(" numbers2 : ");
    print_priority_queue(numbers2);

    return 0;
}
