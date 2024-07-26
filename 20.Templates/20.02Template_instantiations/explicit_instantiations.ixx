module;

#include <fmt/format.h>
#include <cmath>

export module explicit_instantiations;

namespace explicit_instantiations{

    //The Point class
    export template <typename T>
    class Point {
        // The <> is necessary to specify that the operator+ is a template function. 
        // Without it, the compiler cannot correctly instantiate or resolve the template function. 
        // When declaring a friend function in a class template, 
        // you must specify that the friend function is a template. 
        // The angle brackets <> are used to indicate this, 
        // allowing the compiler to understand that operator+ is a 
        // template function that will work with different types T.
        friend Point operator+<>(const Point& lhs, const Point& rhs);
        T x, y;
    public:
        // Constructor
        Point(T x = 0, T y = 0) : x(x), y(y) {}

        // Member function to compute the distance from the origin
        double distanceFromOrigin() const {
            return std::sqrt(static_cast<double>(x * x + y * y));
        }

        double error_function(){
            T instance;
            instance.do_something();
            return 0.0;
        }
    };

    // Overloaded + operator
    export template <typename T>
    Point<T> operator+(const Point<T>& lhs, const Point<T>& rhs) {
        return Point<T>(lhs.x + rhs.x, lhs.y + rhs.y);
    }

}   // namespace explicit_instantiations