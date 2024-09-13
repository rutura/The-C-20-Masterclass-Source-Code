/*
    This file contains code that tinkers with moving lvalues with std::move
*/
module;

#include <iostream>

export module move_semantics_05;

import boxcontainer;

namespace move_semantics_05{

    export void populate_box(box::BoxContainer<int>& box, int modifier){
        for(size_t i{0} ; i < 20 ; ++i){
            box.add((i+1)*modifier);
        }
    }

    //Copy version
    /*
    export template<class T>
    void swap_data(T& a, T& b) 
    { 
    T temp { a }; // invokes copy constructor
    a = b; // invokes copy assignment
    b = temp; // invokes copy assignment
    }
    */


    //Move version

    export template<class T>
    void swap_data(T& a, T& b) 
    { 
    T temp { std::move(a) }; // invokes Move constructor
    a = std::move(b); // invokes move assignment operator
    b = std::move(temp); // invokes move assignment operator
    }

}   // namespace move_semantics_05