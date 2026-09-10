#include <iostream>
#include "exceptions.h"


void do_something(size_t i){
      if(i == 2){
          throw CriticalError("i is 2");
      }
      
      if(i == 3){
          throw SmallError("i is 3");
      }
	  
      if(i == 4){
          throw Warning("i is 4");
      }
      std::cout << "Doing something at iteration : " << i << std::endl;
}


int main(){

   for(size_t i{0}; i < 5 ; ++i){
        
      try{
          do_something(i);
      }
      catch(CriticalError& ex){
          std::cout << "CriticalError Exception cought : " << ex.what() << std::endl;
      }
      catch(SmallError& ex){
          std::cout << "SmallError Exception cought : " << ex.what() << std::endl;
      }
      catch(Warning& ex){
          std::cout << "Warning Exception cought : " << ex.what() << std::endl;
      }  
      catch(SomethingIsWrong& ex){
          std::cout << "SomethingIsWrong Exception cought : " << ex.what() << std::endl;
      }    
    }
   
    return 0;
}