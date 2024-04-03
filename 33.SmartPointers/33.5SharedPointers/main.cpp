#include "dog.h"
#include <fmt/format.h>
#include <memory>


int main()
{

  // shared pointers to fundamental types
  /*
      {

          std::shared_ptr<int> int_ptr_1 {new int{20}};

          fmt::println( "The pointed to value is : {}" , *int_ptr_1 );
          *int_ptr_1 = 40; // Use the pointer to assign
          fmt::println( "The pointed to value is : {}" , *int_ptr_1 );
          fmt::println( "Use count : {}" , int_ptr_1.use_count() ); //1

          fmt::println( "----" );

          //Copying

          std::shared_ptr<int> int_ptr_2 = int_ptr_1; // Use count : 2

          fmt::println( "The pointed to value is (through int_ptr2)  : {}" , *int_ptr_2 );
          *int_ptr_2 = 70;
          fmt::println( "The pointed to value is (through int_ptr2) : {}" , *int_ptr_2 );

          fmt::println( "Use count for int_ptr_1 : {}" , int_ptr_1.use_count() );
          fmt::println( "Use count for int_ptr_2 : {}" , int_ptr_2.use_count() );


          //Other ways to initialize shared pointers
          fmt::println( "-----" );
          std::shared_ptr<int> int_ptr_3; // nullptr
          int_ptr_3 = int_ptr_1; // Use count : 3

          std::shared_ptr<int> int_ptr_4{nullptr};
          int_ptr_4 = int_ptr_1; // Use count : 4

          std::shared_ptr<int> int_ptr_5{int_ptr_1}; // Use count : 5

           fmt::println( "The pointed to value is (through int_ptr5)  : {}" , *int_ptr_5 );
          *int_ptr_5 = 100;
          fmt::println( "The pointed to value is (through int_ptr5) : {}" , *int_ptr_5 );

          fmt::println( "Use count for int_ptr_1 : {}" , int_ptr_1.use_count() );
          fmt::println( "Use count for int_ptr_2 : {}" , int_ptr_2.use_count() );
          fmt::println( "Use count for int_ptr_3 : {}" , int_ptr_3.use_count() );
          fmt::println( "Use count for int_ptr_4 : {}" , int_ptr_4.use_count() );
          fmt::println( "Use count for int_ptr_5 : {}" , int_ptr_5.use_count() );


          //Use a shared pointer to manage an already existing piece of memory
          fmt::println( "-----" );
          fmt::println( "Use a shared pointer to manage an already existing piece of memory :" );
          int * int_ptr_raw = new int(33);

          std::shared_ptr<int> int_ptr_6 {int_ptr_raw};
          int_ptr_raw = nullptr;
          fmt::println( "The value pointed to by int_ptr_raw is (through int_ptr_6) : {}" , *int_ptr_6 );
          fmt::println( "Use count for int_ptr_6 is : {}" , int_ptr_6.use_count() );
          fmt::println( "raw pointer : {}" , fmt::ptr(int_ptr_raw ));
          fmt::println( "int_ptr_6.get() : {}" ,fmt::ptr( int_ptr_6.get() ));


          //Reset : decrements the use count and sets the pointer to nullptr
          fmt::println("\n");
          fmt::println( "Reset..." );
          int_ptr_5.reset(); // decrements reference count and sets int_ptr5 to nullptr
                          // after this if you show use count, for int_ptr5,you'll get 0
          fmt::println( "Use count for int_ptr_1 : {}" , int_ptr_1.use_count() );
          fmt::println( "Use count for int_ptr_2 : {}" , int_ptr_2.use_count() );
          fmt::println( "Use count for int_ptr_3 : {}" , int_ptr_3.use_count() );
          fmt::println( "Use count for int_ptr_4 : {}" , int_ptr_4.use_count() );
          fmt::println( "Use count for int_ptr_5 : {}" , int_ptr_5.use_count() );
          fmt::println( "int_ptr_5.get() : {}" , fmt::ptr(int_ptr_5.get() ));


           //Can get the raw pointer address and use the ptr in if statements (castable to bool)
                  fmt::println("\n");
                  fmt::println( "Casting to bool and using in if statements..." );
          fmt::println( "int_ptr_4 : {}" , fmt::ptr((int_ptr_4 )));
          fmt::println( "int_ptr_4.get() : {}" , fmt::ptr(int_ptr_4.get() ));
  //		fmt::println( std::boolalpha;
          fmt::println( "int_ptr_4->bool : {}" , static_cast<bool>(int_ptr_4) );
          fmt::println( "int_ptr_5->bool : {}" , static_cast<bool>(int_ptr_5) );

          if(int_ptr_4){
              fmt::println( "int_ptr_4 pointing to something valid" );
          }else{
              fmt::println( "int_ptr_4 pointing to nullptr" );
          }


          fmt::println( "Resetting the pointers... " );
          int_ptr_4.reset();
          int_ptr_3.reset();
          int_ptr_2.reset();
          int_ptr_1.reset();
          fmt::println( "Use count for int_ptr_1 : {}" , int_ptr_1.use_count() );
          fmt::println( "Use count for int_ptr_2 : {}" , int_ptr_2.use_count() );
          fmt::println( "Use count for int_ptr_3 : {}" , int_ptr_3.use_count() );
          fmt::println( "Use count for int_ptr_4 : {}" , int_ptr_4.use_count() );
          fmt::println( "Use count for int_ptr_5 : {}" , int_ptr_5.use_count() );

      }
  */


  // Shared pointers with custom types
  /*
     {
                  std::shared_ptr<Dog> dog_ptr_1{ new Dog("Dog1")};
          dog_ptr_1->print_info();

          fmt::println( "Use count : {}" , dog_ptr_1.use_count() );

          std::shared_ptr<Dog> dog_ptr_2 = dog_ptr_1; // Use count : 2

          fmt::println( "Use count for dog_ptr_1 : {}" , dog_ptr_1.use_count() );
          fmt::println( "Use count for dog_ptr_2 : {}" , dog_ptr_2.use_count() );

                  //Initializing
          fmt::println("\n");
                  fmt::println( "Initializing..." );
          std::shared_ptr<Dog> dog_ptr_3;
          dog_ptr_3 = dog_ptr_1; // Use count : 3

          std::shared_ptr<Dog> dog_ptr_4{nullptr};
          dog_ptr_4 = dog_ptr_1; // Use count : 4

          std::shared_ptr<Dog> dog_ptr_5{dog_ptr_1}; // Use count : 5

          fmt::println("\n");
          fmt::println( "Use count for dog_ptr_1 : {}" , dog_ptr_1.use_count() );
          fmt::println( "Use count for dog_ptr_2 : {}" , dog_ptr_2.use_count() );
          fmt::println( "Use count for dog_ptr_3 : {}" , dog_ptr_3.use_count() );
          fmt::println( "Use count for dog_ptr_4 : {}" , dog_ptr_4.use_count() );
          fmt::println( "Use count for dog_ptr_5 : {}" , dog_ptr_5.use_count() );




          //Can also initialize from an already existing raw pointer

          fmt::println("\n");
                  fmt::println( "Initializing from already existing raw pointer" );

          Dog * dog_ptr_raw = new Dog("Ralso");
          std::shared_ptr<Dog> dog_ptr_6 {dog_ptr_raw};
          dog_ptr_raw = nullptr;

          dog_ptr_6->print_info();
          fmt::println( "Use count for dog_ptr_6 is : {}" , dog_ptr_6.use_count() );
          fmt::println( "dog_ptr_raw : {}" , fmt::ptr(dog_ptr_raw ));


         //Reset : decrements the use count and sets the pointer to nullptr
          fmt::println("\n");
          fmt::println( "Resetting" );
          dog_ptr_5.reset(); // decrements reference count and sets int_ptr5 to nullptr
                          // after this if you show use count, for int_ptr5,you'll get 0
          fmt::println( "Use count for dog_ptr_1 : {}" , dog_ptr_1.use_count() );
          fmt::println( "Use count for dog_ptr_2 : {}" , dog_ptr_2.use_count() );
          fmt::println( "Use count for dog_ptr_3 : {}" , dog_ptr_3.use_count() );
          fmt::println( "Use count for dog_ptr_4 : {}" , dog_ptr_4.use_count() );
          fmt::println( "Use count for dog_ptr_5 : {}" , dog_ptr_5.use_count() );


          //Can get the raw pointer address and use the ptr in if statements
                  fmt::println("\n");
                  fmt::println( "Casting to bool and using in if statements..." );
          fmt::println( "dog_ptr_4 : {}" , fmt::ptr(dog_ptr_4 ));
          fmt::println( "dog_ptr_4.get() : {}" , fmt::ptr(dog_ptr_4.get() ));
          fmt::println( "dog_ptr_4->bool : {}" , static_cast<bool>(dog_ptr_4) );
          fmt::println( "dog_ptr_5->bool : {}" , static_cast<bool>(dog_ptr_5) );

          if(dog_ptr_5){
              fmt::println( "dog_ptr_5 pointing to something valid" );
          }else{
              fmt::println( "dog_ptr_5 pointing to nullptr" );
          }
     }
  */


  // make_shared
  {
    std::shared_ptr<int> int_ptr_6 = std::make_shared<int>(55);
    fmt::println("The value pointed to by int_ptr_6 is : {}", *int_ptr_6);

    std::shared_ptr<Dog> dog_ptr_6 = std::make_shared<Dog>("Salz");
    dog_ptr_6->print_info();

    fmt::println("int_ptr_6 use count : {}", int_ptr_6.use_count());// 1
    fmt::println("dog_ptr_6 use count : {}", dog_ptr_6.use_count());// 1


    // Share the object(data) with other shared_ptr's
    fmt::println("\n");
    fmt::println("Share the object(data) with other shared_ptr's");
    std::shared_ptr<int> int_ptr_7{ nullptr };
    int_ptr_7 = int_ptr_6;

    std::shared_ptr<Dog> dog_ptr_7{ nullptr };
    dog_ptr_7 = dog_ptr_6;

    fmt::println("int_ptr6 use count : {}", int_ptr_6.use_count());
    fmt::println("dog_ptr6 use count : {}", dog_ptr_6.use_count());


    fmt::println("\n");
    fmt::println("Reset ptr6's");
    int_ptr_6.reset();// decrement reference count, and set int_ptr6 to nullptr
                      // if reference count is zero, release the managed memory
    dog_ptr_6.reset();
    fmt::println("int_ptr_6 use count : {}", int_ptr_6.use_count());
    fmt::println("dog_ptr_6 use count : {}", dog_ptr_6.use_count());
    fmt::println("int_ptr_7 use count : {}", int_ptr_7.use_count());
    fmt::println("dog_ptr_7 use count : {}", dog_ptr_7.use_count());
  }

  return 0;
}