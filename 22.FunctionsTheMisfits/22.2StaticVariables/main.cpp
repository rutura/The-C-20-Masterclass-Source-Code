#include <iostream>

size_t dog_count{0};// Global scope


unsigned int add_student(){
     static unsigned int student_count{0}; // The scope of this var is in add_student,
							  // but it's life time goes beyond the function execution.
    student_count++;
    ++dog_count;
    return student_count;
}

void do_something(){
    //--student_count; // Compiler error
    ++dog_count;
}

int main(){

    /*
    std::cout << "student count : " << add_student()  << std::endl;//1
    std::cout << "student count : " << add_student()  << std::endl;//2
    std::cout << "student count : " << add_student()  << std::endl;//3
    */

   for(size_t i {} ; i < 20 ;++i){
       std::cout << "student count : " << add_student()  << std::endl;
   }
   
    return 0;
}