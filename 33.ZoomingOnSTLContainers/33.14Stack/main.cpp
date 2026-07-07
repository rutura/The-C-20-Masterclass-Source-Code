#include <iostream>
#include <stack>
#include <vector>
#include <list>
#include <deque>


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

template<typename T, typename Container = std::deque<T>>
void print_stack(std::stack<T,Container> stack){

//template <typename T>
//void print_stack(std::stack<T> stack){


    //Notice that we're working on a copy here. IMPORTANT
    std::cout << "stack of elements : [";
    while(!stack.empty()){
        T item = stack.top();
        std::cout << " " << item ;
        stack.pop(); // Poping from a copy doesn't affect the original. We're good here.
    }
    std::cout << "]" << std::endl;
}

template <typename T, typename Container = std::deque<T>>
void clear_stack(std::stack<T,Container>& stack){
//template <typename T>
//void clear_stack(std::stack<T>& stack){

    std::cout << "Clearing stack of size : " << stack.size() << std::endl;
    while(!stack.empty()){
        stack.pop();
    }
}


int main(){
    //Code1 : Creating std::stacks and storing data in
    std::stack<int> numbers1;
    
    std::cout << " numbers1 : ";
    print_stack(numbers1); // empty
    
    numbers1.push(10);
    numbers1.push(20);
    numbers1.push(30);
    
    std::cout << "numbers1 : ";
    print_stack(numbers1); // 30 20 10 : FILO

    numbers1.push(40);
    numbers1.push(50);
    
    std::cout << "numbers1 : ";
    print_stack(numbers1); // 50 40 30 20 10  : FILO

    std::cout << "-----" << std::endl;

    //Accessing elements
    std::cout << "top : " << numbers1.top() << std::endl;
    //Pop off the top
    print_stack(numbers1);
    numbers1.pop();
    print_stack(numbers1);
    std::cout << "top : " << numbers1.top() << std::endl;
    
    //We can organize these calls to top and pop into a function 
    // that can nicely show the contents of a stack. That's what print_stack does

    std::cout << "-----" << std::endl;

    //Code2 : Modifying the top element through the reference returned by top()
    //top() returns a reference. We can use that to modify the underlying 
    //element in the stack
    std::cout << "numbers1 : ";
    print_stack(numbers1); 
    
    numbers1.top() = 55;
    
    std::cout << "numbers1 : ";
    print_stack(numbers1); 


    //Code3 : Clearing a stack
    std::cout << std::endl;
    std::cout << "clearing a stack : " << std::endl;
    
    std::cout << "stack initial size : " << numbers1.size() << std::endl;
    std::cout << "numbers1 (before) : ";
    print_stack(numbers1);
    
    clear_stack(numbers1);
    
    std::cout << "stack final size : " << numbers1.size() << std::endl;
    std::cout << "numbers1(after) : ";
    print_stack(numbers1);


    //Code4 : Stack of user defined types
    std::stack<Book> books;
    books.push(Book(1921,"The Art of War"));
    books.push(Book(2000,"Social Media Marketing"));
    books.push(Book(2020,"How the Pandemic Changed the World"));
    
    std::cout << "books : ";
    print_stack(books);
    std::cout << "books size : " << books.size() << std::endl;


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


    std::cout << " numbers4 : ";
    print_stack(numbers4); // OK 

    std::cout << " numbers3 : ";
    print_stack(numbers3); // Compiler error

    std::cout << " numbers2 : ";
    print_stack(numbers2); // Compiler error

    return 0;
}