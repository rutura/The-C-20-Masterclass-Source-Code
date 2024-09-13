/*
    This file contains code that demonstrates passing by rvalue reference.
*/
module;

#include <iostream>

export module move_semantics_08;

namespace move_semantics_08{


    export class Item{
        friend std::ostream& operator<<( std::ostream& out, const Item& operand);
    public : 
        Item() : m_data{new int} {
        }
        Item(int value) : m_data{new int(value)}{
        }
        //Copy Members
        Item( const Item& source) : m_data{new int}{
            std::cout << "Item copy constructor copying data..." << "\n";
            *m_data =(*source.m_data);
        }
        Item& operator=(const Item& right_operand){
            std::cout << "Item copy assignment operator copying data..." << "\n";
            if (&right_operand != this){
                
                *m_data =(*right_operand.m_data);
            }
            return *this;
        }
        
        //Move Members
        Item( Item&& source){
            std::cout << "Item move constructor moving data..." << "\n";
            //Steal the pointer
            m_data = source.m_data;
            
            //Reset the source pointer
            source.m_data = nullptr;
        }
        Item& operator=(Item&& right_operand){
            std::cout << "Item move assignment operator moving data..." << "\n";
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

    export std::ostream& operator<<( std::ostream& out, const Item& operand){
        out << "Item : [" << (*operand.m_data) << "]";
        return out;
    }


    export Item get_value(){
        return Item(22);
    }


    export void do_something( Item&& item){
        std::cout << "Do something move version called..." << "\n";
    //Item internal = item;
        Item internal = std::move(item);
    std::cout << "internal : " << internal << "\n";
    }

}   // namespace move_semantics_08