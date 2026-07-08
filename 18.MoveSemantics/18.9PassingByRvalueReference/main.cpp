#include <iostream>
#include "boxcontainer.h"


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

	BoxContainer items;
	items.add(get_value());

  
  
    return 0;
}