#include "utilities.h"


#include <fmt/format.h>
#include "dog.h"

//#2: Unique ptr from shared ptr
std::unique_ptr<Dog> get_unique_ptr()
{
  std::unique_ptr<Dog> dog_ptr_internal = std::make_unique<Dog>("Phil");
  return dog_ptr_internal;
}

//#4: Shared pointers as function parameters and return types
// Passing by value
void use_dog_v1(std::shared_ptr<Dog> dog)
{
  fmt::println("shared_ptr passed by value , dog_name : {}", dog->get_name());
  fmt::println("use count in use_dog_v1 : {}", dog.use_count());// 2
}


// Passing by non const reference
void use_dog_v2(std::shared_ptr<Dog> &dog)
{
  // Since no copy is made, we won't see the reference count increment here
  dog->set_dog_name("Riol");
  // dog.reset(new Dog()); // Passed by non const ref
  fmt::println(
    "shared_ptr passed by non const reference (dog name changed in function) , dog_name : {}",
    dog->get_name());
  fmt::println("use count in use_dog_v2 : {}", dog.use_count());
}


void use_dog_v3(const std::shared_ptr<Dog> &dog)
{
  // Since no copy is made, we won't see the reference count increment here
  dog->set_dog_name("Simy");// We can change the dog object even though
  // shared_ptr is passed by ref. The const protects the shared_ptr
  //  object itself, not the pointed to object.
  // dog.reset(new Dog()); // Passed by const ref
  fmt::println("shared_ptr passed by const reference (dog name changed in function) , dog_name : {}", dog->get_name());
  fmt::println("use count in use_dog_v3 : {}", dog.use_count());
}


// Returning by value
//      Returning a shared_ptr by value goes through return value optimization and at the
//                 end no copy is made, we have a single shared ptr with a reference count of 1,
//                 just like when we create a shared directly with make_shared.
std::shared_ptr<Dog> get_shared_ptr_v1()
{
  std::shared_ptr<Dog> dog_ptr = std::make_shared<Dog>("Internal Dog_v1");
  fmt::println("Managed dog address(in) : {}", fmt::ptr(dog_ptr.get()));
  return dog_ptr;
}


// RETURNING SHARED_PTR BY REF( CONST OR NON CONST) IS A RECIPE
// FOR DISASTER. DON'T DO IT.
// returning std::shared_ptr by reference doesn't properly increment the reference count,
//  which opens up the risk of deleting something at the wrong time. We'll get a crash in older versions
//  of gcc, gcc 14 now rightfully flags this as a compiler error.
/*
std::shared_ptr<Dog> &get_shared_ptr_v2()
{
  std::shared_ptr<Dog> dog_ptr = std::make_shared<Dog>("Internal Dog_v2");
  return dog_ptr;
}
*/

//Module purview
void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void shared_pointers()
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
}

//#2: Unique pointer from shared pointer
void unique_pointer_from_shared_pointer()
{

  // Create shared pointers from unique_ptrs
  std::unique_ptr<int> unique_ptr_int_1 = std::make_unique<int>(22);// Heap object
  std::unique_ptr<Dog> unique_ptr_dog_1 = std::make_unique<Dog>("Halz");// Heap object

  // Create shared pointers from unique_ptrs
  // Ownership moves from unique_ptrs to shared_ptrs from now on
  std::shared_ptr<int> shared_ptr_int_1 = std::move(unique_ptr_int_1);
  std::shared_ptr<Dog> shared_ptr_dog_1 = std::move(unique_ptr_dog_1);
  // std::shared_ptr<Dog> shared_ptr_dog_2 = unique_ptr_dog_1; // Direct assignment
  //  Doesn't work, you have to do
  //  an explicit std::move to move ownership


  fmt::println("shared_ptr_int_1 use count : {}", shared_ptr_int_1.use_count());
  fmt::println("shared_ptr_dog_1 use count : {}", shared_ptr_dog_1.use_count());
  //	fmt::println(std::boolalpha;
  fmt::println("unique_ptr_int_1 : {}", static_cast<bool>(unique_ptr_int_1));
  fmt::println("unique_ptr_dog_1 : {}", static_cast<bool>(unique_ptr_dog_1));

  fmt::println("unique_ptr_int_1 : {}", fmt::ptr(unique_ptr_int_1));
  fmt::println("unique_ptr_dog_1 : {}", fmt::ptr(unique_ptr_dog_1));


  // Can create copies because now we hold a shared ptr
  fmt::println("\n");
  fmt::println("Making copies...");
  std::shared_ptr<int> shared_ptr_int_3{ shared_ptr_int_1 };
  std::shared_ptr<Dog> shared_ptr_dog_3{ shared_ptr_dog_1 };

  fmt::println("shared_ptr_int_1 use count : {}", shared_ptr_int_1.use_count());
  fmt::println("shared_ptr_dog_1 use count : {}", shared_ptr_dog_1.use_count());
  fmt::println("shared_ptr_int_3 use count : {}", shared_ptr_int_3.use_count());
  fmt::println("shared_ptr_dog_3 use count : {}", shared_ptr_dog_3.use_count());


  // Can't transform from std::shared_ptr to std::unique_ptr
  // The reason this transformation is disabled isn't hard to think of.
  //          At any given moment, there may be any number of shared pointers
  //          spread through your entire application working on the same object,
  //          If you were to instantly make one of those a unique ptr, what do
  //          you do with the remaining copies?? Unique ptr can't have copies
  //          anyway. So the compiler prevents you from doing this.
  // std::unique_ptr<int> unique_ptr_illegal_1 {shared_ptr_int_3}; // Compiler error
  // std::unique_ptr<int> unique_ptr_illegal_2 =shared_ptr_int_3; // Compiler error
  // std::unique_ptr<int> unique_ptr_illegal_3 =std::move(shared_ptr_int_3); // Compiler error


  // Returning unique_ptr to unique_ptr
  fmt::println("\n");
  fmt::println("Returning unique_ptr from function to unique ptr");
  std::unique_ptr<Dog> unique_ptr_dog_2 = get_unique_ptr();// This implicitly moves
  // ownership to dog_ptr9_unique
  if (unique_ptr_dog_2) fmt::println("unique_ptr_dog_2 dog name : {}", unique_ptr_dog_2->get_name());


  // Returning unique_ptr to shared_ptr
  fmt::println("\n");
  fmt::println("Returning unique_ptr from function to shared ptr");
  std::shared_ptr<Dog> shared_ptr_dog_4 =
    get_unique_ptr();// This implicitly moves
  // ownership to shared_ptr_dog_4. Implicitly does something
  // like this :
  // std::shared_ptr<Dog> shared_ptr_dog_4 = std::move(dog_ptr_internal);
  // moving ownership to a shared pointer whose reference count becomes 1.
  if (shared_ptr_dog_4) {
    fmt::println("shared_ptr_dog_4 name 	 : {}", shared_ptr_dog_4->get_name());
    fmt::println("shared_ptr_dog_4 use count : {}", shared_ptr_dog_4.use_count());
  }
}

