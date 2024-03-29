#include <fmt/format.h>
#include "boxcontainer.h"


int main(){

	BoxContainer box1(15);
	box1.dummy_initialize();
	
	fmt::println( "box1 : {}" , make_streamable(box1) );
	fmt::println( "&box1 : {}" , fmt::ptr(&box1) );
	
	BoxContainer box2(box1);
	fmt::println( "box2 : {}" , make_streamable(box2) );
	fmt::println( "&box2 : {}" , fmt::ptr(&box2) );
   
    return 0;
}