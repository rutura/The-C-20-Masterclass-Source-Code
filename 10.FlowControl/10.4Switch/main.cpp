#include <fmt/format.h>


// Tools
const int Pen{ 10 };
const int Marker{ 20 };
const int Eraser{ 30 };
const int Rectangle{ 40 };
const int Circle{ 50 };
const int Ellipse{ 60 };


int main()
{

  int tool{ Eraser };

  switch (tool) {
  case Pen: {
    fmt::println("Active tool is Pen");
  } break;

  case Marker: {
    fmt::println("Active tool is Marker");
  } break;


  case Eraser:
  case Rectangle:
  case Circle: {
    fmt::println("Drawing Shapes");
  } break;

  case Ellipse: {
    fmt::println("Active tool is Ellipse");
  } break;

  default: {
    fmt::println("No match found");
  } break;
  }

  fmt::println("Moving on");


  /*
  // Condition can only be integer of enum (We'll learn about enums later in the course)
  std::string name {"John"};
  switch (name) // Compiler error!
  {

  }
  */


  return 0;
}