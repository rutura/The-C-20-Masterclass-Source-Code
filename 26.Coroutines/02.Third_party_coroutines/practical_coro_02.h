/*
    . std::generator is only implemented by gcc 14 at the time of this writting.
    . Try it out in compiler explorer: https://godbolt.org/z/jac1dW9bq
*/
#pragma once

#include <iostream>
//#include <generator>  //Currently only works in gcc 14
namespace practical_coro_02{

    /*
    std::generator<int> fibonacci(int max) {
        int a = 0, b = 1;
        while (a <= max) {
            co_yield a;
            int temp = a;
            a = b;
            b = temp + b;
        }
    }
    */


}   //namespace practical_coro_02.