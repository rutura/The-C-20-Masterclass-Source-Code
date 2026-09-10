#include <iostream>
#include <memory>
#include "dog.h"


std::unique_ptr<Dog> get_unique_ptr(){
     std::unique_ptr<Dog> dog_ptr_internal = std::make_unique<Dog>("Phil");
     return dog_ptr_internal;
}



int main(){

	//Create shared pointers from unique_ptrs
	std::unique_ptr<int> unique_ptr_int_1 = std::make_unique<int>(22);//Heap object
	std::unique_ptr<Dog> unique_ptr_dog_1 = std::make_unique<Dog>("Halz"); //Heap object
        
	//Create shared pointers from unique_ptrs
	//Ownership moves from unique_ptrs to shared_ptrs from now on
	std::shared_ptr<int> shared_ptr_int_1 = std::move(unique_ptr_int_1);
	std::shared_ptr<Dog> shared_ptr_dog_1 = std::move(unique_ptr_dog_1);
	//std::shared_ptr<Dog> shared_ptr_dog_2 = unique_ptr_dog_1; // Direct assignment
                                                        // Doesn't work, you have to do
														// an explicit std::move to move ownership
														
														
	std::cout << "shared_ptr_int_1 use count : " << shared_ptr_int_1.use_count() << std::endl;
	std::cout << "shared_ptr_dog_1 use count : " << shared_ptr_dog_1.use_count() << std::endl;
	std::cout << std::boolalpha;
	std::cout << "unique_ptr_int_1 : " << static_cast<bool> (unique_ptr_int_1) << std::endl;
	std::cout << "unique_ptr_dog_1 : " << static_cast<bool> (unique_ptr_dog_1) << std::endl;

    std::cout << "unique_ptr_int_1 : " << unique_ptr_int_1 << std::endl;
    std::cout << "unique_ptr_dog_1 : " << unique_ptr_dog_1 << std::endl;


	//Can create copies because now we hold a shared ptr
	std::cout << std::endl;
	std::cout << "Making copies..." << std::endl;
	std::shared_ptr<int> shared_ptr_int_3 {shared_ptr_int_1};
	std::shared_ptr<Dog> shared_ptr_dog_3 {shared_ptr_dog_1};
	
	std::cout << "shared_ptr_int_1 use count : " << shared_ptr_int_1.use_count() << std::endl;
	std::cout << "shared_ptr_dog_1 use count : " << shared_ptr_dog_1.use_count() << std::endl;
	std::cout << "shared_ptr_int_3 use count : " << shared_ptr_int_3.use_count() << std::endl;
	std::cout << "shared_ptr_dog_3 use count : " << shared_ptr_dog_3.use_count() << std::endl;



	//Can't transform from std::shared_ptr to std::unique_ptr
		//The reason this transformation is disabled isn't hard to think of.
        //          At any given moment, there may be any number of shared pointers 
        //          spread through your entire application working on the same object, 
        //          If you were to instantly make one of those a unique ptr, what do 
        //          you do with the remaining copies?? Unique ptr can't have copies 
        //          anyway. So the compiler prevents you from doing this.
	//std::unique_ptr<int> unique_ptr_illegal_1 {shared_ptr_int_3}; // Compiler error
	//std::unique_ptr<int> unique_ptr_illegal_2 =shared_ptr_int_3; // Compiler error
	//std::unique_ptr<int> unique_ptr_illegal_3 =std::move(shared_ptr_int_3); // Compiler error
	
	

	//Returning unique_ptr to unique_ptr
	std::cout << std::endl;
	std::cout << "Returning unique_ptr from function to unique ptr" << std::endl;
	std::unique_ptr<Dog> unique_ptr_dog_2 = get_unique_ptr(); // This implicitly moves
													// ownership to dog_ptr9_unique
	if(unique_ptr_dog_2)
		std::cout << "unique_ptr_dog_2 dog name : " << unique_ptr_dog_2->get_name() << std::endl;
		
	

	//Returning unique_ptr to shared_ptr
	std::cout << std::endl;
	std::cout << "Returning unique_ptr from function to shared ptr" << std::endl;
	std::shared_ptr<Dog> shared_ptr_dog_4= get_unique_ptr(); // This implicitly moves
						// ownership to shared_ptr_dog_4. Implicitly does something
						//like this : 
						// std::shared_ptr<Dog> shared_ptr_dog_4 = std::move(dog_ptr_internal);
						//moving ownership to a shared pointer whose reference count becomes 1.
	if(shared_ptr_dog_4){
		std::cout << "shared_ptr_dog_4 name 	 : " << shared_ptr_dog_4->get_name() << std::endl;
		std::cout << "shared_ptr_dog_4 use count : " << shared_ptr_dog_4.use_count() << std::endl;
 
	}
   
    return 0;
}