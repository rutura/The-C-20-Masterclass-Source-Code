#include <fmt/format.h>


int main()
{

  const char *const students[]{ "Daniel Gray", "Tuna Philbe", "The Rock", "Kumar Singh", "Sam Ali", "Dave Mahoro" };


  // Print out the students
  fmt::println("Printing out the students : ");
  for (const char *student : students) { fmt::println("{}", student); }


  // *students[0] = 'K';

  // Can swap for new student though.
  const char *new_student{ "Bob the Great" };
  // students[0] = new_student; // Compiler error


  // Print out the students
  fmt::println("Printing out the students : ");
  for (const char *student : students) { fmt::println("{}", student); }

  return 0;
}