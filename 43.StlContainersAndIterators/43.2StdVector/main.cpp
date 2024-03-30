#include <fmt/format.h>
#include <vector>

template <typename T>
void print_vec( const std::vector<T>& vec){
    for(size_t i{}; i < vec.size();++i){
        fmt::print( "{} ", vec[i]);;
    }
    fmt::println("");
}

template <typename T>
void print_raw_array(const T* p, std::size_t size)
{
    fmt::print( "data = ");
    for (std::size_t i = 0; i < size; ++i)
        fmt::print( "{} ", p[i]);
    fmt::println("");
}


int main(){

    //Constructing vectors
    std::vector<std::string> vec_str {"The","sky","is","blue","my","friend"};
    fmt::println( "vec1[1]  : {}" , vec_str[1] );
    print_vec(vec_str);

    fmt::println( "------" );

    std::vector<int> ints1;
    fmt::print( "ints1 : ");
    print_vec(ints1); // Won't print anything, the vector has no content

    std::vector<int> ints2 = { 1,2,3,4 };
    std::vector<int> ints3{ 11,22,33,44 };
    
    fmt::print( "ints2 : ");
    print_vec(ints2);

    fmt::print( "ints3 : ");
    print_vec(ints3);


    std::vector<int> ints4(20, 55); // A vector with 20 items, all initialized to 55
    fmt::print( "ints4 : ");
    print_vec(ints4);
    
    //Be careful about uniform initialization
    std::vector<int> ints5{20, 55}; // A vector with 2 items : 20 and 55
    fmt::print( "ints5 : ");
    print_vec(ints5);


    //Accessing elements
    fmt::println( "Accessing elements in a vector: " );
    fmt::println( "vec_str[2] : {}" , vec_str[2] );
    fmt::println( "vec_str.at(3) : {}" , vec_str.at(3) );
    fmt::println( "vec_str.front() : {}" , vec_str.front() );
    fmt::println( "vec_str.back() : {}" , vec_str.back() );

    //Using the data method
    fmt::println( "using raw array : " );
    print_raw_array(vec_str.data(),vec_str.size());


    //Adding and removing stuff
    fmt::println( "Adding and removing stuff : " );
    
    fmt::print( "ints1 : ");
    print_vec(ints1);
    
    
    //Pushing back
    ints1.push_back(100);
    ints1.push_back(200);
    ints1.push_back(300);
    ints1.push_back(500);
    fmt::print( "ints1 : ") ;
    print_vec(ints1);
    
    //Poping back
    ints1.pop_back();
    fmt::print( "ints1 : " );
    print_vec(ints1);

   
    return 0;
}