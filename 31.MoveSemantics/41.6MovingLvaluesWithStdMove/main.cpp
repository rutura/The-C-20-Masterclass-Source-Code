#include <iostream>
#include "boxcontainer.h"

void populate_box(BoxContainer<int>& box, int modifier){
	for(size_t i{0} ; i < 20 ; ++i){
		box.add((i+1)*modifier);
	}
}

//Copy version
/*
template<class T>
void swap_data(T& a, T& b) 
{ 
  T temp { a }; // invokes copy constructor
  a = b; // invokes copy assignment
  b = temp; // invokes copy assignment
}
*/


//Move version

template<class T>
void swap_data(T& a, T& b) 
{ 
  T temp { std::move(a) }; // invokes Move constructor
  a = std::move(b); // invokes move assignment operator
  b = std::move(temp); // invokes move assignment operator
}



int main(){

	BoxContainer<int> box1;
	populate_box(box1,2);
	BoxContainer<int> box2;
	populate_box(box2,15);
	
	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;
	
	swap_data(box1,box2);

  	std::cout << "-----" << std::endl;

	std::cout << "box1 : " << box1 << std::endl;
	std::cout << "box2 : " << box2 << std::endl;

    return 0;
}