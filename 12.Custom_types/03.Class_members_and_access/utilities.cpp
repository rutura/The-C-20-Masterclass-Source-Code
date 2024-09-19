#include "utilities.h"

#include "cylinder.h"
#include "dog.h"
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

/*
void getters_as_setters()
{
  const Dog dog1("Fluffy", "Shepherd", 2);
  dog1.print_info();
  fmt::println("dog name : {}", dog1.name());// Getter

  // Modify the object
  // dog1.name() = "Milou"; // Setter
  dog1.print_info();
}
*/


void manage_objects_through_pointers()
{
  Cylinder cylinder1(10, 10);

  cylinder1.volume();

  // Managing a stack object through pointers
  Cylinder *p_cylinder1 = &cylinder1;

  //    fmt::println("volume : {}" , (*p_cylinder1).volume() );
  fmt::println("volume : {}", p_cylinder1->volume());

  // Create a cylinder heap object through the new operator
  Cylinder *p_cylinder2 = new Cylinder(100, 2);// Heap

  fmt::println("volume(clylinder2) : {}", p_cylinder2->volume());
  fmt::println("base_rad(cylinder2) : {}", p_cylinder2->get_base_radius());


  delete p_cylinder2;
}

void the_this_pointer()
{
  Dog dog1("Fluffy", "Shepherd", 2);// Constructor
  dog1.print_info();

  /*
  dog1.set_dog_name("Pumba");
  dog1.set_dog_breed("Wire Fox Terrier");
  dog1.set_dog_age(4);
  */

  // Chained calls using pointers
  // dog1.set_dog_name("Pumba")->set_dog_breed("Wire Fox Terrier")->set_dog_age(4);

  // Chained calls using references
  dog1.set_dog_name("Pumba").set_dog_breed("Wire Fox Terrier").set_dog_age(4);


  dog1.print_info();


  fmt::println("Done!");
  // Destructor
}