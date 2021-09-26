#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>


template <typename T>
class VectorWrapper{
public: 
    //Iterator methods
    std::vector<T>::iterator begin() { return m_items.begin(); }
    std::vector<T>::iterator end()   { return m_items.end(); }

    //Const overloads
    std::vector<T>::const_iterator begin() const{ return m_items.cbegin(); }
    std::vector<T>::const_iterator end() const  { return m_items.cend(); }


    std::vector<T>::const_iterator cbegin() { return m_items.cbegin(); }
    std::vector<T>::const_iterator cend()   { return m_items.cend(); }
 
    friend std::ostream& operator<< (std::ostream& out, const VectorWrapper<T>& vec){
        out << "Items : " ;
        for (auto i : vec.m_items){
            out << i << " ";
        }
        return out;
    }  
    
    void add( T item){
        m_items.push_back(item);
    }
private : 
    std::vector<T> m_items;
};

int main(){

	VectorWrapper<std::string> greeting;
    greeting.add("Hello");
    greeting.add("World!");
    greeting.add("How");
    greeting.add("are");
    greeting.add("you");
    greeting.add("all");
    greeting.add("doing?");
    
    std::cout << "greeting : " << greeting << std::endl;

    std::cout << "Range based for loop : " << std::endl;
    for(auto i : greeting){
        std::cout << i << " ";
    }
    std::cout << std::endl;


    std::cout << "taking only 2 : " << std::endl;
    for(auto i : greeting | std::views::take(2)){
        std::cout << i << " ";
    }
    std::cout << std::endl;
   
    return 0;
}