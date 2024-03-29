#include <fmt/format.h>

class Item{
public : 
    Item(){}
    ~Item()  {
        try{
            throw 0;
        }catch(int ex){
            throw;
        }
    }
    
};


int main(){
 		try{
			Item item;	
		}catch(int ex){
			fmt::println( "main() : Catching int exception" );
		} 

        fmt::println( "END." );
    return 0;
}