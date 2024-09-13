/*
    . Function overloading: 
    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Can also use presets on the command line.
    . Dependencies: 
        . gcc 14 or up (can be official container)
        . cmake 3.29 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

// One line comment
#include <fmt/format.h>
import utilities;

int main() {

    //Overloading with different parameters
    /*
    max(1, 2);
    max(1.0, 2.0);
    max(1, 2.0);
    max(1.0, 2);
    max(1.0, 2, 3);
    max("hello", "world");
    */

    //Overloading with pointer parameters
    /*
    double doubles[]{ 10.0, 30.0, 12.3 };
    int ints[]{ 1, 2, 5, 2, 8, 4 };

    //auto result = max(ints, std::size(ints));
    auto result = max(doubles, std::size(doubles));
    fmt::println("result : {}", result);
    */

    //Overloading with reference parameters
    /*
    char a{ 6 };
    char b{ 9 };

    auto result = max(a, b);
    fmt::println("result : {}", result);
    */


    //Overloading with const parameters
    /*
    int a{ 6 };
    int b{ 9 };

    auto result = max(a, b);
    fmt::println("result : {}", result);
    */


    //Overloading with const pointer and pointer to const parameters
    /*
    // int a{10};
    // int b{12};

    // const int c{30};
    // const int d{15};

    // auto result = max(&c,&c);
        

    const int c{ 30 };
    const int d{ 15 };

    const int *p_c{ &c };
    const int *p_d{ &d };

    fmt::println("&p_c : {}", fmt::ptr(&p_c));
    fmt::println("&p_d : {}", fmt::ptr(&p_d));

    auto result = min(p_c, p_d);
    */


    //Overloading with const reference parameters
    /*
    int a{ 45 };
    int b{ 85 };

    int max1 = max(a, b);
    fmt::println("max1 : ", max1);

    const int &ref_a = a;
    const int &ref_b = b;

    int max2 = max(ref_a, ref_b);
    fmt::println("max2 : ", max2);
    */


    //Overloading with default parameters
    print_age();


}