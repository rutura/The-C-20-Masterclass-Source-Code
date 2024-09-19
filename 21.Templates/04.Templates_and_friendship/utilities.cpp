#include "utilities.h"

#include "templates_and_friendship_01.h"
#include "templates_and_friendship_03.h"
#include "templates_and_friendship_06.h"
#include "templates_and_friendship_07.h"
#include "templates_and_friendship_08.h"

#include <fmt/format.h>
#include <iostream>
#include <string_view>


void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void templates_and_friendship_01_demo()
{
  templates_and_friendship_01::Point p(1, 2);
  print_point(p);
}

void templates_and_friendship_02_demo()
{
  /*
  templates_and_friendship_02::Point p(3, 4);
  templates_and_friendship_02::print_point<double>(p);	//The template parameter
  could be anything here. It's not used anyway.

  templates_and_friendship_02::Canvas<int> canvas;
  canvas.draw(p);

  templates_and_friendship_02::Canvas<double> canvas2;
  canvas2.draw(p);
  */
}

void templates_and_friendship_03_demo()
{
  /*
  //Int instances of the friends.
  templates_and_friendship_03::Point p(5, 6);
  //templates_and_friendship_03::print_point<int>(p);	// print_point<int> can
  access the private members of Point<int>

  templates_and_friendship_03::Canvas<int> canvas; // If it was double, you'd
  get a compiler error. canvas.draw(p);	// Canvas<int> can access the private
  members of Point<int>
  */
}

void templates_and_friendship_04_demo()
{
  // templates_and_friendship_04::Point<int> p(7, 8);
  // print_point(p);	// print_point can access the private members of
  // Point<int>

  // templates_and_friendship_04::Point<double> p2(9.0, 10.0);
  // print_point(p2);	// print_point can't access the private members of
  // Point<double>
}

void templates_and_friendship_05_demo()
{
  /*
  templates_and_friendship_05::Point<int> p(11, 12);
  print_point(p);	// print_point can access the private members of
  Point<int>

  templates_and_friendship_05::Canvas<int> canvas;
  canvas.draw(p);	// Canvas<int> can access the private members of
  Point<int>
  */

  // Creating a Point<double> instance
  // templates_and_friendship_05::Point<double> p2(13.0, 14.0);
  // print_point(p2);	// print_point can't access the private members of
  // Point<double>
}

void templates_and_friendship_06_demo()
{
  /*
  templates_and_friendship_06::Point<int> p(15, 16);
  print_point(p);	// print_point can access the private members of
  Point<int>

  templates_and_friendship_06::Canvas<int> canvas;
  canvas.draw(p);	// Canvas<int> can access the private members of
  Point<int>
  */

  // Creating a Point<double> instance
  templates_and_friendship_06::Point<double> p2(17.0, 18.0);
  print_point(p2);

  templates_and_friendship_06::Canvas<double> canvas2;
  canvas2.draw(p2);
}

void templates_and_friendship_07_demo()
{
  templates_and_friendship_07::Point<int> p(19, 20);
  // print_point(p);	// print_point can access the private members of
  // Point<int>

  // templates_and_friendship_07::Canvas<int> canvas;
  // canvas.draw(p);	// Canvas<int> can access the private members of
  // Point<int>

  // Creating a Point<double> instance
  // templates_and_friendship_07::Point<double> p2(21.0, 22.0);
  // print_point<double>(p2);
  // print_point<int>(p2);	// Error

  // templates_and_friendship_07::Canvas<double> canvas2;
  // canvas2.draw(p2);
  // canvas2.draw(p);	// Error
}

void templates_and_friendship_08_demo()
{
  templates_and_friendship_08::BoxContainer<int> box_container;
  box_container.add(1);
  box_container.add(2);
  box_container.add(3);
  box_container.add(4);
  box_container.add(5);

  std::cout << box_container << '\n';
}