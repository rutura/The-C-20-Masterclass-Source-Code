#include <iostream>

const double adjustment {0.7234};

namespace Math{
    double add(double a, double b){
        std::cout << "Math::add" << std::endl;
        return a + b;
    }
    double sub(double a, double b){
        std::cout << "Math::sub" << std::endl;
        return a - b;
    }
    double mult(double a, double b){
        std::cout << "Math::mult" << std::endl;
        return a * b ;
    }
    double div(double a, double b){
        std::cout << "Math::div" << std::endl;
        return a / b;
    }
    
}

namespace Math_Weighted{
    double add(double a, double b){
        std::cout << "Math_Weighted::add" << std::endl;
        return a + b - adjustment;
    }
    double sub(double a, double b){
        std::cout << "Math_Weighted::sub" << std::endl;
        return a - b - adjustment;
    }
    double mult(double a, double b){
        std::cout << "Math_Weighted::mult" << std::endl;
        return a * b - adjustment;
    }
    double div(double a, double b){
        std::cout << "Math_Weighted::div" << std::endl;
        return a / b - adjustment;
    }
}