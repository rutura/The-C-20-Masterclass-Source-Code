#include <iostream>


class Item{
public : 

    Item(int a, int b)
        : m_var1{a}, m_var2{b}
    {}
    void some_member_func(){
		
        auto func = [this](){
            std::cout << "member vars :" << m_var1 << "," << m_var2 << std::endl;
        };
        func();
    };
private : 
    int m_var1;
    int m_var2;
};


int main(){

    Item item1(10,20);
    item1.some_member_func();
    
    return 0;
}