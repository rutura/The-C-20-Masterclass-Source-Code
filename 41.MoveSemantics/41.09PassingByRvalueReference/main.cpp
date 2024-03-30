#include "boxcontainer.h"


class Item{
    friend std::ostream& operator<<( std::ostream& out, const Item& operand);
    friend struct fmt::formatter<Item>;
public : 
    Item() : m_data{new int} {
    }
    Item(int value) : m_data{new int(value)}{
    }
    //Copy Members
    Item( const Item& source) : m_data{new int}{
        fmt::println( "Item copy constructor copying data..." );
        *m_data =(*source.m_data);
    }
    Item& operator=(const Item& right_operand){
        fmt::println( "Item copy assignment operator copying data..." );
        if (&right_operand != this){
            
            *m_data =(*right_operand.m_data);
        }
        return *this;
    }
    
    //Move Members
    Item( Item&& source){
        fmt::println( "Item move constructor moving data..." );
        //Steal the pointer
        m_data = source.m_data;
        
        //Reset the source pointer
        source.m_data = nullptr;
    }
    Item& operator=(Item&& right_operand){
        fmt::println( "Item move assignment operator moving data..." );
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
template<>
struct fmt::formatter<Item> {
    constexpr auto parse(format_parse_context& ctx){return ctx.begin(); }
    template<typename FormatContext>
    auto format(const Item& obj, FormatContext& ctx) {
        return format_to(ctx.out(), "Item: [{}]", (*obj.m_data));
    }
};

Item get_value(){
    return Item(22);
}


void do_something( Item&& item){
    fmt::println( "Do something move version called..." );
   //Item internal = item;
    Item internal = std::move(item);
   fmt::println( "internal : {}" , internal );
}



int main(){

	/*

	Item&& rvalue_ref {get_value()};

	//Item item1(std::move(rvalue_ref)); // Move constructor

	fmt::println( "-------" );

	do_something(std::move(rvalue_ref));
	*/

	BoxContainer<Item> items;
	items.add(get_value());

  
  
    return 0;
}