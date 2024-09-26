/*
    . We are modeling a pixel that will live in a 2D space, that we will call a canvas.
    . We are going all basic here. Creating a class with everthing inside public.
        . we use the class keyword to define a class.
        . we can also use struct which makes everything inside public by default.
    . We create objects of the class and print the data inside.
    . Problems: 
        . The insides of our class are exposed to the outside world.
        . We need flexibility in creating objects: 
            . something like std::vector vec {1, 2, 3, 4, 5};
            . We do that through constructors. We look at those in ct2.ixx
*/
module;

#include <cstdint>

export module ct1;

namespace ct1{

    //export class Pixel {
    export struct Pixel {

        //public: 
            uint32_t m_color{0xFF000000};
            unsigned int pos_x{0};
            unsigned int pos_y{0};
    };

} // namespace ct1