/*
            . Exploring the basics of class templates: 
        . Templates, (class templates in this example), allow generic programming: The Point class 
            is a template class that can work with any data type T (e.g., int, float, double) as 
            long as the type supports the required operations (in this case, the + operator for the 
            x and y coordinates).

        . Template parameter usage: In the declaration template <typename T>, the T is a placeholder 
            for a type that will be specified when creating an object of the Point class. This makes 
            the class flexible and reusable for different types.
*/
module;

export module templates_2;

namespace templates_2{

    //The requirement is that the type T must support the + operator.
    //The types of the coordinates also must be the same.
    export template <typename T>
    class Point{
        friend Point operator+ (const Point a,const Point b){
            return Point(a.x + b.x, a.y + b.y);
        }
    public:
        Point(T x, T y): x(x), y(y) {}
        T get_x() const { return x;}
        T get_y() const { return y;}
    private:
        T x;
        T y;
    };
    
} // namespace templates_2