#include <iostream>


template<typename T>
class TemplateClass; // forward declare to make function declaration possible
 
template<typename T>
void some_func( TemplateClass<T>); // declaration . Func is a template function because it has
						// template<typename T> in front of it, the compiler will
						// generate an instance for it with concrete types as template
						//arguments when needed.

template <typename T>
class TemplateClass{
    friend void some_func<T>(TemplateClass<T>  param);
public : 
     explicit TemplateClass<T>(){
      
     }
     void set_up(T param) {
         m_var = param;
     }
     void do_something(const T a, T b){
         std::cout << "Doing something with " << a << " and " << b << std::endl;
     }
private : 
     T m_var;
};

template <typename T>
void some_func(TemplateClass<T>  param){
    std::cout << "Inside some_func , accessing private data of TemplateClass : "
        << param.m_var << std::endl;
}


int main(){

	TemplateClass<int> object1;
    object1.set_up(10);
    
    TemplateClass<double> object2;
    object2.set_up(12.2);
    
    some_func(object1);
    some_func(object2);
    
    return 0;
}