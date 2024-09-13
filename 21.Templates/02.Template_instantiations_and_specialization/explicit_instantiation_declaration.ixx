module;

export module explicit_instantiation_declaration;

namespace explicit_instantiation_declaration{

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

    //Explicit template instantiation declarations
    extern template int add<int>(int, int);
    extern template class Point<int>;

}   // namespace explicit_instantiation_declaration