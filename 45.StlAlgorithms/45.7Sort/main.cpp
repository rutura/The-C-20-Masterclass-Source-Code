#include <fmt/format.h>
#include <algorithm>
#include <vector>
#include <list>


class Book{
    friend std::ostream& operator<< (std::ostream& out, const Book& operand);
    friend struct fmt::formatter<Book>;
public : 

    Book(int year, std::string title) 
        : m_year(year),m_title(title)
        {
        }
        
    bool operator< (const Book & right_operand)const{
        return this->m_year < right_operand.m_year;
    }
    
    
   
    bool operator> (const Book & right_operand)const{
        return this->m_year > right_operand.m_year;
    }
   
      
    bool operator==(const Book&  right_operand)const{
        return (this->m_year == right_operand.m_year);
    }
   
    
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
        return format_to(ctx.out(), "Book [{}, {}]", obj.m_year,obj.m_title);
    }
};

template<typename T>
void print_collection( const T& collection){
    
    fmt::print( " Collection [" );
    for(const auto& elt : collection){
        fmt::print(" {}" , elt );
    }
    fmt::println( "]");
}



int main(){
    
    //Directly without predicate
    std::vector<int> collection = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
    
    fmt::print( "collection(unsorted) : ");
    print_collection(collection);
    
    std::sort(std::begin(collection),std::end(collection));
    
    fmt::print( "collection(sorted) : ");
    print_collection(collection);
    
    
    fmt::print( "---------------------------" );

    //With custom compare function
    collection = {5, 7, 4, 2, 8, 6, 1, 9, 0, 3}; 
    
    fmt::print( "collection(unsorted) : ");
    print_collection(collection);
    
    //std::sort(std::begin(collection),std::end(collection),std::less<int>());
    //std::sort(std::begin(collection),std::end(collection),std::greater<int>());
    std::sort(std::begin(collection),std::end(collection),[](int x, int y){return x < y;});
    
    fmt::print( "collection(sorted) : ");
    print_collection(collection);
    
    
    fmt::print( "--------------------------" );

    //Sorting collections of custom items
    std::vector<Book> books {Book(1734,"Cooking Food"),
                    Book(2000,"Building Computers"),Book(1995,"Farming for Beginners")};
                    
                    
    fmt::print( "books(before sort) : " );
    print_collection(books);
    
    //std::sort(std::begin(books),std::end(books));
    //std::sort(std::begin(books),std::end(books),std::less<Book>());
    //std::sort(std::begin(books),std::end(books),std::greater<Book>());
                                                                // Will look for > operator.
                                                                // Put it in and make the compiler
                                                                //happy

    
    auto cmp = [](const Book& book1, const Book& book2){
        return (book1.m_year < book2.m_year);
    };
  
    std::sort(std::begin(books),std::end(books),cmp);
   
    fmt::print( "books(after sort) : " );
    print_collection(books);
   
    return 0;
}