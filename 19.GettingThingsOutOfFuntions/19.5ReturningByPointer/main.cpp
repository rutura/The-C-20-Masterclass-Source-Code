#include <iostream>


int* max_return_pointer(int* a, int* b)
{
    if(*a > *b) {
        return a;
    } else {
        return b;
    }
}

int* max_input_by_value (int a, int b)
{
    if(a > b) {
        return &a; // Pointer to local variable returned
    } else {
        return &b; // Pointer to local variable returned
    }
}


int* sum( int* a, int* b){
    int result = *a + *b; 
    return &result;// Pointer to local variable returned
}


int main(){

    /*
    int x{56};
    int y{45};
    int* p_max = max_return_pointer(&x,&y);

    std::cout << "x : " << x << std::endl;
    std::cout << "y : " << y << std::endl;
    std::cout << "*p_max : " << *p_max << std::endl;


    ++(*p_max);

    std::cout << "-----" << std::endl;
    std::cout << "x : " << x << std::endl;
    std::cout << "y : " << y << std::endl;
    std::cout << "*p_max : " << *p_max << std::endl;
    */


   /*
    int x{56};
    int y{45};
    int* p_sum = sum(&x,&y);
    std::cout << *p_sum << std::endl;
    */


    int x{56};
    int y{45};
    int* p_sum = max_input_by_value(x,y);
    std::cout << *p_sum << std::endl;




    std::cout << "Done!" << std::endl;
   
    return 0;
}