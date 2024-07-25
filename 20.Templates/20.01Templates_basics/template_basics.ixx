module;

export module template_basics;

namespace template_basics {

    export template <typename T>
    T add(T a, T b){
        return a + b;
    }

    export class  Integer{
        friend	Integer operator+ (const Integer a, const Integer b);
            int value;
        public: 
            explicit Integer(int const i): value(i) {}
            explicit operator int() const { return value;}
            int get() const { return value;}
    };

    export Integer operator+ ( Integer const a, Integer const b){
        return Integer(a.value + b.value);
    }

    //Create a Point class with with double coordinates. Add a + operator.
    export class Point{
        friend Point operator+ (const Point a,const Point b);
        double x;
        double y;
    public:
        Point(double x, double y): x(x), y(y) {}
        double get_x() const { return x;}
        double get_y() const { return y;}
    }; 
    export Point operator+ (const Point a,const Point b){
        return Point(a.x + b.x, a.y + b.y);
    }

}   // namespace template_basics