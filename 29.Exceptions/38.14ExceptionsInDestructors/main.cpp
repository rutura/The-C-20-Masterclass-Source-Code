#include <iostream>

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
			std::cout << "main() : Catching int exception" << std::endl;
		} 

        std::cout << "END." << std::endl; 
    return 0;
}