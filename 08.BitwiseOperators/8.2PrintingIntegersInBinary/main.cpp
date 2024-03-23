#include <fmt/format.h>
#include <bitset>


int main(){

    unsigned short int data {15};

    fmt::println("data (dec) : {0:#d}",  data );
    fmt::println("data (oct) : {0:#o}" ,  data );
    fmt::println("data (hex) : {0:#x}",data );
    fmt::println("data (bin) : {0:#b}",  data );
    fmt::println("data (bin) : {}",  std::bitset<16>(data).to_string() );

    return 0;
}