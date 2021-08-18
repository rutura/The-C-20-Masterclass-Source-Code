#include <iostream>
#include "exceptions.h"

void some_function(size_t i){
    if(i == 0)
        throw 1;
    if(i ==2)
        throw "const char*-Hello there";
    if(i==3)
        throw CriticalError("Something is wrong");
    if(i==4)
        throw std::string("std::string-Hello there");     
}


int main(){

   try{
        for( size_t i{}; i < 5; ++i){
            try{
                some_function(i);
            }
            catch(int ex){
                std::cout << "int handler- Cought an integer" << std::endl;
            }
            catch(...){
                std::cout << "Inner... handler , Cought some exception" << std::endl;
                throw;
            }
        }        
    }
    catch(const std::string& ex){
        std::cout << "Cought some string exception" << std::endl;
    }
    catch(...){
        std::cout << "Outer ...handler cought some other exception" << std::endl;
    }

  
   
    return 0;
}