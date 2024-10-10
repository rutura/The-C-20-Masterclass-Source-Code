/*
    .#3: Class is not a template, but the friend function and class are 
         specific specializations (or instances) of the template.
            . Specifically, friendship is only granted to int instances or specializations
                of the friend classes or functions.
            . print_point<double> and Canvas<double> cannot access the private 
                members of Point for example. 
*/
module;

#include <fmt/format.h>

export module templates_3;

namespace templates_3 {

    class Point;    //Forward declaration

    template  <typename T>
    void print_point(const Point& p);   //Forward declaration

    template <typename T>
    class Canvas;   //Forward declaration

    export class Point {
        //Only int instances of the friends have access to the private 
        //members of any instance of the Point class.
        friend void print_point<int>(const Point& p);
        friend class Canvas<int>;
    public:
        Point(int x, int y) : x(x), y(y) {}
    private: 
        int x;
        int y;
    };

    //Definition if print_point
    export template <typename T>
    void print_point(const Point& p) {
        fmt::print("Point: ({}, {})\n", p.x, p.y);
    }

    //Definition of Canvas
    export template <typename T>
    class Canvas {
    public:
        void draw(const Point& p) {
            fmt::print("Drawing point: ({}, {})\n", p.x, p.y);
        }
    };

    //Specializations
    /*
    template <>
    void print_point<int>(const Point& p) {
        fmt::println("Point - function specialization : ({}, {})\n", p.x, p.y);
    }

    
    template <>
    class Canvas<int> {
    public:
        void draw(const Point& p) {
            fmt::println("Drawing point - specialization: ({}, {})\n", p.x, p.y);
        }
    };
    */

    
}   // namespace templates_3 