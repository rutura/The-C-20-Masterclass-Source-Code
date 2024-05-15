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

  switch (double strength{ 3.56 }; tool) {
  case Pen: {
    fmt::println("Active tool is Pen. strength : {}", strength);
  } break;

  case Marker: {
    fmt::println("Active tool is Marker. strength : {}", strength);
  } break;


  case Eraser:
  case Rectangle:
  case Circle: {
    fmt::println("Drawing Shapes. strength : {}", strength);
  } break;

  case Ellipse: {
    fmt::println("Active tool is Ellipse. strength : {}", strength);
  } break;

  default: {
    fmt::println("No match found. strength : {}", strength);
  } break;
  }

  fmt::println("Moving on");
  // strength++;


  return 0;
}