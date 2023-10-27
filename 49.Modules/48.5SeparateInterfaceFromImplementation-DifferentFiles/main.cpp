import <iostream>;
import math_stuff;

int main()
{
    auto result = add(10, 20);
    std::cout << "result : " << result << std::endl;

    greet("John");

    print_name_length("John");

    Point point1(22, 44);
    std::cout << "point1 : " << point1 << std::endl;
}