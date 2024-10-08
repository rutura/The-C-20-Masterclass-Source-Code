/*
    . Exploring template parameter types: 
        . Type template parameters (typename or class):
            . These are the most common template parameters, used to specify a data type. You can 
                use either typename or class to define them.
            . Example: template <typename T> or template <class T> allows the template to accept any type T.

        . Non-type template parameters:
            . These allow you to pass values (such as constants, pointers, or references) as template arguments 
                instead of types.
            . The parameter must be a compile-time constant.
            . Example: template <int N> can accept an integer value as a parameter, useful for defining 
                things like array sizes.

        . Template template parameters (We'll see this later):
            . These allow templates to accept another template as a parameter.
            . Example: template <template <typename> class Container> allows you to pass a template 
                class (like std::vector) as an argument.

        . Auto template parameters (C++20, reserved for later):
            . C++20 introduced the ability to use auto for template parameters, where the type is deduced automatically.
*/
module;

export module templates_3;

namespace templates_3{

    //Type template parameters
    export template <typename T>
    class Point {
        T x, y;
    public:
        Point(T x, T y) : x(x), y(y) {}
        T get_x() const { return x; }
        T get_y() const { return y; }
        Point operator+(const Point& other) {
            return Point(x + other.x, y + other.y);
        }
    };

    export template <typename T>
    T maximum(T a, T b) {
        return a > b ? a : b;
    }

    //Can do defaults
    export template <typename T = int>
    T add(T a, T b){
        return a + b;
    }


    //Non-type template parameters
    export template <int N>
    class Array{
    private:
        int m_array[N];
    public:
        int get_size() const{
            return N;
        }
    };

}   // namespace templates_3