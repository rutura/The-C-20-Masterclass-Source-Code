#include <fmt/format.h>
#include <deque>

class Item{
public : 
    Item() :m_var(0){
        fmt::println( "Item default constructor called" );
    }
    Item(int var) : m_var(var){
       // fmt::println( "Item constructor called for: {}", m_var );
    }
    
    Item(const Item& source) : m_var{source.m_var}{
        // fmt::println( "Item copy constructor called for : {}" , m_var );
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
    constexpr auto parse(format_parse_context& ctx){return ctx.begin();}
    template<typename FormatContext>
    auto format(const Item& obj, FormatContext& ctx) {
        return format_to(ctx.out(), "Item [ value: {}]", obj.get());
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



int main(){

    //Creating deques
    std::deque<int> numbers = {1,2,3,4,5,6};
    
    std::deque<Item> items {Item(22),Item(33),Item(44),Item(55)};
    
    fmt::print( "numbers : " );
    print_collection(numbers);
    
    fmt::print( "items : " );
    print_collection(items);


    //Code1 : Element access
    //Access elements : [], at(), front() and back()
    fmt::println( "Element access : " );
    fmt::println( "numbers[3] : {}" , numbers[3] ); // No bound check
    fmt::println( "numbers.at(3) : {}" , numbers.at(3) ); // Bound check
    
    fmt::println( "numbers[30] (Undefined behavior): {}" ,  numbers[30] );// No bounds check, undefined behavior, junk value or even crash.
    //fmt::println( "numbers.at(30) (throws expception): {}" , numbers.at(30) );
    
    fmt::println( "numbers.front() : {}" , numbers.front() );
    fmt::println( "numbers.back() :{}" , numbers.back() );
    
    //Data method : Deque has no data method

    //Iterators
    fmt::println( "-----------------------" );
    
    fmt::println( "Iterators : " );
    //begin() and end()
    auto it = numbers.begin();
    
    fmt::print( "Deque(With iterators) : [ ");
    while(it!=numbers.end()){
        fmt::print( " {}" , *it );
        ++it;
    }
    fmt::println( " ]" );


    //Reverse traversal with rbebin and rend
    
    auto it_reverse = numbers.rbegin(); // non const iterator
    
    fmt::print( "Deque(Reverse traversal with iterators) : [ ");
    while(it_reverse!=numbers.rend()){
        fmt::println( " {}" , *it_reverse );
        ++it_reverse; // Increments towards the first element of the array.
    }
    fmt::println( " ]" );
    
    fmt::println( "-----------------------" );


    //Capacity
    fmt::println( "capacity : " );
    fmt::println( "numbers size : {}" , numbers.size() );
    fmt::println( "numbers max_size : {}" , numbers.max_size() );
    fmt::println( "numbers is empty : {}" , numbers.empty() );
    
    numbers.push_back(20);
    fmt::println( "after pushing 20 to back : " );
    print_collection(numbers);
    fmt::println( "numbers size : {}" , numbers.size() );
    
    fmt::println( "-----------------------" );

    //Code4 : Modifiers

    fmt::println( "clear : " );
    print_collection(numbers);
    
    //Clear
    numbers.clear();
    
    print_collection(numbers);
    fmt::println( "numbers size : {}" , numbers.size() );
    
    numbers ={10,20,30,40,50,60};
    
    fmt::println( "after reassignment : " );
    print_collection(numbers);


    //Insert : element inserted in front of it_pos
    fmt::println( "insert : " );
    auto it_pos = numbers.begin() + 2;
    
    print_collection(numbers);
    
    numbers.insert(it_pos,300);
    print_collection(numbers);
    numbers.insert(it_pos,400); //iterator it_pos moves as we add elements. 
                                // it_pos keeps pointing to same element
                                // elements are inserted at position in front of it_pos
    print_collection(numbers);


    //Emplace 
    fmt::println( "emplace : " );
    print_collection(numbers);
    
    auto it_item_pos = numbers.begin() + 2;
    numbers.emplace(it_item_pos,45); // The parameters following the iterator
                                        // are passed to a constructor of the type stored in 
                                        // the vector.
    print_collection(numbers);


    //Erase
    fmt::println( "erase : " );
    print_collection(numbers);
    
    numbers.erase(numbers.begin() + 4);
    
    print_collection(numbers);
    
    numbers.erase(numbers.begin() + 1, numbers.begin()+4);
    
    print_collection(numbers);


    //Emplace_back
    fmt::println( "emplace_back : " );
    print_collection(numbers);
    
    numbers.emplace_back(10);
    numbers.emplace_back(11);
    numbers.emplace_back(12);
    
    print_collection(numbers);

    //Pop back
    fmt::println( "pop_back : " );
    print_collection(numbers);
    
    numbers.pop_back();
    print_collection(numbers);
    
    numbers.pop_back();
    print_collection(numbers);
    
    numbers.pop_back();
    print_collection(numbers);


    //Resize
    fmt::println( "resize : " );
    fmt::println( " resize (Before) : " );
    print_collection(numbers);
    fmt::println( " numbers size : " , numbers.size() );
    
    numbers.resize(30);
    
    print_collection(numbers);
    fmt::println( " after resize : " );
    fmt::println( " numbers size : " , numbers.size() );
    
    //Can even resize down
    numbers.resize(10);
    print_collection(numbers);


    //Swap
    fmt::println( "swap : " );
    
    std::deque<Item> other_items = {Item(100),Item(200),Item(300)};
    
    fmt::print( "items : " );
    print_collection(items);
    
    fmt::print( "other_items : " );
    print_collection(other_items);
    
    //items.swap(other_items);
    other_items.swap(items);
    
    fmt::println( "after swap : " );
    
    fmt::print( "items : " );
    print_collection(items);
    
    fmt::print( "other_items : " );
    print_collection(other_items); 
    
  
    return 0;
}