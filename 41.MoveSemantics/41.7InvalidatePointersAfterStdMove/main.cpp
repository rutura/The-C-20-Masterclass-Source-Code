#include <iostream>
#include "boxcontainer.h"

void populate_box(BoxContainer<int>& box, int modifier){
	for(size_t i{0} ; i < 20 ; ++i){
		box.add((i+1)*modifier);
	}
}



int main(){

    BoxContainer<int> box1;
	populate_box(box1,2);

    std::cout << "box1 : " << box1 << std::endl;
    
    BoxContainer<int> box2(std::move(box1));

    std::cout << "box2 : " << box2 << std::endl;
    std::cout << "box1 : " << box1 << std::endl;


	std::cout << "------" << std::endl;

	box1.add(34);
	box1.add(4);
	std::cout << "box1 : " << box1 << std::endl;


    return 0;
}