#include <fmt/format.h>


int sum ( int a , int b){
    int result = a + b;
    fmt::println( "In : &result(int) :  {}" , fmt::ptr(&result) );
 	return result;
}

std::string add_strings(std::string str1, std::string str2){
    std::string result =  str1 + str2;
    fmt::println( "In : &result(std::string) :  {}" , fmt::ptr(&result) );
    return result;
}

int main(){

    
    /*
    int x{15};
    int y{9};
    int result = sum(x,y);
    fmt::println( "Out : &result(int) :  {}" , &result );
    fmt::println( "result : {}" , result );
    */
 

   
    std::string in_str1{"Hello"};
    std::string in_str2{" World!"};
    std::string result_str = add_strings(in_str1,in_str2);
    fmt::println( "Out : &result_str(std::string) :  {}" , fmt::ptr(&result_str) );
    fmt::println( "result_str : {}" , result_str );
  

    return 0;
}