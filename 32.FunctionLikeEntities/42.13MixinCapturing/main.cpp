#include <iostream>



int main(){

    int a{10};
    int b{11};
    int c{12};
    int d{13};
    
    //Code1 : Mix by value and by ref
    auto func1 = [a,&b] (int x, int y){
        
    };

    //Code2 : All by value, a by reference
    auto func2 = [=,&a] (int x, int y){
        
    };

    //Code3 : All by reference, a by value
    auto func3 = [&,a] (int x, int y){
        
    };

    //Code4 : capture all = and & must always  come first
    /*
    auto func4 = [a,b,&] (int x, int y){ // Compiler Error
        
    };
    */

    //Code5 : capture all = and & must always  come first
    /*
    auto func5 = [a,b,=] (int x, int y){ // Compiler Error
        
    };
    */


    //Code6 : Can't prefix vars captured  by value with =
    /*
    auto func6 = [=a,=b] (int x, int y){ // Compiler Error
        
    };
    */


    //Code7 : If you use =, you're no longer allowed to capture any other variable
    //by value, similarly, if you use & , you can't capture any other variable
    // by reference. Some compilers may give a warning, others an error.
    
    /*
    auto func7 = [=,&b,c] (int x, int y){ // Compiler Error/Warning
        
    };
   
    auto func8 = [&,b,&c] (int x, int y){ // Compiler Error/Warning
        
    };
    */

   
    return 0;
}