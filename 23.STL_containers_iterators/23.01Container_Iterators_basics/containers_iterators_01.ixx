/*
    This file contains code that tinkers with std::vector and std::array.
*/
module;

#include <vector>
#include <array>
#include <fmt/format.h>

export module containers_iterators_01;

namespace containers_iterators_01{


    //Vector manipulation
    template<typename T>
     void print_vec(const std::vector<T> &vec)
    {
    for (size_t i{}; i < vec.size(); ++i) {
        fmt::print("{} ", vec[i]);
        ;
    }
    fmt::println("");
    }

    template<typename T> void print_raw_array(const T *p, std::size_t size)
    {
    fmt::print("data = ");
    for (std::size_t i = 0; i < size; ++i) fmt::print("{} ", p[i]);
    fmt::println("");
    }


    //Array manipulation
    template<typename T, size_t Size>// The second template argument has to be a size.
    void print_array(const std::array<T, Size> &arr)
    {
    for (size_t i{}; i < arr.size(); ++i) { fmt::print("{}", arr[i]); }
    fmt::println("");
    }

    export void use_vector(){

        // Constructing vectors
        std::vector<std::string> vec_str{ "The", "sky", "is", "blue", "my", "friend" };
        fmt::println("vec1[1]  : {}", vec_str[1]);
        print_vec(vec_str);

        fmt::println("------");

        std::vector<int> ints1;
        fmt::print("ints1 : ");
        print_vec(ints1);// Won't print anything, the vector has no content

        std::vector<int> ints2 = { 1, 2, 3, 4 };
        std::vector<int> ints3{ 11, 22, 33, 44 };

        fmt::print("ints2 : ");
        print_vec(ints2);

        fmt::print("ints3 : ");
        print_vec(ints3);


        std::vector<int> ints4(20, 55);// A vector with 20 items, all initialized to 55
        fmt::print("ints4 : ");
        print_vec(ints4);

        // Be careful about uniform initialization
        std::vector<int> ints5{ 20, 55 };// A vector with 2 items : 20 and 55
        fmt::print("ints5 : ");
        print_vec(ints5);


        // Accessing elements
        fmt::println("Accessing elements in a vector: ");
        fmt::println("vec_str[2] : {}", vec_str[2]);
        fmt::println("vec_str.at(3) : {}", vec_str.at(3));
        fmt::println("vec_str.front() : {}", vec_str.front());
        fmt::println("vec_str.back() : {}", vec_str.back());

        // Using the data method
        fmt::println("using raw array : ");
        print_raw_array(vec_str.data(), vec_str.size());


        // Adding and removing stuff
        fmt::println("Adding and removing stuff : ");

        fmt::print("ints1 : ");
        print_vec(ints1);


        // Pushing back
        ints1.push_back(100);
        ints1.push_back(200);
        ints1.push_back(300);
        ints1.push_back(500);
        fmt::print("ints1 : ");
        print_vec(ints1);

        // Poping back
        ints1.pop_back();
        fmt::print("ints1 : ");
        print_vec(ints1);

    }


    export void use_array(){

        std::array<int, 3> int_array1;// Will contain junk by default
        std::array<int, 3> int_array2{ 1, 2 };// Will contain 1,2,0
        std::array<int, 3> int_array3{};// Will contain 0 0 0
        std::array int_array4{ 1, 2 };// Compiler will deduce std::array<int,2>
        // std::array<int, 3> int_array5{1,2,3,4,5}; // Compiler error : More than enough elements
        // Can deduce the type with auto.

        fmt::print("int_array1 : ");
        print_array(int_array1);

        fmt::print("int_array2 : ");
        print_array(int_array2);

        fmt::print("int_array3 : ");
        print_array(int_array3);

        fmt::print("int_array4 : ");
        print_array(int_array4);



        // Adding and removing stuff
        // Can't really add stuff. Can specify content at initialization
        // Can also fill the entire array with an element
        fmt::println("");
        fmt::println("Filling the array : ");
        int_array1.fill(321);
        int_array4.fill(500);
        fmt::print("int_array1 : ");
        print_array(int_array1);
        fmt::print("int_array4 : ");
        print_array(int_array4);


        // Accessing elements
        fmt::println("");
        fmt::print("Accessing elements in an array: ");
        fmt::println("int_array2[0] : {}", int_array2[0]);
        fmt::println("int_array2.at(1) : {}", int_array2.at(1));
        fmt::println("int_array2.front() : {}", int_array2.front());
        fmt::println("int_array2.back() : {}", int_array2.back());
        // data method
        print_raw_array(int_array2.data(), int_array2.size());

    }


}   // namespace containers_iterators_01