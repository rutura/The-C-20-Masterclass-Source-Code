#include <fmt/format.h>
#include <queue>



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
        return this->m_year < right_operand.m_year; // original prioriy: bigger year comes to the top.
        //return this->m_year > right_operand.m_year; // reverses original priorities : smaller year comes to the top. 
        //return this->m_title < right_operand.m_title; //Orders by titles in reverse order ( D,C,B,A,...).
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


//template <typename T>
//void print_priority_queue(std::priority_queue<T> p_queue){

template<typename T,
                    typename Container = std::vector<T>,
                    typename Compare = std::less<typename Container::value_type>>  
void print_priority_queue(std::priority_queue<T,Container,Compare> p_queue){ 
    
    fmt::print( "priority queue of elements : [");
    while(!p_queue.empty()){
        fmt::print( " {}",  p_queue.top() );
        p_queue.pop();
    }
    fmt::println( "]" );
    
}


//template <typename T>
//void clear_queue(std::priority_queue<T>& p_queue){

template<typename T,
                    typename Container = std::vector<T>,
                    typename Compare = std::less<typename Container::value_type>>  
void clear_queue(std::priority_queue<T,Container,Compare>& p_queue){ 
    
    fmt::print( "Clearing priority queue of size : {}" ,p_queue.size() );
    while(!p_queue.empty()){
        p_queue.pop();
    }
    
}



int main(){

    //Code1 : Creating  pushing and accessing
    std::priority_queue<int> numbers1; // The greatest has higher priority
    
    fmt::print( " numbers1 : ");
    print_priority_queue(numbers1);
    
    numbers1.push(10);
    numbers1.push(8);
    numbers1.push(12);
    
    fmt::print( " numbers1 : ");
    print_priority_queue(numbers1);
    
    numbers1.push(11);
    numbers1.push(3);
    
    fmt::print( " numbers1 : ");
    print_priority_queue(numbers1);
    
    //Acess
    fmt::println( " numbers1.top() :  {}",  numbers1.top() );


    //Code2 : Can't through top to modify top element : this is
    //because top() returns  a CONST reference.
    fmt::println("");
    fmt::println( "modify top element through top():" );
    
    fmt::print( " numbers1 (before modification) : ");
    print_priority_queue(numbers1);
    
    //numbers1.top() = 500; // Compiler error

    fmt::print( " numbers1 (after modification) : ");
    print_priority_queue(numbers1);


    //Code3 : poping : Pops the highest priority element
    fmt::println("");
    fmt::println( "poping data : " );
    
    fmt::print( " numbers1 : ");
    print_priority_queue(numbers1);
    
    numbers1.pop();
    
    fmt::print( " numbers1 : ");
    print_priority_queue(numbers1);
    
    numbers1.pop();
    
    fmt::print( " numbers1 : ");
    print_priority_queue(numbers1);

    //Code4 : Clearing a priority queue
    fmt::println("");
    fmt::println( "clearing a priority queue : " );
    
    fmt::println( " priority queue initial size : {}" , numbers1.size() );
    fmt::print( " numbers1 (before) : ");
    print_priority_queue(numbers1);
    
    clear_queue(numbers1);
    
    fmt::print( " priority_queue final size : {}" , numbers1.size() );
    fmt::print( " numbers1(after) : ");
    print_priority_queue(numbers1);


    //Code5 : priority_queue of user defined types
    fmt::println("");
    fmt::print( "priority queue of user defined type :" );
    
    std::priority_queue<Book> books;
    
    //ATTETION : Notice the effects of changing operator< to do a different comparison
    //mechanism and how that affects the priorities perceived by the priority queue
    //this can  be seen in the order the elements are printed in by print_priority_queue : 
    //it starts from the top.
    
    books.push(Book(1921,"Art of War"));
    books.push(Book(2020,"Building Social Media Marketing Strategies"));
    books.push(Book(1990,"Converging Lines of Modern Economy"));
    books.push(Book(1998,"Driving Current Triggered Transistors"));
    
    fmt::print( "books : ");
    print_priority_queue(books);
    fmt::println( "books size : {}" , books.size() );
    fmt::println( "top book : {}" , books.top() );


   //Code6 : specify a custom comparator and/or underlying container
    fmt::println("");
    fmt::print( "changing the comparator and underlying container : " );
    
    //std::priority_queue<int, std::vector<int>, std::less<int> > numbers2; // Default. 
                                       // Works with single template parameter functions
    //std::priority_queue<int, std::vector<int>, std::greater<int> > numbers2; // Non default,
                //compiler doesn't generate correct template instances,
                //we need to be explicit in our print and clear functions
    //std::priority_queue<int, std::deque<int>, std::greater<int> > numbers2;
    
    //Using your own functor
   
    auto cmp = [](int left, int right) { return left < right; };
    //This uses a different constructor. Let's be honest, this syntax is weird.
    std::priority_queue<int, std::vector<int>, decltype(cmp)> numbers2(cmp);
  
   
    numbers2.push(10);
    numbers2.push(8);
    numbers2.push(12);
    
    fmt::print( " numbers2 : ");
    print_priority_queue(numbers2);
    
   
    return 0;
}