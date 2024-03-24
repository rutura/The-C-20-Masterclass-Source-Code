#include <fmt/format.h>



int main(){

	
	bool go {true};

	if(int speed {10};go){
        fmt::println( "speed : {}" , speed );
		
		if(speed > 5){
			fmt::println( "Slow down!" );
		}else{
			fmt::println( "All good!" );
		}
	}else{
        fmt::println( "speed : {}" , speed );
		fmt::println( "Stop" );
	}

    //fmt::println( "Out of the if block , speed : {}" , speed );
   
    return 0;
}