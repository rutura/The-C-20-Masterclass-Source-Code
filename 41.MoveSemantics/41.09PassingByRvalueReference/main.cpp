#include <iostream>
#include "boxcontainer.h"


class Item{
    friend std::ostream& operator<<( std::ostream& out, const Item& operand);
public : 
    Item() : m_data{new int} {
    }
    Item(int value) : m_data{new int(value)}{
    }
    //Copy Members
    Item( const Item& source) : m_data{new int}{
        std::cout << "Item copy constructor copying data..." << std::endl;
        *m_data =(*source.m_data);
    }
    Item& operator=(const Item& right_operand){
        std::cout << "Item copy assignment operator copying data..." << std::endl;
        if (&right_operand != this){
            
            *m_data =(*right_operand.m_data);
        }
        return *this;
    }
    
    //Move Members
    Item( Item&& source){
        std::cout << "Item move constructor moving data..." << std::endl;
        //Steal the pointer
        m_data = source.m_data;
        
        //Reset the source pointer
        source.m_data = nullptr;
    }
    Item& operator=(Item&& right_operand){
        std::cout << "Item move assignment operator moving data..." << std::endl;
        if (&right_operand != this){
            
            //Steal the pointer
            m_data =right_operand.m_data;
            
            //Reset the source pointer
            right_operand.m_data = nullptr;
        }
        return *this;
    }
private : 
    int * m_data{nullptr};
};

std::ostream& operator<<( std::ostream& out, const Item& operand){
    out << "Item : [" << (*operand.m_data) << "]";
    return out;
}


Item get_value(){
    return Item(22);
}


void do_something( Item&& item){
    std::cout << "Do something move version called..." << std::endl;
   //Item internal = item;
    Item internal = std::move(item);
   std::cout << "internal : " << internal << std::endl;
}



int main(){

	/*

	Item&& rvalue_ref {get_value()};

	//Item item1(std::move(rvalue_ref)); // Move constructor

	std::cout << "-------" << std::endl;

	do_something(std::move(rvalue_ref));
	*/

	BoxContainer<Item> items;
	items.add(get_value());

  
  
    return 0;
}