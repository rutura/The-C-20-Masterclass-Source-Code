/*
          .#3: example 1
            . see class_templates_concepts_03.ixx  
*/
module;


#include <iostream>
#include <vector>

export module class_templates_concepts_03;


namespace class_templates_concepts_03{

    // Define the OutputStreamable concept
    export template <typename T>
    concept OutputStreamable = requires(std::ostream& o, T d) {
        o << d;
    };

    // Define the Point class as a template
    export template <OutputStreamable T>
    struct Point {
        T mx; // Use template type T for x coordinate
        T my; // Use template type T for y coordinate

        // Friend function to overload the output operator for Point
        friend std::ostream& operator<<(std::ostream& o, const Point<T>& p) {
            o << "Point [ x : " << p.mx << ", y : " << p.my << "]";
            return o;
        }
    };

}   // namespace class_templates_concepts_03