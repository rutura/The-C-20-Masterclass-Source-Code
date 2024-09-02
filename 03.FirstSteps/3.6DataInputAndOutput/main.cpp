// 2:31:35
// https://youtu.be/8jLOx1hD3_o?t=9095

#include <iostream>
#include <string>

int main()
{
  /*
  std::cout << "Hello from C++20!" << std::endl;

  int age{48};

  std::cout << "Age: " << age << std::endl;

  std::cerr << "An error occurred." << std::endl;

  std::clog << "This is a log message." << std::endl;
  */

/* 
  int age1;

  std::cout << "Type your name and age>" << std::endl;

  std::string name;

  std::cin >> name >> age1;

  std::cout << "Hello " << name << "! You are " << age1 << " years old!" << std::endl;
 */

  std::string full_name;
  int age2;

  std::cout << "Enter your full name and your age>" << std::endl;

  std::getline(std::cin, full_name);
  std::cin >> age2;

  std::cout << "Hello " << full_name << "! You are "
            << age2 << " years old!" << std::endl;

  return 0;
}