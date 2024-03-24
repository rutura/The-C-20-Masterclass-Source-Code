#include <fmt/format.h>

int main(){

    /*
    //int * data = new int[10000000000000000]; // 

    for(size_t i{0} ; i < 10000000 ; ++i){
        int * data = new int[100000000];
    }
    */

   //exception
   /*
    for(size_t i{0} ; i < 100 ; ++i){
        try{
            int * data = new int[1000000000];
        }catch(std::exception& ex){
            fmt::println( "  Something went wrong : {}", ex.what() );
        }
    }
    */


   //std::nothrow
    for(size_t i{0} ; i < 100 ; ++i){
   
        int * data = new(std::nothrow) int[1000000000];

        if(data!=nullptr){
            fmt::println( "Data allocated" );
        }else{
            fmt::println( "Data allocation failed" );
        }
       
    }


    fmt::println( "Program ending well" );
    
    return 0;
}