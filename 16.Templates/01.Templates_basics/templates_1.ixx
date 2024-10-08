/*
    . The basics of templates, starting with function templates.
        . Type Flexibility: Templates allow you to write generic code that works with any data type, making functions or classes reusable for different types (e.g., int, double, std::string).

        . Template Syntax: Declared using template <typename T>, where T is a placeholder for a type that will be determined when the template is used.

        . Function Templates: Functions like T add(T a, T b) can work with any type, as long as the type supports the operations used in the function (e.g., + for addition).

        . Class Templates: Similar to function templates but apply to entire classes, allowing you to create generic data structures, such as std::vector<T>.

        . Type Deduction: When calling a template function, the compiler automatically deduces the type based on the arguments passed, unless you specify it explicitly.

        . Constraints (C++20): Templates can be restricted to certain types using concepts to ensure that only types that meet specific requirements (e.g., std::is_integral) can be used.

        . Instantiation: Templates are not compiled until they are instantiated (i.e., when you use them with a specific type). This can lead to longer compile times if used extensively.
*/
module;

export module templates_1;

namespace templates_1{

    export template <typename T>
    T add(T a, T b) {
        return a + b;
    }

    export class Integer {
        friend Integer operator+ (const Integer& a, const Integer& b);
    public:
        explicit Integer(int i) : value(i) {}
        int get() const { return value; }

    private:
        int value;
    };

    export Integer operator+ (const Integer& a, const Integer& b) {
        return Integer(a.value + b.value);
    }

    export class Point {
        friend Point operator+ (const Point& a, const Point& b);
    public:
        Point(double x, double y) : x(x), y(y) {}
        double get_x() const { return x; }
        double get_y() const { return y; }
    private:
        double x, y;
    };

    export Point operator+ (const Point& a, const Point& b) {
        return Point(a.x + b.x, a.y + b.y);
    }
    
} // namespace templates_1