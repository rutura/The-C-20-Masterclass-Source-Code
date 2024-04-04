/*
    . This example shows the usage of namespaces with modules
    . If you export a namespace, everything inside it is exported.
    . If you export something from a namespace, the namespace is exported. But not everything inside it. A good example is the add function in our module.
*/
#include <fmt/format.h>
// import <iostream>;
import math;

int main()
{
    math::Point  p1(1, 2);
    math::Point p2(3, 4);
    math::Line l1(p1, p2);
    fmt::println("{}", l1);
    // std::cout << l1 << std::endl;

    //Print the distance between p1 and p2
    fmt::println("Distance between {} and {} is {}", p1,  p2 , math::distance(p1, p2) );
    /*std::cout << "Distance between " << p1 << " and " << p2 << " is "
        << math::distance(p1, p2) << std::endl;*/

    //Print the sum of p1 and p2.Error: add is not exported
    // fmt::println("Sum of {} and {} is {}",  p1 ,  p2 , math::add(p1, p2));
    //std::cout << "Sum of " << p1 << " and " << p2 << " is " << math::add(p1, p2) << std::endl;
}
