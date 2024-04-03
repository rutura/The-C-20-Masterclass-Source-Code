#include "circle.h"
#include "oval.h"
#include "shape.h"
#include <fmt/format.h>
#include <memory>

int main()
{

  Circle circle1(7.2, "circle1");
  Oval oval1(13.3, 1.2, "Oval1");
  Circle circle2(11.2, "circle2");
  Oval oval2(31.3, 15.2, "Oval2");
  Circle circle3(12.2, "circle3");
  Oval oval3(53.3, 9.2, "Oval3");


  // If you store raw object data in an array set up to store base class objects
  // the data is going to be sliced off!
  /*
  fmt::printl( "sizeof (circle1) : {}" , sizeof(circle1) );
  Shape shapes1[] {circle1,oval1,circle2,oval2,circle3,oval3};

  for(Shape& s : shapes1){
       fmt::printl( "sizeof (object) : {}" , sizeof(s) );
      s.draw(); //
  }
  */

  // What if we store in references? Compiler error : references aren't left assignable
  // const Shape& shapes2[] {circle1,oval1,circle2,oval2,circle3,oval3};


  // Raw pointers
  /*
      Shape* shapes3[] {&circle1,&oval1,&circle2,&oval2,&circle3,&oval3};

      for ( Shape* shape_ptr : shapes3){
              fmt::printl( "Inside array , sizeof(*shape_ptr) : {}" , sizeof(*shape_ptr) );
              shape_ptr->draw();
      }
  */


  // Smart pointers
  std::shared_ptr<Shape> shapes4[]{ std::make_shared<Circle>(12.2, "Circle4"),
    std::make_shared<Oval>(10.0, 20.0, "Oval4") };
  for (auto &s : shapes4) { s->draw(); }


  return 0;
}