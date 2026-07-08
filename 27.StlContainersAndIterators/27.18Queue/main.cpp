#include <deque>
#include <format>
#include <list>
#include <print>
#include <queue>
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

template <typename T, typename Container = std::deque<T>>
void print_queue(std::queue<T, Container> queue) {
    std::print(" queue of items : [");
    while (!queue.empty()) {
        T item = queue.front();
        std::print(" {}", item);
        queue.pop();
    }
    std::println("]");
}

template <typename T, typename Container = std::deque<T>>
void clear_queue(std::queue<T, Container>& queue) {
    std::println(" Clearing queue of size : {}", queue.size());
    while (!queue.empty()) {
        queue.pop();
    }
}

int main() {

    std::println("Creating pushing and accessing : ");
    std::queue<int> numbers1;

    std::print(" numbers1 : ");
    print_queue(numbers1);

    numbers1.push(10);
    numbers1.push(20);
    numbers1.push(30);

    std::print(" numbers1 : ");
    print_queue(numbers1);

    numbers1.push(40);
    numbers1.push(50);

    std::print(" numbers1 : ");
    print_queue(numbers1);

    std::println(" numbers1.front() : {}", numbers1.front());
    std::println(" numbers1.back() : {}", numbers1.back());

    // front()/back() both return references, so they can modify in place too.
    std::println("");
    std::println("modify top element through front and back :");
    std::print(" numbers1 (before modification) : ");
    print_queue(numbers1);

    numbers1.front() = 500;
    numbers1.back() = 600;

    std::print(" numbers1 (after modification) : ");
    print_queue(numbers1);

    std::println("");
    std::println("poping data : ");
    std::print(" numbers1 : ");
    print_queue(numbers1);

    numbers1.pop();
    std::print(" numbers1 : ");
    print_queue(numbers1);

    numbers1.pop();
    std::print(" numbers1 : ");
    print_queue(numbers1);

    std::println("");
    std::println("clearing a queue : ");
    std::println(" queue initial size : {}", numbers1.size());
    std::print(" numbers1 (before) : ");
    print_queue(numbers1);

    clear_queue(numbers1);

    std::println(" queue final size : {}", numbers1.size());
    std::print(" numbers1(after) : ");
    print_queue(numbers1);

    std::println("");
    std::println("queue of user defined type :");
    std::queue<Book> books;

    books.push(Book(1921, "The Art of War"));
    books.push(Book(2000, "Social Media Marketing"));
    books.push(Book(2020, "How the Pandemic Changed the World"));

    std::print(" books : ");
    print_queue(books);
    std::println(" books size : {}", books.size());
    std::println(" front book : {}", books.front());
    std::println(" back book : {}", books.back());

    std::println("");
    std::println("custom underlying sequence container : ");
    std::queue<int, std::list<int>> numbers3;
    std::queue<int, std::deque<int>> numbers4;

    numbers3.push(3);
    numbers3.push(4);

    numbers4.push(5);
    numbers4.push(6);

    std::print(" numbers3 : ");
    print_queue(numbers3);

    std::print(" numbers4 : ");
    print_queue(numbers4);

    return 0;
}
