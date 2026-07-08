#include <iostream>
#include "boxcontainer.h"

void populate_box(BoxContainer& box, int modifier){
	for(size_t i{0} ; i < 20 ; ++i){
		box.add((i+1)*modifier);
	}
}

BoxContainer make_box(int modifier){
	BoxContainer local_int_box(20);
	populate_box(local_int_box,modifier);
	return local_int_box;
}


int main(){

	BoxContainer box_array[2];

    std::cout << "--------" << std::endl;

	for(size_t i{0} ; i < 2 ; ++i){
		box_array[i] = make_box(i+1);//Move assignment operator called
	}

    std::cout << "--------" << std::endl;
   
    return 0;
}