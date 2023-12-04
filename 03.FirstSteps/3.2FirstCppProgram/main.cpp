/*
    . First C++ program
    . Introduce comments
    . Introduce errors and warnings.
    . Statements and functions
    . Coding conventions. We'll go with snake case.

*/

//One line comment

//This brings in the iostream library
#include <iostream>
#include <fmt/format.h>

/*
    This is a block comment that englobes multiple
    lines of text
*/

void print_number(int number){
    std::cout << "Number : " << number << std::endl;
}
int add_numbers( int first_param, int second_param){
    int result = first_param + second_param;
    return result;
}

int main(){

    //This is going to print Number1, Number2 and Number3.
    std::cout << "Number1" << std::endl;
    std::cout << "Number2" << std::endl;
    std::cout << "Number3" << std::endl;
    print_number(5);
    

    //Compile time error- Introduce a syntax error.
   std::cout << "Hello Word!" << std::endl;

   //Run time error - dividing by zero.
//    int value = 7/0;
//    std::cout << "value: " << value << std::endl;
  
    //The program ends after the return statement.

    int num1 = 5;
    int num2 = 6;
    int result = add_numbers(num1, num2);
    std::cout << "Result: " << result << std::endl;
    return 0;
}