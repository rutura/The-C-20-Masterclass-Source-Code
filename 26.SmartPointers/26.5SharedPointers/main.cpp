#include <iostream>
#include <memory>
#include "dog.h"



int main(){

    //shared pointers to fundamental types
    /*
    {

        std::shared_ptr<int> int_ptr_1 {new int{20}};
        
        std::cout << "The pointed to value is : " << *int_ptr_1 << std::endl;
        *int_ptr_1 = 40; // Use the pointer to assign
        std::cout << "The pointed to value is : " << *int_ptr_1 << std::endl;
        std::cout << "Use count : " << int_ptr_1.use_count() << std::endl; //1

        std::cout << "----" << std::endl;

        //Copying

        std::shared_ptr<int> int_ptr_2 = int_ptr_1; // Use count : 2
        
        std::cout << "The pointed to value is (through int_ptr2)  : " << *int_ptr_2 << std::endl;
        *int_ptr_2 = 70;
        std::cout << "The pointed to value is (through int_ptr2) : " << *int_ptr_2 << std::endl;
        
        std::cout << "Use count for int_ptr_1 : " << int_ptr_1.use_count() << std::endl;
        std::cout << "Use count for int_ptr_2 : " << int_ptr_2.use_count() << std::endl;


        //Other ways to initialize shared pointers
        std::cout << "-----" << std::endl;
        std::shared_ptr<int> int_ptr_3; // nullptr
        int_ptr_3 = int_ptr_1; // Use count : 3

        std::shared_ptr<int> int_ptr_4{nullptr};
        int_ptr_4 = int_ptr_1; // Use count : 4
        
        std::shared_ptr<int> int_ptr_5{int_ptr_1}; // Use count : 5
        
         std::cout << "The pointed to value is (through int_ptr5)  : " << *int_ptr_5 << std::endl;
        *int_ptr_5 = 100;
        std::cout << "The pointed to value is (through int_ptr5) : " << *int_ptr_5 << std::endl;
        
        std::cout << "Use count for int_ptr_1 : " << int_ptr_1.use_count() << std::endl;
        std::cout << "Use count for int_ptr_2 : " << int_ptr_2.use_count() << std::endl;
        std::cout << "Use count for int_ptr_3 : " << int_ptr_3.use_count() << std::endl;
        std::cout << "Use count for int_ptr_4 : " << int_ptr_4.use_count() << std::endl;
        std::cout << "Use count for int_ptr_5 : " << int_ptr_5.use_count() << std::endl;


        //Use a shared pointer to manage an already existing piece of memory
        std::cout << "-----" << std::endl;
        std::cout << "Use a shared pointer to manage an already existing piece of memory :" << std::endl;
        int * int_ptr_raw = new int(33);
        
        std::shared_ptr<int> int_ptr_6 {int_ptr_raw};
        int_ptr_raw = nullptr;
        std::cout << "The value pointed to by int_ptr_raw is (through int_ptr_6) : " << *int_ptr_6 << std::endl;
        std::cout << "Use count for int_ptr_6 is : " << int_ptr_6.use_count() << std::endl;
        std::cout << "raw pointer : " << int_ptr_raw << std::endl;
        std::cout << "int_ptr_6.get() : " << int_ptr_6.get() << std::endl;


        //Reset : decrements the use count and sets the pointer to nullptr
        std::cout << std::endl;
        std::cout << "Reset..." << std::endl;
        int_ptr_5.reset(); // decrements reference count and sets int_ptr5 to nullptr
                        // after this if you show use count, for int_ptr5,you'll get 0
        std::cout << "Use count for int_ptr_1 : " << int_ptr_1.use_count() << std::endl;
        std::cout << "Use count for int_ptr_2 : " << int_ptr_2.use_count() << std::endl;
        std::cout << "Use count for int_ptr_3 : " << int_ptr_3.use_count() << std::endl;
        std::cout << "Use count for int_ptr_4 : " << int_ptr_4.use_count() << std::endl;
        std::cout << "Use count for int_ptr_5 : " << int_ptr_5.use_count() << std::endl;
        std::cout << "int_ptr_5.get() : " << int_ptr_5.get() << std::endl;


         //Can get the raw pointer address and use the ptr in if statements (castable to bool)
		std::cout << std::endl;
		std::cout << "Casting to bool and using in if statements..." << std::endl;
        std::cout << "int_ptr_4 : " << int_ptr_4 << std::endl;
        std::cout << "int_ptr_4.get() : " << int_ptr_4.get() << std::endl;
		std::cout << std::boolalpha;
        std::cout << "int_ptr_4->bool : " << static_cast<bool>(int_ptr_4) << std::endl;
        std::cout << "int_ptr_5->bool : " << static_cast<bool>(int_ptr_5) << std::endl;
        
        if(int_ptr_4){
            std::cout << "int_ptr_4 pointing to something valid" << std::endl;
        }else{
            std::cout << "int_ptr_4 pointing to nullptr" << std::endl;
        }


        std::cout << "Resetting the pointers... " << std::endl;
        int_ptr_4.reset();
        int_ptr_3.reset();
        int_ptr_2.reset();
        int_ptr_1.reset();
        std::cout << "Use count for int_ptr_1 : " << int_ptr_1.use_count() << std::endl;
        std::cout << "Use count for int_ptr_2 : " << int_ptr_2.use_count() << std::endl;
        std::cout << "Use count for int_ptr_3 : " << int_ptr_3.use_count() << std::endl;
        std::cout << "Use count for int_ptr_4 : " << int_ptr_4.use_count() << std::endl;
        std::cout << "Use count for int_ptr_5 : " << int_ptr_5.use_count() << std::endl;
		
    }
    */


   //Shared pointers with custom types
   /*
   {
		std::shared_ptr<Dog> dog_ptr_1{ new Dog("Dog1")};
        dog_ptr_1->print_info();
        
        std::cout << "Use count : " << dog_ptr_1.use_count() << std::endl;
        
        std::shared_ptr<Dog> dog_ptr_2 = dog_ptr_1; // Use count : 2
        
        std::cout << "Use count for dog_ptr_1 : " << dog_ptr_1.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_2 : " << dog_ptr_2.use_count() << std::endl;

		//Initializing
        std::cout << std::endl;
		std::cout << "Initializing..." << std::endl;
        std::shared_ptr<Dog> dog_ptr_3;
        dog_ptr_3 = dog_ptr_1; // Use count : 3

        std::shared_ptr<Dog> dog_ptr_4{nullptr};
        dog_ptr_4 = dog_ptr_1; // Use count : 4
        
        std::shared_ptr<Dog> dog_ptr_5{dog_ptr_1}; // Use count : 5
          
        std::cout << std::endl;
        std::cout << "Use count for dog_ptr_1 : " << dog_ptr_1.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_2 : " << dog_ptr_2.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_3 : " << dog_ptr_3.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_4 : " << dog_ptr_4.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_5 : " << dog_ptr_5.use_count() << std::endl;
        



        //Can also initialize from an already existing raw pointer
        
        std::cout << std::endl;
		std::cout << "Initializing from already existing raw pointer" << std::endl;
        
        Dog * dog_ptr_raw = new Dog("Ralso");
        std::shared_ptr<Dog> dog_ptr_6 {dog_ptr_raw};
        dog_ptr_raw = nullptr;

        dog_ptr_6->print_info();
        std::cout << "Use count for dog_ptr_6 is : " << dog_ptr_6.use_count() << std::endl;
        std::cout << "dog_ptr_raw : " << dog_ptr_raw << std::endl;


       //Reset : decrements the use count and sets the pointer to nullptr
        std::cout << std::endl;
        std::cout << "Resetting" << std::endl;
        dog_ptr_5.reset(); // decrements reference count and sets int_ptr5 to nullptr
                        // after this if you show use count, for int_ptr5,you'll get 0
        std::cout << "Use count for dog_ptr_1 : " << dog_ptr_1.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_2 : " << dog_ptr_2.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_3 : " << dog_ptr_3.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_4 : " << dog_ptr_4.use_count() << std::endl;
        std::cout << "Use count for dog_ptr_5 : " << dog_ptr_5.use_count() << std::endl;
		
		
        //Can get the raw pointer address and use the ptr in if statements
		std::cout << std::endl;
		std::cout << "Casting to bool and using in if statements..." << std::endl;
        std::cout << "dog_ptr_4 : " << dog_ptr_4 << std::endl;
        std::cout << "dog_ptr_4.get() : " << dog_ptr_4.get() << std::endl;
        std::cout << "dog_ptr_4->bool : " << static_cast<bool>(dog_ptr_4) << std::endl;
        std::cout << "dog_ptr_5->bool : " << static_cast<bool>(dog_ptr_5) << std::endl;
        
        if(dog_ptr_5){
            std::cout << "dog_ptr_5 pointing to something valid" << std::endl;
        }else{
            std::cout << "dog_ptr_5 pointing to nullptr" << std::endl;
        }
   }
   */


   //make_shared
   {
		std::shared_ptr<int> int_ptr_6 = std::make_shared<int>(55);
        std::cout << "The value pointed to by int_ptr_6 is : " << *int_ptr_6 << std::endl;
        
        std::shared_ptr<Dog> dog_ptr_6 = std::make_shared<Dog>("Salz");
        dog_ptr_6->print_info();
        
        std::cout << "int_ptr_6 use count : " << int_ptr_6.use_count() << std::endl;//1
        std::cout << "dog_ptr_6 use count : " << dog_ptr_6.use_count() << std::endl;//1


		//Share the object(data) with other shared_ptr's
        std::cout << std::endl;
        std::cout << "Share the object(data) with other shared_ptr's" << std::endl;
        std::shared_ptr<int> int_ptr_7 {nullptr};
        int_ptr_7 = int_ptr_6;
        
        std::shared_ptr<Dog> dog_ptr_7 {nullptr};
        dog_ptr_7 = dog_ptr_6;
        
        std::cout << "int_ptr6 use count : " << int_ptr_6.use_count() << std::endl;
        std::cout << "dog_ptr6 use count : " << dog_ptr_6.use_count() << std::endl;


        std::cout << std::endl;
        std::cout << "Reset ptr6's" << std::endl;
        int_ptr_6.reset(); // decrement reference count, and set int_ptr6 to nullptr
                            // if reference count is zero, release the managed memory
        dog_ptr_6.reset();
        std::cout << "int_ptr_6 use count : " << int_ptr_6.use_count() << std::endl;
        std::cout << "dog_ptr_6 use count : " << dog_ptr_6.use_count() << std::endl;
		std::cout << "int_ptr_7 use count : " << int_ptr_7.use_count() << std::endl;
        std::cout << "dog_ptr_7 use count : " << dog_ptr_7.use_count() << std::endl;
        

   }

    return 0;
}