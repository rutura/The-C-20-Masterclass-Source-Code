#include <iostream>
#include <queue>



class Book{
    friend std::ostream& operator<< (std::ostream& out, const Book& operand);
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



//template <typename T>
//void print_priority_queue(std::priority_queue<T> p_queue){

template<typename T,
                    typename Container = std::vector<T>,
                    typename Compare = std::less<typename Container::value_type>>  
void print_priority_queue(std::priority_queue<T,Container,Compare> p_queue){ 
    
    std::cout << "priority queue of elements : [";
    while(!p_queue.empty()){
        std::cout << " " << p_queue.top() ;
        p_queue.pop();
    }
    std::cout << "]" << std::endl;
    
}


//template <typename T>
//void clear_queue(std::priority_queue<T>& p_queue){

template<typename T,
                    typename Container = std::vector<T>,
                    typename Compare = std::less<typename Container::value_type>>  
void clear_queue(std::priority_queue<T,Container,Compare>& p_queue){ 
    
    std::cout << "Clearing priority queue of size : " << p_queue.size() << std::endl;
    while(!p_queue.empty()){
        p_queue.pop();
    }
    
}



int main(){

    //Code1 : Creating  pushing and accessing
    std::priority_queue<int> numbers1; // The greatest has higher priority
    
    std::cout << " numbers1 : ";
    print_priority_queue(numbers1);
    
    numbers1.push(10);
    numbers1.push(8);
    numbers1.push(12);
    
    std::cout << " numbers1 : ";
    print_priority_queue(numbers1);
    
    numbers1.push(11);
    numbers1.push(3);
    
    std::cout << " numbers1 : ";
    print_priority_queue(numbers1);
    
    //Acess
    std::cout << " numbers1.top() :  " << numbers1.top() << std::endl;


    //Code2 : Can't through top to modify top element : this is
    //because top() returns  a CONST reference.
    std::cout << std::endl;
    std::cout << "modify top element through top():" << std::endl;
    
    std::cout << " numbers1 (before modification) : ";
    print_priority_queue(numbers1);
    
    //numbers1.top() = 500; // Compiler error

    std::cout << " numbers1 (after modification) : ";
    print_priority_queue(numbers1);


    //Code3 : poping : Pops the highest priority element
    std::cout << std::endl;
    std::cout << "poping data : " << std::endl;
    
    std::cout << " numbers1 : ";
    print_priority_queue(numbers1);
    
    numbers1.pop();
    
    std::cout << " numbers1 : ";
    print_priority_queue(numbers1);
    
    numbers1.pop();
    
    std::cout << " numbers1 : ";
    print_priority_queue(numbers1);

    //Code4 : Clearing a priority queue
    std::cout << std::endl;
    std::cout << "clearing a priority queue : " << std::endl;
    
    std::cout << " priority queue initial size : " << numbers1.size() << std::endl;
    std::cout << " numbers1 (before) : ";
    print_priority_queue(numbers1);
    
    clear_queue(numbers1);
    
    std::cout << " priority_queue final size : " << numbers1.size() << std::endl;
    std::cout << " numbers1(after) : ";
    print_priority_queue(numbers1);


    //Code5 : priority_queue of user defined types
    std::cout << std::endl;
    std::cout << "priority queue of user defined type :" << std::endl;
    
    std::priority_queue<Book> books;
    
    //ATTETION : Notice the effects of changing operator< to do a different comparison
    //mechanism and how that affects the priorities perceived by the priority queue
    //this can  be seen in the order the elements are printed in by print_priority_queue : 
    //it starts from the top.
    
    books.push(Book(1921,"Art of War"));
    books.push(Book(2020,"Building Social Media Marketing Strategies"));
    books.push(Book(1990,"Converging Lines of Modern Economy"));
    books.push(Book(1998,"Driving Current Triggered Transistors"));
    
    std::cout << "books : ";
    print_priority_queue(books);
    std::cout << "books size : " << books.size() << std::endl;
    std::cout << "top book : " << books.top() << std::endl;


   //Code6 : specify a custom comparator and/or underlying container
    std::cout << std::endl;
    std::cout << "changing the comparator and underlying container : " << std::endl;
    
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
    
    std::cout << " numbers2 : ";
    print_priority_queue(numbers2);
    
   
    return 0;
}