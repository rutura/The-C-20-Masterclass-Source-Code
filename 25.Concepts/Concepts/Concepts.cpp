#include <iostream>
#include <concepts>
using namespace std;

template <typename T>
T add_up(const T collection[], unsigned int size)
    requires (std::is_integral_v<T> || std::is_floating_point_v<T>)
{
    T sum{};
    for (unsigned int i{ 0 }; i < size; ++i) {
        sum += collection[i];
    }
    return sum;
}

template<typename T>
requires std::integral <T>
T maximum(T a, T b) {
    return a > b ? a : b;
}


template<typename T>
concept isMultipliable = requires(T a, T b){
    a * b;
}

int main() {
    int a{ 10 };
    int b{ 20 };
    auto max = maximum(a, b);
    cout << "Maximum:: " << max << endl;

    float numbers1[]{ 10.2f, 11.8f };
    double numbers2[]{ 10.9999999999999999, 11.11111111111111111111 };
    char numbers3[]{ 'a', 'b' };
    int numbers4[]{ 10, 11 };
    auto result = add_up(numbers2, (unsigned int)size(numbers2));
    cout << "Result:: " << result << endl;
    return 0;
}