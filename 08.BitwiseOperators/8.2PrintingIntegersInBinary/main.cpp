#include <fmt/format.h>
#include <bitset>

/**
* Reference: https://fmt.dev/latest/syntax.html
* - fmt format specifiers for different bases
*/
int main(){

    unsigned short int data {15};

    fmt::println("data (dec) : {0:#d}",  data );
    fmt::println("data (oct) : {0:#o}" ,  data );
    fmt::println("data (hex) : {0:#x}",data );
    fmt::println("data (bin) : {:016b}",  std::bitset<16>(data).to_ulong());

    return 0;
}