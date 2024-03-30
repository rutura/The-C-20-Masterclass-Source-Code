#include <fmt/format.h>
#include <algorithm>
#include <vector>


template<typename T>
void print_collection( const T& collection){
    fmt::print( " Collection [" );
    for(const auto& elt : collection){
        fmt::print( " {}" ,  elt );
    }
    fmt::println("]");
}



int main(){

    //std::vector<int> source {1,2,3,4,5,6,7,8,9};
    int source[] {1,2,3,4,5,6,7,8,9};   

    std::vector<int> dest {15,21,12,53,30,40};
    
    fmt::print( "source : ");
    print_collection(source);
    
    fmt::print( "dest : ");
    print_collection(dest);
    
    //Copy from source to dest
    //Copy elements from source in the range [std::begin(source),std::begin(source) + 4 ) 
    //to dest, starging from iterator std::begin(dest)
    //Make sure you are copying from valid ranges either in dest or source.
    std::copy(std::begin(source),std::begin(source) + 4,std::begin(dest));
    
    fmt::print( "source(after copy) : ");
    print_collection(source);
    
    fmt::print( "dest(after copy) : ");
    print_collection(dest);

    fmt::print( "---------------------------" );
 
    std::vector<int> dest1{100,200,300,400,500,600};
    
    fmt::print( "source : ");
    print_collection(source);
    
    fmt::print( "dest1 : " );
    print_collection(dest1);
    
    auto odd = [](int n){
        return ((n%2)!=0);
    };
    //If there are more elements in source than the space available in dest,
    //surplus elements will just be ignored.
    std::copy_if(std::begin(source),std::end(source),std::begin(dest1),odd);
    
    fmt::print( "source(after copy) : ");
    print_collection(source);
    
    fmt::print( "dest1(after copy) : " );
    print_collection(dest1);
   
    return 0;
}