#include <iostream>
#include "scores.h"


int main(){

  
    Scores math("Math");
    math.print_info();

    for(size_t i{} ; i <20 ; ++i){
        if(i==0){
            math[0] = 73.7;
        }else{
            math[i] = math[i-1] + 0.56;
        }
    }

    math.print_info(); 

    std::cout << "------" << std::endl;
   

    //Const objecst
    const Scores geo("Geography");
    std::cout << "geo [5] : " << geo[5] << std::endl;



    return 0;
}