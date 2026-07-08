#ifndef ITEM_H
#define ITEM_H

#include <iostream>

class Item{
    friend std::ostream& operator<<( std::ostream& out, const Item& operand);
    friend bool operator==(const Item& left, const Item& right);
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

#endif // ITEM_H
