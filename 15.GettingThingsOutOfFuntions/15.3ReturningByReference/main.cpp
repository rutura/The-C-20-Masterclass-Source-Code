#include <iostream>

int& max_return_reference(int& a, int& b)
{
    if(a > b) {
        return a;
    } else {
        return b;
    }
}

int& sum( int& a, int& b){
    int result = a + b; 
    return result;// Reference to local variable returned
}


int& max_input_by_value (int a, int b)
{
    if(a > b) {
        return a; // Reference to local variable returned
    } else {
        return b; // Reference to local variable returned
    }
}


int main(){

    /*
    int x{14};
    int y{9};
    int& ref_max = max_return_reference(x,y); // Reference
    int val = max_return_reference(x,y); // Copy

    std::cout << "ref_max : " << ref_max << std::endl;
    std::cout << "val : " << val << std::endl;
    std::cout << "x : " << x << std::endl;
    std::cout << "y : " << y << std::endl;

    ref_max++;

    std::cout << "----- " << std::endl;
    std::cout << "ref_max : " << ref_max << std::endl; // 15
    std::cout << "val : " << val << std::endl; // 14
    std::cout << "x : " << x << std::endl; // 15
    std::cout << "y : " << y << std::endl; // 9

    */


   /*
    int x{14};
    int y{9};
    int& result = sum(x,y); // Reference
    std::cout << "result : " << result << std::endl;
    */


    int x{14};
    int y{9};
    int& result = max_input_by_value(x,y); // Reference
    std::cout << "result : " << result << std::endl;



    std::cout << "Done!" << std::endl;
   
    return 0;
}