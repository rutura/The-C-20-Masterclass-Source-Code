#include <iostream>
#include "boxcontainer.h"

void populate_box(BoxContainer& box, int modifier){
	for(size_t i{0} ; i < 20 ; ++i){
		box.add((i+1)*modifier);
	}
}

//Copy version
/*
void swap_data(BoxContainer& a, BoxContainer& b)
{
  BoxContainer temp { a }; // invokes copy constructor
  a = b; // invokes copy assignment
  b = temp; // invokes copy assignment
}
*/


//Move version

void swap_data(BoxContainer& a, BoxContainer& b)
{
  BoxContainer temp { std::move(a) }; // invokes Move constructor
  a = std::move(b); // invokes move assignment operator
  b = std::move(temp); // invokes move assignment operator
}



int main(){

	BoxContainer box1;
	populate_box(box1,2);
	BoxContainer box2;
	populate_box(box2,15);
	
	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;
	
	swap_data(box1,box2);

  	std::cout << "-----" << std::endl;

	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;

    return 0;
}