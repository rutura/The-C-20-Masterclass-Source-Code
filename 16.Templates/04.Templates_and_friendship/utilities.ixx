module;

#include <fmt/format.h>

#include <iostream>
#include <string_view>

export module utilities;

import templates_1;
import templates_2;
import templates_3;
import templates_4;
import templates_5;
import templates_6;
import templates_7;

//IMPORTANT NOTE: Code from this chapter prioritized compilation on Windows with Visual C++.
//                Some parts couldn't compile on Clang. Test each part incrementally.
//                May be it has to do with C++20 modules? 


//#1: Friendship without templates
export void templates_1_demo() {
  templates_1::Point p(1, 2);
  print_point(p);
}

//#2: The class is not a template, but the friend function and class are templates.
export void templates_2_demo() {

    using templates_2::Point;
    using templates_2::Canvas;
    using templates_2::print_point;

    Point p1(3, 4);
    Canvas<int> canvas1;
    canvas1.draw(p1);
    print_point<int>(p1);

    Point p2(5, 7);
    Canvas<float> canvas2;
    canvas2.draw(p2); // Canvas<float> can access the private members of Point.
    print_point<float>(p2);
    print_point<float>(p1); // A float instance of print_point can access the private members of Point.

}

//#3: The class is not a template, but the friend function and 
//   class are specific specializations of the template.
export void templates_3_demo() {
    //Int instances of the friends.
    templates_3::Point p(5, 6);

    //print_point<int> can access the private members of Point<int>.
    //If it was double, you'd get a compiler error.Canvas<int> can access the private
    templates_3::print_point<int>(p);	

    //The same goes for the Canvas class template.
    templates_3::Canvas<int> canvas; 
    canvas.draw(p);
}

//#4: Class is a template, and the friend function is not a template.
//     . Granting access to a limited set of function overloads.
export void templates_4_demo() {
  templates_4::Point<int> p(7, 8);
  print_point(p);	// print_point can access the private members of Point<int>

  templates_4::Point<double> p2(9.0, 10.0);
  //print_point(p2);	// Error. Why?  
}

//#5: The class is a template, friend functions and classes are templates, but
// only a int instances of the friends have access to the private members.
export void templates_5_demo() {

  templates_5::Point<int> p(11, 12);
  print_point(p);	// print_point can access the private members of Point<int>

  templates_5::Canvas<int> canvas;
  canvas.draw(p);	// Canvas<int> can access the private members of Point<int>

  // Creating a Point<double> instance
  templates_5::Point<double> p2(13.0, 14.0);
  //print_point(p2);	// Error: print_point can't access the private members of // Point<double>
}


//#6: Class is template, friends are template, and we want any instance 
//    of the friend templates to have access to private members of the class.
export void templates_6_demo() {
  templates_6::Point<int> p(15, 16);
  print_point(p);	// print_point can access the private members of Point<int>

  templates_6::Canvas<int> canvas;
  canvas.draw(p);	// Canvas<int> can access the private members of Point<int>

  // Creating a Point<double> instance
  templates_6::Point<double> p2(17.0, 18.0);
  print_point(p2);

  templates_6::Canvas<double> canvas2;
  canvas2.draw(p2);
}


//#7: Class is a template, friends are templates, and we only want friends 
// whose template paramter matches that  of the class to have access to 
// the private members of the class.
export void templates_7_demo() {
  templates_7::Point<int> p(19, 20);
  print_point(p);	// print_point can access the private members of Point<int>

  templates_7::Canvas<int> canvas;
  canvas.draw(p);	// Canvas<int> can access the private members of Point<int>

  //Creating a Point<double> instance
  templates_7::Point<double> p2(21.0, 22.0);
  print_point<double>(p2);
  //print_point<int>(p2);	// Error

  templates_7::Canvas<double> canvas2;
  canvas2.draw(p2);
  //canvas2.draw(p);	// Error
}