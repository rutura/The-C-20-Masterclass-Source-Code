#include <fmt/format.h>
#include "boxcontainer.h"


int main(){

	BoxContainer box1(5);
	fmt::println( "box1 : {}" , make_streamable(box1) );

	box1.add(11);
	box1.add(12);
	box1.add(13);
	fmt::println( "box1 : {}" , make_streamable(box1) );
	
	box1.add(14);
	box1.add(15);
	fmt::println( "box1 : {}" , make_streamable(box1) );
	
	box1.add(16);
	fmt::println( "box1 : {}" , make_streamable(box1) );
	
	for(size_t i{0}; i < 4 ; ++i){
		box1.add(17+i);
	}
	fmt::println( "box1 : {}" , make_streamable(box1) );
	
	box1.add(21);
	fmt::println( "box1 : {}"  , make_streamable(box1) );

   
    return 0;
}