#include <iostream>

int main(){

    for (size_t i{0} , x {5}, y{22} ; y > 15 ; ++i , x+=5 , y-=1){
        std::cout << "i: " << i << ", x : " << x << ", y : " << y << std::endl;

    }
   
    return 0;
}