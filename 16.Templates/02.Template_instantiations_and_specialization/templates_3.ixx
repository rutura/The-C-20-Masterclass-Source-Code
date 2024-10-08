/*
    . Exploring explicit template instantiation declarations: 
        . You use syntaxes like shown below to tell the compiler that an instantiation of the 
            template will be provided elsewhere in the project.: 
                . `extern template int add<int>(int, int)`;
                . `extern template class Point<int>`;
        . In our case, we put these declarations in the template_3 module interface file
        . The definitions show up in the template_3.cpp file.
        . The compiler will not instantiate the template in the template_3 module interface file.
            . This reduces compilation times, binary sizes, and helps avoid multiple instantiations across different translation units.
        . Places where you can put the instantiation definition
            . Inside the module interface file at the bottom: like templates_3.ixx at the bottom.
            . Inside a module implementation file. like templates_3.cpp

        . DEAL BREAKER: 
            . I couldn't get this to work with Visual C++.
            . But it works with Clang18. Whuaaaa!
*/
module;

export module templates_3;

namespace templates_3{

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

    //Explicit template instantiation declarations. These are declarations, only 
    //hinting to the fact that the definitions will be provided elsewhere.
    //the extern keyword makes all the difference here.
    extern template int add<int>(int, int);
    extern template class Point<int>;
    
} // namespace templates_3


/*
namespace templates_3{
    //Explicit template instantiation definitions
    template int add<int>(int, int);
    template class Point<int>;
    
} // namespace templates_3
*/