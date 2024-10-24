/*
    . Private module fragment
*/
module;

export module more_on_modules_06;

namespace more_on_modules_06{

    export double add( double a, double b);

}   //namespace more_on_modules_06

module: private;

namespace more_on_modules_06{

    double add( double a, double b){
        return a + b;
    }

}   //namespace more_on_modules_06