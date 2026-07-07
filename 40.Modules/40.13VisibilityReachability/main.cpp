import <iostream>;
import math;

int main()
{
    //Point is not visible. We can't create its instance
    //math::Point p(1, 2);

    auto p = math::generateRandomPoint();
    //print p
    std::cout << p << std::endl;
    std::cout << "x: " << p.getX() << std::endl;
}