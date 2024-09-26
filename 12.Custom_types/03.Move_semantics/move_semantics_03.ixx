/*
    This file contains code that tinkers with moving temporaries around.
        . The canvas class with move semantics added.
        . Step through these demos with a debugger to see how these 
            constructors and assignment operators are used.

        . Copy elision for returned objects from functions. Consider the 
            returning_objects_with_move_semantics() funtion below.
            . In C++17, if possible, the compiler will elide the copy/move
                constructor and directly construct the object in the caller's
                scope. This improves performance. But elision is not guaranteed always. 
                Here are the rules: 

                    . If a nameless temporary object is returned, elision will kick in and 
                        the copy/move operations will be completely bypassed. The copy and move
                        contructors still need to be there though. This ellision is guaranteed by the 
                        C++17 standard.

                    . If a local named object (must not be a parameter), is returned, ellision
                        may kick in but, it's not guaranteed. Some compilers only do this in release builds.
                         This is known as the named return value optimization. 
                        If ellision is not possible, normal copy/move operations will take place.

                    . You can use std::move to disable ellision. In this case, normal copy/move operations will take place.

                    . Compared to NRVO, falling back to move semantics has a small performance impact, 
                        but falling back to copy semantics can have a big performance impact! So, when returning 
                        a local variable or a nameless temporary from a function, write return object and do not 
                        use std::move.

        . Passing arguments to functions. Case in point: The Scores class
            . We only have the set_scores function taking a vector by const reference. 
                . void set_scores(const std::vector<int>& scores)
                . the data is copied.
            . You might want to improve on this and add an overload that takes an rvalue reference.
                . void set_scores(std::vector<int>&& scores)
                . when set_scores is called with an rvalue, the data is moved, no copies are made.

            . Having to set up two overloads that almost look the same is a bit of a hassle. We can
                avoid these by just setting up one function that takes the vector by value. This way,
                the function can be called with both lvalues and rvalues. If an lvalue is passed in,
                it’s copied exactly one time, just as with a reference-to-const parameter. And,
                if an rvalue is passed in, no copy is made, just as with an rvalue reference parameter.

            . This pass by value recommendation is only valid for parameters that are copied anyway,
                 just like the scores vector. For all other cases, it's still recommended to use const references. 
                 Another case where this wouldn't work is where polymorphism is involved, because passing by value
                 causes a phenomenon known as slicing. We'll learn about that later.

            . Use the example code in the modern namespace inside the canvas module to show an example of the 
                rule of 0.

            . There is another rule, called the rule of file, that states that if you declare any of the 5 special
                member functions, you should declare all 5. The 5 special member functions are:
                    . Destructor
                    . Copy constructor
                    . Copy assignment operator
                    . Move constructor
                    . Move assignment operator

            . The rule of five should be limited to custom resource acquisition is 
                initialization (RAII) classes. An
                RAII class takes ownership of a resource and handles its deallocation at the right time.
*/
module;

#include <fmt/format.h>
#include <vector>

export module move_semantics_03;

import canvas;


namespace move_semantics_03{

    export class Scores{

        public: 

            //Two overlads
            /*
            void set_scores(const std::vector<int>& scores){
                m_scores = scores;
            }
            void set_scores(std::vector<int>&& scores){
                m_scores = std::move(scores);
            }
            */

            //One function taing the vector by value
            void set_scores(std::vector<int> scores){
                m_scores = std::move(scores);
            }

        private:
            std::vector<int> m_scores;
    };

    raw::Canvas make_canvas(std::size_t width, std::size_t height){
        return raw::Canvas(width, height);
    }

    export void canvas_move_semantics_demo_1(){
        std::vector<raw::Canvas> canvases;
        canvases.reserve(3);    // This reserves the capacity, not the size.

        for(size_t i{0} ; i < 3 ; ++i){
            fmt::println("Iteration: {}", i);
            canvases.push_back(make_canvas(10,10));
            fmt::println("");
        }   
    }

    export void canvas_move_semantics_demo_2(){
        raw::Canvas c(10,10);
        c = make_canvas(20,20);

        raw::Canvas c2 (30,30);
        c = c2;
        fmt::println("All done.");
    }

    export raw::Canvas returning_objects_with_move_semantics(){

        //1. Mandatory Copy/Move Ellision C++17
        /*
        return raw::Canvas{10,10}; // nameless temporary returned: Mandatory Copy/Move Elision (C++17)
        */

        //2. Non mandatory Copy/Move Ellision: Named return value optimization
        /*
        raw::Canvas c1{10,10};
        return c1;
        */

        //3. std::move and its effects on return statements
        raw::Canvas c2{10,10};
        return std::move(c2);
    }

}  // namespace move_semantics_03