//#3: Shared pointers with arrays
void shared_pointers_with_arrays()
{
  // C++17 only : Recommended
  std::shared_ptr<int[]> shared_ptr_int_arr_1(new int[10]{ 1, 2, 3, 4, 5, 6, 7, 8 });
  std::shared_ptr<Dog[]> shared_ptr_dog_arr_1(new Dog[10]{ Dog("Dog1"), Dog("Dog2") });


  // Setting elements
  shared_ptr_int_arr_1[3] = 28;
  shared_ptr_dog_arr_1[1] = Dog("Fluzzy");

  // Read int array
  fmt::println("\n");
  fmt::println("Reading data from arrays");
  fmt::println("Reading shared_ptr_int_arr_1: ");
  for (size_t i{ 0 }; i < 10; ++i) { fmt::println("shared_ptr_int_arr_1[{}] : {}", i, shared_ptr_int_arr_1[i]); }

  fmt::println("\n");
  fmt::println("Reading shared_ptr_dog_arr_1: ");
  for (size_t i{ 0 }; i < 10; ++i) {
    fmt::println("shared_ptr_dog_arr_1[{}] : {}", i, shared_ptr_dog_arr_1[i].get_name());
  }
}

//#4: shared pointers as function parameters and return types
void shared_pointers_as_function_parameters_and_return_types()
{
  // Passing by value : A copy will be made, increment the ref count in function body
  /*
          fmt::println("\n");
          fmt::println( "Passing shared_ptr by value : " );

          std::shared_ptr<Dog> shared_ptr_dog_1 = std::make_shared<Dog>("Filld");
          fmt::println( "shared_ptr_dog_1 use count(before) : {}"
                                                                                                                          , shared_ptr_dog_1.use_count() ); //1
          use_dog_v1(shared_ptr_dog_1);

          fmt::println( "shared_ptr_dog_1 use count(after) : {}"
                                                                                                                          , shared_ptr_dog_1.use_count() ); //1
  */


  // Passing by non const reference
  //		No copy is made, reference count doesn't increment in function body
  /*
  fmt::println( "\n");
  fmt::println( "Passing by non const reference : " );
  std::shared_ptr<Dog> shared_ptr_dog_2 = std::make_shared<Dog>("Flizy");

  fmt::println( "shared_ptr_dog_2 use count(before) : {}"
                                                                                                                  , shared_ptr_dog_2.use_count() );
  use_dog_v2(shared_ptr_dog_2);

  fmt::println( "shared_ptr_dog_2 use count(after) : {}"
                                                                                                                  , shared_ptr_dog_2.use_count() );
  */

  // Passing by const reference
  // The const just protects the shared pointer object itself, it doesn't
  // protect the pointed to value from changes.
  /*
          fmt::println("\n");
          fmt::println( "Passing by const reference : " );

          std::shared_ptr<Dog> shared_ptr_dog_3 = std::make_shared<Dog>("Kitzo");

          fmt::println( "shared_ptr_dog_3 use count(before) : {}"
                                                                                                                          , shared_ptr_dog_3.use_count() );//1
          use_dog_v3(shared_ptr_dog_3);

          fmt::println( "shared_ptr_dog_3 use count(after) : {}"
                                                                                                                          , shared_ptr_dog_3.use_count() ); //1

  */

  // Returning by value
  //      Returning a shared_ptr by value goes through return value optimization and at the
  //                end no copy is made, we have a single shared ptr with a reference count of 1, just
  //                like when we create a shared directly with make_shared.
  /*
  std::shared_ptr<Dog> shared_ptr_dog_4 = get_shared_ptr_v1();
  fmt::println( "Managed dog address (out) : {}" , fmt::ptr(shared_ptr_dog_4.get()) );
  fmt::println( "shared_ptr_dog_4 use count : {}" , shared_ptr_dog_4.use_count() );
  */

  // Returning by reference : not recommended.
  //std::shared_ptr<Dog> &shared_ptr_dog_5 = get_shared_ptr_v2();
  //fmt::println("ref count : {}", shared_ptr_dog_5.use_count());
}