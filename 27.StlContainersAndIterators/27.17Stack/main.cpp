#include <deque>
#include <format>
#include <list>
#include <print>
#include <stack>
#include <string>
#include <vector>

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

// Container defaults to deque, but a stack can be built on top of any
// sequence container that supports back()/push_back()/pop_back() - vector
// and list both qualify too, which is what the last section below shows.
template <typename T, typename Container = std::deque<T>>
void print_stack(std::stack<T, Container> stack) {
    // Working on a copy here - popping it doesn't affect the caller's stack.
    std::print("stack of elements : [");
    while (!stack.empty()) {
        T item = stack.top();
        std::print(" {}", item);
        stack.pop();
    }
    std::println("]");
}

template <typename T, typename Container = std::deque<T>>
void clear_stack(std::stack<T, Container>& stack) {
    std::println("Clearing stack of size : {}", stack.size());
    while (!stack.empty()) {
        stack.pop();
    }
}

int main() {

    std::stack<int> numbers1;

    std::print("numbers1 : ");
    print_stack(numbers1); // empty

    numbers1.push(10);
    numbers1.push(20);
    numbers1.push(30);

    std::print("numbers1 : ");
    print_stack(numbers1); // 30 20 10 - last in, first out

    numbers1.push(40);
    numbers1.push(50);

    std::print("numbers1 : ");
    print_stack(numbers1); // 50 40 30 20 10

    std::println("-----");

    std::println("top : {}", numbers1.top());
    print_stack(numbers1);
    numbers1.pop();
    print_stack(numbers1);
    std::println("top : {}", numbers1.top());

    std::println("-----");

    // top() returns a reference, so it can be used to modify the element in place.
    std::print("numbers1 : ");
    print_stack(numbers1);
    numbers1.top() = 55;
    std::print("numbers1 : ");
    print_stack(numbers1);

    std::println("");
    std::println("clearing a stack : ");
    std::println("stack initial size : {}", numbers1.size());
    std::print("numbers1 (before) : ");
    print_stack(numbers1);

    clear_stack(numbers1);

    std::println("stack final size : {}", numbers1.size());
    std::print("numbers1(after) : ");
    print_stack(numbers1);

    std::println("");
    std::println("stack of user defined types : ");
    std::stack<Book> books;
    books.push(Book(1921, "The Art of War"));
    books.push(Book(2000, "Social Media Marketing"));
    books.push(Book(2020, "How the Pandemic Changed the World"));

    std::print("books : ");
    print_stack(books);
    std::println("books size : {}", books.size());

    std::println("");
    std::println("custom underlying sequence container : ");
    std::stack<int, std::vector<int>> numbers2;
    std::stack<int, std::list<int>> numbers3;
    std::stack<int, std::deque<int>> numbers4;

    numbers2.push(5); // underlying container: std::vector
    numbers2.push(6);

    numbers3.push(7); // underlying container: std::list
    numbers3.push(8);

    numbers4.push(9); // underlying container: std::deque
    numbers4.push(10);

    // print_stack's Container template parameter deduces to whatever
    // container each stack actually uses - vector, list, and deque all work
    // here without any changes to print_stack itself.
    std::print("numbers4 : ");
    print_stack(numbers4);

    std::print("numbers3 : ");
    print_stack(numbers3);

    std::print("numbers2 : ");
    print_stack(numbers2);

    return 0;
}
