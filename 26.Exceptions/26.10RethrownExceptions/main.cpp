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
            try{
                do_something(i);
            }     
            catch(SomethingIsWrong& ex_inner){
                if(typeid(ex_inner) == typeid(Warning)){
                    std::cout << typeid(ex_inner).name()  <<
                        " -Inner catch block ,Exception cought : " <<
                        ex_inner.what() << std::endl;
                }else{
                    throw; //
                   // throw ex_inner;//This will do a copy, and there will be slicing.Beware.
                }
            }
        }
        catch(SomethingIsWrong& ex_outer){
            std::cout << typeid(ex_outer).name() << 
                    " -Outer catch block, Exception cought : " << 
                        ex_outer.what() << std::endl;
        }
    }//End of for loop

  
   
    return 0;
}