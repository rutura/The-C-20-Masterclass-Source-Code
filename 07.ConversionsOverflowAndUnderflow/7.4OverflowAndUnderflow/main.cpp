#include <fmt/format.h>

int main(){

    //Overflow 

    unsigned char data {250};

    ++data;
    fmt::println("data : {}" , static_cast<int>(data) );

    ++data;
    fmt::println("data : {}" , static_cast<int>(data) );

    ++data;
    fmt::println("data : {}" , static_cast<int>(data) );

    ++data;
    fmt::println("data : {}" , static_cast<int>(data) );

    ++data; 
    fmt::println("data : {0:x}" ,static_cast<int>(data) ); // 255 in hex(ff)

    ++data;  // Overflow
    fmt::println("data : {}" , static_cast<int>(data) ); // 256


    data = 1;

    --data;
    fmt::println("data : {}" , static_cast<int>(data) );

    --data;
    fmt::println("data : {}" , static_cast<int>(data) );

   
    return 0;
}