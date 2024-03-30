#include <fmt/format.h>
#include <functional>
#include <map>


class IntComparator {
public : 
    bool operator()( int left, int right) const { 
        return (left < right); 
    }
};

bool compare_ints(int left, int right){
    return (left < right);
}


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

template <typename T>
void print_collection(const T& collection){

    auto it = collection.begin();

    fmt::print( " Collection [");
    while(it != collection.end()){
        fmt::print(" {}" , *it );
        ++it;
    }
    fmt::println("]" );
}

template <typename T,typename K>
 void print_map(const std::map<T,K> & map){
    
    auto it = map.begin();
    
    fmt::print( " map of elements : [" );
    while(it != map.end()){
        
        fmt::print( " [{}, {}]", it->first ,  it->second);
        ++it;
    }
    fmt::println( " ]");
}




int main(){

    //Code1 : Building maps : Notice that things are stored by key by default
    // regardless of the order you put them in the collection in .
    fmt::println("");
    fmt::println( "Creating maps : " );
    
    std::map<int,int> numbers {{1,11},{0,12},{4,13},{2,14},{3,15}};
    
    fmt::print( " numbers : ") ;
    print_map(numbers);
    
    //Map of custom types : Need to implement operator<
    std::map<int,Book> books {
                            {2,Book(1734,"Cooking Food")},
                            {0,Book(1930,"Building Computers")},
                            {1,Book(1995,"Farming for Beginners")}
                        };
    fmt::print( " books : " );
    print_map(books);
    
    fmt::println( "--------------------------------------" );
    
    //Code2 : Element access with regular loops
    //A std::map can be though of as a collection of std::pair's
    fmt::println("");
    fmt::println( "Looping around printing stuff : " );
    fmt::println("");
    fmt::println( " printing books with regular range based for loop [] syntax (C++17) :" );
    for(const auto&[key,value] : books){
        fmt::println( "  book [{}]: {}",  key,  value );
    }
    
    fmt::println("");
    fmt::println( " Traverse map with C++11 loop syntax : " );;
    for(const auto& elt : books){
        fmt::println( "  book [{}]:{}",  elt.first ,  elt.second );
    }
    
    fmt::println("");
    fmt::println( " traverse map with loop (with explicit types) : " );
    for(const std::pair<int,Book>& elt : books){
        fmt::println( "  book [{}, {}]",  elt.first,  elt.second );
    }
    
    fmt::println( "--------------------------------------" );

    //Keys can be anything
    fmt::println("");
    fmt::println( "keys can be anything : std::string in this case (stored by key) : " );
    
    std::map<std::string, std::string> address_book;
    
    address_book["Daniel Gray"] = "Kigali, KG St 334 #56";
    address_book["Steve Moris"] = "Huye, SH St 27 #78";
    address_book["John Snow"] = "Musanze, NM St 33 #89";
    address_book["Henry King"] = "Muhanga, SM St 128 #3";
    
    for(const auto&[key,value] : address_book){
        fmt::println(" {} lives at address {}",   key ,  value );
    }
    
    fmt::println( "--------------------------------------" );
    
    //Iterators
    fmt::println("");
    fmt::println( "Iterators : " );
    
    auto it_access = numbers.begin();
    
    fmt::print( " numbers (forward iterators) : [");
    while(it_access!=numbers.end()){
        fmt::print( " {}", numbers[it_access->first]);
        ++it_access;
    }
    fmt::println( "]" );
    
    
    
    fmt::println("");
    fmt::println( "modifying elements through iterators : " );
    
    //Iterate forward over numbers
    print_map(numbers);
    
    auto it_modify = numbers.begin();
    
    while(it_modify!=numbers.end()){
        numbers[it_modify->first] = 222; // Modify values in the map
        ++it_modify;
    }
    print_map(numbers);
    
    //Iterate over books in reverse
    fmt::println("");
    fmt::println( "(iterators) set of books (reverse) :"  );
    
    auto it_back_books = books.rbegin();
    while(it_back_books != books.rend()){
            //Will require you to add a default constructor to Book.
            //This is an implementation detail of std::map. If we cut out the line
            //using operator[] the requirement for the default constructor goes away.
        fmt::println( " {} - {}",  it_back_books->first,  books[it_back_books->first]  );
        ++it_back_books;        
    }
    
    
    
    //Code4 : Capacity : 
    fmt::println( "---------------------" );
    
    fmt::println("");
    fmt::println( "capacity : " );
    
    fmt::print( " numbers : ");
    print_map(numbers);
    fmt::println( " map max_size : {}" , numbers.max_size() );
    fmt::println( " map is empty : {}" , numbers.empty() );
    fmt::println( " map size : {}" , numbers.size() );
    
    fmt::println( "---------------------" );
    
    //Modifiers
    
    //Clear
    fmt::println("");
    fmt::println( "clear :" );
    
    fmt::print( " numbers : " );
    print_map(numbers);
    
    numbers.clear();
    
    fmt::print( " numbers : ");
    print_map(numbers);
    fmt::println( " numbers is empty : {}",  numbers.empty() );
    
    
    //Insert  : return an std::pair object containing result about the insert operation.
    fmt::println("");
    fmt::println( "insert : " );
    
    
    numbers = {{0,11},{1,12},{2,13},{3,14},{4,15}}; 
    print_map(numbers);
    
    //Insert key 2 : won't insert because std::set doesn't allow duplicate keys.
    //Will just do nothing and won't give an error though.
    numbers.insert({2,44});
    
    //numbers.insert({5,16});//Works
    
    fmt::print( "After insert [2,44] : ") ;
    //fmt::println( "After insert {5,16} : " ;
    print_map(numbers);
    
    //Can capture the insert result through a returned std::pair object.
    auto result = numbers.insert({6,17});
   
   fmt::println( " result.second : ", result.second );
   
   if(result.second){
       fmt::println( " Insertion successful" );
   }else{
       fmt::println( " Couldn't inser in the set. It's a duplicate!" );
   }
   print_map(numbers);
   
   
   
    //Emplace 
    fmt::println("");
    fmt::println( "emplace : " );
    
    fmt::print( " before emplace : " );
    print_map(numbers);
    
    auto result_emplace = numbers.emplace(std::make_pair(7,18));
    
    if(result_emplace.second){
        fmt::println( " Emplace  successful" );
    }else{
        fmt::println( " Emplace  FAILED" );

    }
    
    fmt::print( " after emplace : ");
    print_map(numbers);
    
    
    

    //Erase
    fmt::println("");
    fmt::println( "erase : " );
    
    print_map(numbers);
    
    auto it_erase = numbers.find(3); // Find element with key 3
    
    if(it_erase!= numbers.end()){
        fmt::println( " Found element with key {} ! : {}",  it_erase->first ,  it_erase->second  );
    }else{
        fmt::println( " Couldn't find element with key 3 !" );
    }
    
    //Erase the element with key 3
    if(it_erase!=numbers.end())
        numbers.erase(it_erase);
    
    print_map(numbers);
    
    
    
    
    //Changing comparators : There are many ways this can be done, but I am 
    //going to give you a few variations to get you started.

    fmt::println("");
    fmt::println( "Changing comparators : " );
    
    //std::map<int,int> numbers2 {{1,11},{0,12},{4,13},{2,14},{3,15}};//Default
    //std::map<int,int,std::less<int>> numbers2 {{1,11},{0,12},{4,13},{2,14},{3,15}};//Built in functor
    //std::map<int,int,std::greater<int>> numbers2 {{1,11},{0,12},{4,13},{2,14},{3,15}};
    
    //Custom functor
    //std::map<int,int,IntComparator> numbers2 {{1,11},{0,12},{4,13},{2,14},{3,15}};
    
    //Custom funtion pointer
    /*
    std::map<int,int,bool(*)(int,int)> numbers2(compare_ints);
    numbers2.insert({{1,11},{0,12},{4,13},{2,14},{3,15}});
    */
    
    //Lambda function
    std::map<int,int,std::function<bool(int,int)>> numbers2([](int left, int right){
        return left > right ;
        });
    numbers2.insert({{1,11},{0,12},{4,13},{2,14},{3,15}});

    
    fmt::print( "numbers2 : [ ");
    for(const auto& [key,value] : numbers2){
        fmt::print( " ({}, {})", key , value );
    }
    fmt::println( "]" );
 
    return 0;
}