#include <iostream>

int global_var1{23}; // global variable


void some_function(){
    int local_var{10};
    std::cout << "Inside function global_var : " << global_var1 << std::endl;
    std::cout << "Inside functoin local_var : " << local_var << std::endl;
}

void some_other_function(){
    //local_var = 5;
}



int main(){
 std::cout << "Inside main function global_var : " << global_var1 << std::endl;
 //local_var = 5;
   
    return 0;
}