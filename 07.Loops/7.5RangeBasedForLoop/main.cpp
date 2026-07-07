#include <iostream>



int main(){

    int bag_of_values [] {1,2,3,4,5,6,7,8,9,10}; // This is a collection of integers
    // The variable value will be assigned a value from the values array on each iteration
	
    /*
    for(size_t i {0} ; i < 10 ; ++i){
        std::cout << "value : " << bag_of_values[i] << std::endl;
    }
    */
	

    /*
    for (int value : bag_of_values){
        //value holds a copy of the current iteration in the whole bag
        std::cout << " value : " << value << std::endl;
    }
    */


   //Specify the collection in place
   /*
    for (int value : {1,2,3,4,5,6,7,8,9,10}){
        //value holds a copy of the current iteration in the whole bag
        std::cout << " value : " << value << std::endl;
    }
    */

   //Auto type deduction
	for (auto value : {1,2,3,4,5,6,7,8,9,10}){
        //value holds a copy of the current iteration in the whole bag
        std::cout << " value : " << value << std::endl;
    }
   
    return 0;
}