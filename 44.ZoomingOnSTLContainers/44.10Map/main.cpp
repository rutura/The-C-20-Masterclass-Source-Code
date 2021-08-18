#include <iostream>
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


template <typename T,typename K>
 void print_map(const std::map<T,K> & map){
    
    auto it = map.begin();
    
    std::cout << " map of elements : [" ;
    while(it != map.end()){
        
        std::cout << " [" << it->first << "," << it->second << "]" ;
        ++it;
    }
    std::cout << " ]" << std::endl;
}




int main(){

    //Code1 : Building maps : Notice that things are stored by key by default
    // regardless of the order you put them in the collection in .
    std::cout << std::endl;
    std::cout << "Creating maps : " << std::endl;
    
    std::map<int,int> numbers {{1,11},{0,12},{4,13},{2,14},{3,15}};
    
    std::cout << " numbers : " ;
    print_map(numbers);
    
    //Map of custom types : Need to implement operator<
    std::map<int,Book> books {
                            {2,Book(1734,"Cooking Food")},
                            {0,Book(1930,"Building Computers")},
                            {1,Book(1995,"Farming for Beginners")}
                        };
    std::cout << " books : " ;
    print_map(books);
    
    std::cout << "--------------------------------------" << std::endl;
    
    //Code2 : Element access with regular loops
    //A std::map can be though of as a collection of std::pair's
    std::cout << std::endl;
    std::cout << "Looping around printing stuff : " << std::endl;
    std::cout << std::endl;
    std::cout << " printing books with regular range based for loop [] syntax (C++17) :" << std::endl;
    for(const auto&[key,value] : books){
        std::cout << "  book [ " << key << " ]:" << value << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << " Traverse map with C++11 loop syntax : " << std::endl;;
    for(const auto& elt : books){
        std::cout << "  book [" << elt.first << " ] : " << elt.second << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << " traverse map with loop (with explicit types) : " << std::endl;
    for(const std::pair<int,Book>& elt : books){
        std::cout << "  book [" << elt.first << " ] : " << elt.second << std::endl;
    }
    
    std::cout << "--------------------------------------" << std::endl;

    //Keys can be anything
    std::cout << std::endl;
    std::cout << "keys can be anything : std::string in this case (stored by key) : " << std::endl;
    
    std::map<std::string, std::string> address_book;
    
    address_book["Daniel Gray"] = "Kigali, KG St 334 #56";
    address_book["Steve Moris"] = "Huye, SH St 27 #78";
    address_book["John Snow"] = "Musanze, NM St 33 #89";
    address_book["Henry King"] = "Muhanga, SM St 128 #3";
    
    for(const auto&[key,value] : address_book){
        std::cout <<" " <<  key << " lives at address : " << value << std::endl;
    }
    
    std::cout << "--------------------------------------" << std::endl;
    
    //Iterators
    std::cout << std::endl;
    std::cout << "Iterators : " << std::endl;
    
    auto it_access = numbers.begin();
    
    std::cout << " numbers (forward iterators) : [";
    while(it_access!=numbers.end()){
        std::cout << " " << numbers[it_access->first];
        ++it_access;
    }
    std::cout << "]" << std::endl;
    
    
    
    std::cout << std::endl;
    std::cout << "modifying elements through iterators : " << std::endl;
    
    //Iterate forward over numbers
    print_map(numbers);
    
    auto it_modify = numbers.begin();
    
    while(it_modify!=numbers.end()){
        numbers[it_modify->first] = 222; // Modify values in the map
        ++it_modify;
    }
    print_map(numbers);
    
    //Iterate over books in reverse
    std::cout << std::endl;
    std::cout << "(iterators) set of books (reverse) :"  << std::endl;
    
    auto it_back_books = books.rbegin();
    while(it_back_books != books.rend()){
            //Will require you to add a default constructor to Book.
            //This is an implementation detail of std::map. If we cut out the line
            //using operator[] the requirement for the default constructor goes away.
        std::cout << " " << it_back_books->first <<  " - " << books[it_back_books->first]  << std::endl;
        ++it_back_books;        
    }
    
    
    
    //Code4 : Capacity : 
    std::cout << "---------------------" << std::endl;
    
    std::cout << std::endl;
    std::cout << std::boolalpha;
    std::cout << "capacity : " << std::endl;
    
    std::cout << " numbers : ";
    print_map(numbers);
    std::cout << " map max_size : " << numbers.max_size() << std::endl;
    std::cout << " map is empty : " << numbers.empty() << std::endl;
    std::cout << " map size : " << numbers.size() << std::endl;
    
    std::cout << "---------------------" << std::endl;
    
    //Modifiers
    
    //Clear
    std::cout << std::endl;
    std::cout << "clear :" << std::endl;
    
    std::cout << " numbers : " ;
    print_map(numbers);
    
    numbers.clear();
    
    std::cout << " numbers : " ;
    print_map(numbers);
    std::cout << std::boolalpha;
    std::cout << " numbers is empty : " << numbers.empty() << std::endl;
    
    
    //Insert  : return an std::pair object containing result about the insert operation.
    std::cout << std::endl;
    std::cout << "insert : " << std::endl;
    
    
    numbers = {{0,11},{1,12},{2,13},{3,14},{4,15}}; 
    print_map(numbers);
    
    //Insert key 2 : won't insert because std::set doesn't allow duplicate keys.
    //Will just do nothing and won't give an error though.
    numbers.insert({2,44});
    
    //numbers.insert({5,16});//Works
    
    std::cout << "After insert {2,44} : " ;
    //std::cout << "After insert {5,16} : " ;
    print_map(numbers);
    
    //Can capture the insert result through a returned std::pair object.
    auto result = numbers.insert({6,17});
   
   std::cout << " result.second : " << result.second << std::endl;
   
   if(result.second){
       std::cout << " Insertion successful" << std::endl;
   }else{
       std::cout << " Couldn't inser in the set. It's a duplicate!" << std::endl;
   }
   print_map(numbers);
   
   
   
    //Emplace 
    std::cout << std::endl;
    std::cout << "emplace : " << std::endl;
    
    std::cout << " before emplace : " ;
    print_map(numbers);
    
    auto result_emplace = numbers.emplace(std::make_pair(7,18));
    
    if(result_emplace.second){
        std::cout << " Emplace  successful" << std::endl;
    }else{
        std::cout << " Emplace  FAILED" << std::endl;

    }
    
    std::cout << " after emplace : ";
    print_map(numbers);
    
    
    

    //Erase
    std::cout << std::endl;
    std::cout << "erase : " << std::endl;
    
    print_map(numbers);
    
    auto it_erase = numbers.find(3); // Find element with key 3
    
    if(it_erase!= numbers.end()){
        std::cout << " Found element with key " << it_erase->first <<
            " ! : " << it_erase->second  << std::endl;
    }else{
        std::cout << " Couldn't find element with key 3 !" << std::endl;
    }
    
    //Erase the element with key 3
    if(it_erase!=numbers.end())
        numbers.erase(it_erase);
    
    print_map(numbers);
    
    
    
    
    //Changing comparators : There are many ways this can be done, but I am 
    //going to give you a few variations to get you started.

    std::cout << std::endl;
    std::cout << "Changing comparators : " << std::endl;
    
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

    
    std::cout << "numbers2 : [ ";
    for(const auto& [key,value] : numbers2){
        std::cout << " (" << key << "," << value << ")";
    }
    std::cout << "]" << std::endl;
 
    return 0;
}