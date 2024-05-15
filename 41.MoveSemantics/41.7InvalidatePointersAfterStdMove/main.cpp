
#include "boxcontainer.h"

void populate_box(BoxContainer<int> &box, int modifier)
{
  for (size_t i{ 0 }; i < 20; ++i) { box.add((i + 1) * modifier); }
}


int main()
{

  BoxContainer<int> box1;
  populate_box(box1, 2);

  fmt::println("box1 : {}", box1);

  BoxContainer<int> box2(std::move(box1));

  fmt::println("box2 : {}", box2);
  fmt::println("box1 : {}", box1);


  fmt::println("------");

  box1.add(34);
  box1.add(4);
  fmt::println("box1 : {}", box1);


  return 0;
}