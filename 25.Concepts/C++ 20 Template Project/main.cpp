#include <iostream>
#include <concepts>
using namespace std;

template<typename T>
requires <std::integral T>
T maximum(T a, T b) {
    return a > b ? a : b;
}


int main(){
    int a{ 10 };
    int b{ 20 };
    auto max = maximum(a, b);
    cout << "Maximum:: " << max << endl;
    return 0;
}