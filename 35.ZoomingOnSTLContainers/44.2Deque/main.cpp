#include <iostream>
#include <deque>

class Item{
public : 
    Item() :m_var(0){
        std::cout << "Item default constructor called" << std::endl;
    }
    Item(int var) : m_var(var){
       // std::cout << "Item constructor called for: " << m_var << std::endl;
    }
    
    Item(const Item& source) : m_var{source.m_var}{
        //std::cout << "Item copy constructor called for :" << m_var << std::endl;
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

template <typename T>
void print_collection(const T& collection){
    
    auto it = collection.begin();
    
    std::cout << " Collection [";
    while(it != collection.end()){
        std::cout << " " << *it ;
        ++it;
    }
    std::cout << "]" << std::endl;
}



int main(){

    //Creating deques
    std::deque<int> numbers = {1,2,3,4,5,6};
    
    std::deque<Item> items {Item(22),Item(33),Item(44),Item(55)};
    
    std::cout << "numbers : " ;
    print_collection(numbers);
    
    std::cout << "items : " ;
    print_collection(items);


    //Code1 : Element access
    //Access elements : [], at(), front() and back()
    std::cout << std::endl;
    std::cout << "Element access : " << std::endl;
    std::cout << "numbers[3] : " << numbers[3] << std::endl; // No bound check
    std::cout << "numbers.at(3) : " << numbers.at(3) << std::endl; // Bound check
    
    std::cout << "numbers[30] (Undefined behavior):" <<  numbers[30] << std::endl;// No bounds check, undefined behavior, junk value or even crash.
    //std::cout << "numbers.at(30) (throws expception): " << numbers.at(30) << std::endl;
    
    std::cout << "numbers.front() : " << numbers.front() << std::endl;
    std::cout << "numbers.back() :" << numbers.back() << std::endl;
    
    //Data method : Deque has no data method

    //Iterators
    std::cout << "-----------------------" << std::endl;
    
    std::cout << std::endl;
    std::cout << "Iterators : " << std::endl;
    //begin() and end()
    auto it = numbers.begin();
    
    std::cout << "Deque(With iterators) : [ ";
    while(it!=numbers.end()){
        std::cout << " " << *it ;
        ++it;
    }
    std::cout << " ]" << std::endl;


    //Reverse traversal with rbebin and rend
    
    auto it_reverse = numbers.rbegin(); // non const iterator
    
    std::cout << "Deque(Reverse traversal with iterators) : [ ";
    while(it_reverse!=numbers.rend()){
        std::cout << " " << *it_reverse ;
        ++it_reverse; // Increments towards the first element of the array.
    }
    std::cout << " ]" << std::endl;    
    
    std::cout << "-----------------------" << std::endl;


    //Capacity
    std::cout << std::endl;
    std::cout << "capacity : " << std::endl;
    std::cout << "numbers size : " << numbers.size() << std::endl;
    std::cout << "numbers max_size : " << numbers.max_size() << std::endl;
    std::cout << std::boolalpha; // Force output of bool as true or false instead of 1 or 0
    std::cout << "numbers is empty : " << numbers.empty() << std::endl;
    
    numbers.push_back(20);
    std::cout << "after pushing 20 to back : " << std::endl;
    print_collection(numbers);
    std::cout << "numbers size : " << numbers.size() << std::endl;
    
    std::cout << "-----------------------" << std::endl;

    //Code4 : Modifiers
    std::cout << std::endl;
    
    std::cout << "clear : " << std::endl;
    print_collection(numbers);
    
    //Clear
    numbers.clear();
    
    print_collection(numbers);
    std::cout << "numbers size : " << numbers.size() << std::endl;
    
    numbers ={10,20,30,40,50,60};
    
    std::cout << "after reassignment : " << std::endl;
    print_collection(numbers);


    //Insert : element inserted in front of it_pos
    std::cout << std::endl;
    std::cout << "insert : " << std::endl;
    auto it_pos = numbers.begin() + 2;
    
    print_collection(numbers);
    
    numbers.insert(it_pos,300);
    print_collection(numbers);
    numbers.insert(it_pos,400); //iterator it_pos moves as we add elements. 
                                // it_pos keeps pointing to same element
                                // elements are inserted at position in front of it_pos
    print_collection(numbers);


    //Emplace 
    std::cout << std::endl;
    std::cout << "emplace : " << std::endl;
    print_collection(numbers);
    
    auto it_item_pos = numbers.begin() + 2;
    numbers.emplace(it_item_pos,45); // The parameters following the iterator
                                        // are passed to a constructor of the type stored in 
                                        // the vector.
    print_collection(numbers);


    //Erase
    std::cout << std::endl;
    std::cout << "erase : " << std::endl;
    print_collection(numbers);
    
    numbers.erase(numbers.begin() + 4);
    
    print_collection(numbers);
    
    numbers.erase(numbers.begin() + 1, numbers.begin()+4);
    
    print_collection(numbers);


    //Emplace_back
    std::cout << std::endl;
    std::cout << "emplace_back : " << std::endl;
    print_collection(numbers);
    
    numbers.emplace_back(10);
    numbers.emplace_back(11);
    numbers.emplace_back(12);
    
    print_collection(numbers);

    //Pop back
    std::cout << std::endl;
    std::cout << "pop_back : " << std::endl;
    print_collection(numbers);
    
    numbers.pop_back();
    print_collection(numbers);
    
    numbers.pop_back();
    print_collection(numbers);
    
    numbers.pop_back();
    print_collection(numbers);


    //Resize
    std::cout << std::endl;
    std::cout << "resize : " << std::endl;
    std::cout << " resize (Before) : " << std::endl;
    print_collection(numbers);
    std::cout << " numbers size : " << numbers.size() << std::endl;
    
    numbers.resize(30);
    
    print_collection(numbers);
    std::cout << " after resize : " << std::endl;
    std::cout << " numbers size : " << numbers.size() << std::endl;
    
    //Can even resize down
    numbers.resize(10);
    print_collection(numbers);


    //Swap
    std::cout << std::endl;
    std::cout << "swap : " << std::endl;
    
    std::deque<Item> other_items = {Item(100),Item(200),Item(300)};
    
    std::cout << "items : " ;
    print_collection(items);
    
    std::cout << "other_items : " ;
    print_collection(other_items);
    
    //items.swap(other_items);
    other_items.swap(items);
    
    std::cout << "after swap : " << std::endl;
    
    std::cout << "items : " ;
    print_collection(items);
    
    std::cout << "other_items : " ;
    print_collection(other_items); 
    
  
    return 0;
}