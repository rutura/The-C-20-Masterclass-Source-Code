#include <fmt/format.h>
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
      fmt::println( "Doing something at iteration : {}" , i );
}


int main(){

   for(size_t i{0}; i < 5 ; ++i){
        
      try{
          do_something(i);
      }
      /*
      catch(CriticalError& ex){
          fmt::println( "CriticalError Exception cought : {}" , ex.what() );
      }
      catch(SmallError& ex){
          fmt::println( "SmallError Exception cought : {}" , ex.what() );
      }
      catch(Warning& ex){
          fmt::println( "Warning Exception cought : {}" , ex.what() );
      } 
      */ 
      catch(SomethingIsWrong& ex){
          fmt::println( "SomethingIsWrong Exception cought : {}" , ex.what() );
      }    
    }
   
    return 0;
}