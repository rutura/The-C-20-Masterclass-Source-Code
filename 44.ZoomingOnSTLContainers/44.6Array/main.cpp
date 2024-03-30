#include <fmt/format.h>
#include <array>


class Item{
public : 
    Item() :m_var(0){
        fmt::println( " Item default constructor called" );
    }
    Item(int var) : m_var(var){
       // fmt::println( "Item constructor called for: {}" , m_var );
    }
    Item(int var1, int var2) : m_var( var1 * var2)
    {
        
    }
    
    Item(const Item& source) : m_var{source.m_var}{
        //fmt::println( "Item copy constructor called for : {}", m_var );
    }
    
    int get() const{
        return m_var;
    }
private : 
    int m_var{0};
};

std::ostream& operator << (std::ostream& out, const Item & item){
    out << "Item [ value : " << item.get() << "]";
    return out;
}
template<>
struct fmt::formatter<Item> {
    constexpr auto parse(format_parse_context& ctx){return ctx.begin(); }
    template<typename FormatContext>
    auto format(const Item& obj, FormatContext& ctx) {
        return format_to(ctx.out(), "Item [value: {}]", obj.get());
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


template <typename T>
void print_raw_array(const T* p, std::size_t size)
{
    fmt::print(" data = ");
    for (std::size_t i = 0; i < size; ++i)
        fmt::print("{} ", p[i]);
    fmt::println("");
}



int main(){

   //Code1 : Collection creation and element access
  fmt::println("");
    fmt::println( "Collection creation and element access : " );

    std::array<int,10> numbers{1,2,3,4,5,6,7,8,9,10};
    //If you put in less than 10, the rest is auto filled with 0 (default constructed value)
    //If you put in more than 10, you get a compiler error. Can't go over that
    
    fmt::print( " numbers : " );
    print_collection(numbers);
    
    fmt::println( " Element at index 3 : {}" , numbers.at(3) ); // Bound checks
    fmt::println( " Element at index 3 : {}" , numbers[3] ); // No bound checks
    
    //Bound check : at() throws an out of range exception when you try to access
    // beyond the legal bounds of the array
    try{
    fmt::println( " Element at index 20 (at()) :{} ", numbers.at(20) );// Throws out of range expception
    }
    catch(std::exception& ex){
        fmt::println( " Access failed. Reason : {}" , ex.what() );
    }
    
    //Bound check : [] does no bound check. If you access beyond the legal bounds
    // you get undefined behavior
    fmt::println( "Element at index 20 ([]) :{} ", numbers[20] );// Undefined behavior : Junk, Crash, anything can happen here
     
    //Get the front element
    fmt::println( " numbers front : {}" , numbers.front() );
    //Get the back element 
    fmt::println( " numbers back : {}" , numbers.back() );
    
    //Front and back return references, we can even use them to modify data. Right ? 
    numbers.front() = 22;
    numbers.back()  = 33;
    
    fmt::println( " numbers front : {}"  , numbers.front() );
    fmt::println( " numbers back : {}" , numbers.back() );
    
    //The data method
    int raw_array[] {4,5,6,7,8,9};
    fmt::println( " Showing raw array data : " );
    print_raw_array(raw_array,6);
    
    fmt::println( " Showing numbers.data as a raw array : " );
    print_raw_array(numbers.data(),numbers.size());
    
    
    fmt::println( "-----------------------" );
    
    
    //Code2 : Iterators
  fmt::println("");
    fmt::println( "Iterators : " );

    auto it = numbers.begin();
    
    fmt::print( " std::array(with iterators) : [ ");
    while(it!=numbers.end()){
        fmt::print( "{} " , *it );
        ++it;
    }
    fmt::println( " ]" );
    
    //Reverse traversal with rbegin and rend
    auto it_reverse = numbers.rbegin(); // non const iterator
    
    fmt::print( " std::array(Reverse traversal with iterators) : [ ");
    while(it_reverse!=numbers.rend()){
        fmt::print( "{} " , *it_reverse);
        ++it_reverse; // Increments towards the first element of the array.
    }
    fmt::println( " ]" );
    
    fmt::println( "-----------------------" );
    
    
    //Code3 : Capacity
  fmt::println("");
    fmt::println( "capacity : " );
    fmt::println( " numbers size : {}" , numbers.size() );
    fmt::println( " numbers max_size : {}" , numbers.max_size() );
    fmt::println( " numbers is empty : {}" , numbers.empty() );
    //fmt::println( "numbers capacity : {}" , numbers.capacity() );//No capacity method
    
    fmt::println( "-----------------------" );
    
    
    //Code4 : Operations
    //Filling
    fmt::println( "filling : " );
    fmt::println( " numbers : ") ;
    print_collection(numbers);
    numbers.fill(1000);
    fmt::println( " numbers : " );
    print_collection(numbers);
    
    
    
   
    //Swapping : arrays must be of same size and contain the same type. 
    //otherwise they'll be different types and you can't cross assign different types.
  fmt::println("");
    fmt::println( "Swapping : " );
    std::array<int,10> other_numbers {5,5,5,5,5,5,5,5,5,5};
    
    fmt::print( " numbers : " );
    print_collection(numbers);
    
    fmt::print( " other_numbers : " );
    print_collection(other_numbers);
    
    //swap
    numbers.swap(other_numbers);
    
    fmt::print( " numbers : " );
    print_collection(numbers);
    
    fmt::print( " other_numbers : " );
    print_collection(other_numbers);
    
    
    
    //Code5 : Can assign arrays to each other
  fmt::println("");
    fmt::println( "Assigning arrays to each other :" );
    
    fmt::print( " numbers : " );
    print_collection(numbers);
    fmt::print( " other_numbers : " );
    print_collection(other_numbers);
    
    numbers = other_numbers; // Calls the copy assignment operator of std::array
    
    fmt::print( " numbers : " );
    print_collection(numbers);
    fmt::print( " other_numbers : " );
    print_collection(other_numbers);
    
    //This isn't possible with raw arrays.
    /*
    int int_arr1[] {1,2,3};
    int int_arr2[] {4,5,6};
    int_arr2 = int_arr1; // Compiler error : invalid array assignment
    */
    
    
    //Code6 : std::arrays for custom objects
  fmt::println("");
    fmt::println( "Storing custom objects in std::array : " );
    
    std::array<Item,5> items = {};
    fmt::println( " default initialized items : " );
    
    fmt::print( " items : " );
    print_collection(items);
    
    items.fill(Item(5));
    
    fmt::print( " items : " );
    print_collection(items);
    
  
  
    return 0;
}