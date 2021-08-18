#include <iostream>
#include <cmath>


//Valid comparable points are within the [100,100] bounds
class Point{
    public : 
        Point (int x, int y) 
            : m_x{x}, m_y{y}
            {}
        bool operator==(const Point& right) const{
			return length() == right.length();
		}
        std::partial_ordering operator<=>(const Point& right) const {
            if(is_within_bounds(*this) && is_within_bounds(right)){
                if(length() > right.length())
                    return std::partial_ordering::greater;
                else if(length() < right.length())
                    return std::partial_ordering::less;
                else    
                    return std::partial_ordering::equivalent;
            }
            return std::partial_ordering::unordered;
        }
    private :
        bool is_within_bounds(const Point& p) const{
            if((std::abs(p.m_x) < 100) && (std::abs(p.m_y) < 100))
                return true;
            return false;
        }
        double length() const{
            return sqrt(pow(m_x - 0, 2) +  pow(m_y - 0, 2) * 1.0); 
        }
        int m_x{};
        int m_y{}; 
};




int main(){

    Point p1(110,110);
    Point p2(20,20);

    std::cout << std::boolalpha;
    auto result1 = (p1 > p2);
    std::cout << "p1 > p2 : " << result1 << std::endl;

    auto result2 = (p1 >= p2);
    std::cout << "p1 >= p2 : " << result2 << std::endl;

    auto result3 = (p1 == p2);
    std::cout << "p1 == p2 : " << result3 << std::endl;

    auto result4 = (p1 != p2);
    std::cout << "p1 != p2 : " << result4 << std::endl;

    auto result5 = (p1 < p2);
    std::cout << "p1 < p2 : " << result5 << std::endl;

    auto result6 = (p1 <= p2);
    std::cout << "p1 <= p2 : " << result6 << std::endl;
    
    return 0;
}