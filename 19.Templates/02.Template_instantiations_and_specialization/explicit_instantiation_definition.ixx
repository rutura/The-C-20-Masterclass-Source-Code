/*
    Explicit Instantiation Definition

        Explanation:
            . Explicit instantiation definition tells the compiler to generate a specific
                 version of a template at a particular point in the code. You do this to
                 control where the template code is instantiated, usually for optimization or to reduce code bloat.

        Why it's needed:
            . It helps manage compilation times and binary sizes. By explicitly instantiating templates in specific places, you can avoid multiple instantiations across different translation units. This can help reduce the size of the final binary and speed up compilation times.

        Syntax: 
            . Shown below in the explicit_instantiation_definition namespace.
*/
module;

export module explicit_instantiation_definition;

namespace explicit_instantiation_definition{

    export template<typename T>
    T add(T a, T b) {
        //T instance;
        //instance.hello();
        return a + b;
    }

    export template<typename T>
    class Point {
    public:
        Point(T x, T y) : x(x), y(y) {}
        T getX() const { return x; }
        T getY() const { return y; }

        //A compiler error will be thrown if the explicit instantiation definition is in place.
        //Because that forces the compiler to generate an complete int instance in this case.
        void error_function(){
            //T instance;
            //instance.some_function();
        }
    private:
        T x, y;
    };

    //Explicit template instantiation definitions
    //template int add<int>(int, int);
    //template class Point<int>;

}   // namespace explicit_instantiation_definition