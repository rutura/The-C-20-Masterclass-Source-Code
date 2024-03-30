#include <memory>
#include "boxcontainer.h"

void populate_box(BoxContainer<int>& box, int modifier){
	for(size_t i{0} ; i < 20 ; ++i){
		box.add((i+1)*modifier);
	}
}



int main(){

    BoxContainer<int> box1;
	populate_box(box1,2);

    fmt::println( "box1 : {}" , box1 );

    BoxContainer<int> box2;
	
	box2 = std::move(box1);

	fmt::println( "------" );

	fmt::println( "box1 : {}" , box1 );
	fmt::println( "box2 : {}" , box2 );


	fmt::println( "------" );

    std::unique_ptr<int> ptr_int = std::make_unique<int>(33);

	fmt::println( "*ptr_int : {}" , *ptr_int );

	std::unique_ptr<int> ptr_int_copy = ptr_int;


	if(ptr_int){
		fmt::println( "*ptr_int : {}" , *ptr_int );
	}else{
		fmt::println( "ptr_int doesn't contain any valid data" );
	}
	fmt::println( "*ptr_int_copy : {}" , *ptr_int_copy );


  
    return 0;
}