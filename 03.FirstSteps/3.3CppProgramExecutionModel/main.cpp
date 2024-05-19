/*
    . Exploring the C++ program execution model
    . Reference the lecture on execution model in v 1.0 of the course.
    . Same content as v 1.0 in the course but updated to use the fmt library.

*/

import utilities;


int main()
{

  int a = 10;
  int b = 5;
  int c;

  print_msg("Statement 1");
  print_msg("Statement 2");
  c = f_add(a, b);
  print_number(c);
  print_msg("Statement 3");
  print_msg("Statement 4");

  return 0;
}