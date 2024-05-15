#include "boxcontainer.h"

int main()
{

  // Operator+=
  BoxContainer box1;
  box1.add(1);
  box1.add(2);
  box1.add(3);

  fmt::println("box1 : {}", make_streamable(box1));

  BoxContainer box2;
  box2.add(10);
  box2.add(20);
  box2.add(30);

  fmt::println("box2 : {}", make_streamable(box2));

  fmt::println("operator+= : ");
  box2 += box1;
  fmt::println("box2 : {}", make_streamable(box2));
  box2.add(50);
  fmt::println("box2 : {}", make_streamable(box2));

  fmt::println("--------------------------");

  //----------------------------------------------------

  // Operator+
  fmt::println("operator+ : ");

  fmt::println("box1 : {}", make_streamable(box1));
  fmt::println("box2 : {}", make_streamable(box2));

  BoxContainer box3;
  box3.add(81);
  box3.add(82);

  fmt::println("box3 : {}", make_streamable(box3));

  fmt::println("box1 + box3 : {}", make_streamable((box1 + box3)));

  fmt::println("--------------------------");

  //----------------------------------------------------

  // Operator=
  fmt::println("operator= : ");

  fmt::println("box1 : {}", make_streamable(box1));
  fmt::println("box2 : {}", make_streamable(box2));
  fmt::println("box3 : {}", make_streamable(box3));

  box3 = box2;

  fmt::println("box1 : {}", make_streamable(box1));
  fmt::println("box2 : {}", make_streamable(box2));
  fmt::println("box3 : {}", make_streamable(box3));


  return 0;
}