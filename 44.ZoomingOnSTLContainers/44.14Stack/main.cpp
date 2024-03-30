#include <fmt/format.h>
#include <stack>
#include <vector>
#include <list>
#include <deque>


class Book{
    friend std::ostream& operator<< (std::ostream& out, const Book& operand);
    friend struct fmt::formatter<Book>;

public : 
    Book() = default;
    Book(int year, std::string title) 
        : m_year(year),m_title(title)
        {
        }
        
    bool operator< (const Book & right_operand)const{
        return this->m_year < right_operand.m_year;
    }
    
private : 
    int m_year;
    std::string m_title;
};

std::ostream& operator<< (std::ostream& out, const Book& operand){
    out << "Book [" << operand.m_year << ", " << operand.m_title << "]";
    return out;
}

template<>
struct fmt::formatter<Book> {
    constexpr auto parse(format_parse_context& ctx){return ctx.begin(); }
    template<typename FormatContext>
    auto format(const Book& obj, FormatContext& ctx) {
        return format_to(ctx.out(), "Book [{},{}]", obj.m_year, obj.m_title);
    }
};


template<typename T, typename Container = std::deque<T>>
void print_stack(std::stack<T,Container> stack){

//template <typename T>
//void print_stack(std::stack<T> stack){


    //Notice that we're working on a copy here. IMPORTANT
    fmt::print( "stack of elements : [");
    while(!stack.empty()){
        T item = stack.top();
        fmt::print( " {}",  item );
        stack.pop(); // Poping from a copy doesn't affect the original. We're good here.
    }
    fmt::println( "]");
}

template <typename T, typename Container = std::deque<T>>
void clear_stack(std::stack<T,Container>& stack){
//template <typename T>
//void clear_stack(std::stack<T>& stack){

    fmt::println( "Clearing stack of size : {}",  stack.size());
    while(!stack.empty()){
        stack.pop();
    }
}


int main(){
    //Code1 : Creating std::stacks and storing data in
    std::stack<int> numbers1;
    
    fmt::print( " numbers1 : ");
    print_stack(numbers1); // empty
    
    numbers1.push(10);
    numbers1.push(20);
    numbers1.push(30);
    
    fmt::print( "numbers1 : ");
    print_stack(numbers1); // 30 20 10 : FILO

    numbers1.push(40);
    numbers1.push(50);
    
    fmt::print( "numbers1 : ");
    print_stack(numbers1); // 50 40 30 20 10  : FILO

    fmt::println( "-----" );

    //Accessing elements
    fmt::println( "top : {}" ,  numbers1.top());
    //Pop off the top
    print_stack(numbers1);
    numbers1.pop();
    print_stack(numbers1);
    fmt::println( "top : {}", numbers1.top());
    
    //We can organize these calls to top and pop into a function 
    // that can nicely show the contents of a stack. That's what print_stack does

    fmt::println( "-----");

    //Code2 : Modifying the top element through the reference returned by top()
    //top() returns a reference. We can use that to modify the underlying 
    //element in the stack
    fmt::print( "numbers1 : ");
    print_stack(numbers1); 
    
    numbers1.top() = 55;
    
    fmt::print( "numbers1 : ");
    print_stack(numbers1); 


    //Code3 : Clearing a stack
    fmt::print("");
    fmt::println( "clearing a stack : " );
    
    fmt::println( "stack initial size : {}" , numbers1.size() );
    fmt::print( "numbers1 (before) : ");
    print_stack(numbers1);
    
    clear_stack(numbers1);
    
    fmt::println( "stack final size : {}" , numbers1.size() );
    fmt::print( "numbers1(after) : ");
    print_stack(numbers1);


    //Code4 : Stack of user defined types
    std::stack<Book> books;
    books.push(Book(1921,"The Art of War"));
    books.push(Book(2000,"Social Media Marketing"));
    books.push(Book(2020,"How the Pandemic Changed the World"));
    
    fmt::print( "books : ");
    print_stack(books);
    fmt::println( "books size : {}" , books.size() );


    //Custom underlying sequence container
    
    std::stack<int,std::vector<int>> numbers2;
    std::stack<int,std::list<int>> numbers3;
    std::stack<int,std::deque<int>> numbers4;
    
    numbers2.push(5); // underlying container : std::vector
    numbers2.push(6);
    
    numbers3.push(7);   // underlying container : std::list
    numbers3.push(8);
    
    numbers4.push(9);   //  underlying container : std::deque
    numbers4.push(10);


    fmt::print( " numbers4 : ");
    print_stack(numbers4); // OK 

    fmt::print( " numbers3 : ");
    print_stack(numbers3); // Compiler error

    fmt::print( " numbers2 : ");
    print_stack(numbers2); // Compiler error

    return 0;
}