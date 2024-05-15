#include <fmt/format.h>

enum Direction : unsigned char { TopLeft = 64, TopRight, Center, BottomLeft, BottomRight };

enum Tool { Pen, Marker, Eraser, Rectangle, Circle, PaintBucket };


int main()
{

  Direction direction{ Direction::TopLeft };
  Tool tool{ Tool::Pen };

  fmt::println("direction : {}", static_cast<unsigned int>(direction));
  // fmt::println( "tool : {}" , tool );
  // fmt::println( "(tool > direction) : {}" , (tool > direction) );

  return 0;
}