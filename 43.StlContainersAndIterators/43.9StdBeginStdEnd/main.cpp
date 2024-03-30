#include <fmt/format.h>
#include <vector>


int main(){

    //std::vector<int> vi {1,2,3,4,5,6,7,8,9};
    int vi[] {1,2,3,4,5,6,7,8,9};
    

    /*
    fmt::print( " Collection : " );
    for(auto it = vi.begin(); it!= vi.end(); ++it){
        fmt::print( "{} ", *it );
    }

    */

   fmt::println("--------" );

    fmt::print(" Collection : " );
    for(auto it = std::begin(vi); it!= std::end(vi); ++it){
        fmt::print(  "{} ", *it );
    }
  
   
    return 0;
}