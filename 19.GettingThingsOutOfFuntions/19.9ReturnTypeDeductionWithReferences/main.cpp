#include <fmt/format.h>

auto& max(int& a, int& b){
    if(a>b){
        return a;
    }else{
        return b; // Will return a copy.
    }
}

int main(){


    int x{10};
    int y{45};

	int& result = max(x,y); // Error : Can not treat return value as a reference
							// It's jut a bare separate variable with a value inside.
							
	//int result = max(x,y); // A copy of the max is returned
	
	++ result;
	
	fmt::println( "x :{}" , x ); // 10
	fmt::println( "y :{}" , y ); // 46
	fmt::println( "result : {}" , result ); // 46
   
    return 0;
}