module;

#include <iostream>

export module ranges_library_03;

namespace ranges_library_03{


    export class Point
    {
        friend std::ostream& operator<< (std::ostream& out , const Point& p);
    public:
        Point() = default;
        Point(double x, double y) : 
            m_x(x), m_y(y){
        }
        //Operators
        bool operator==(const Point& other) const;
        std::partial_ordering operator<=>(const Point& right) const;

    private: 
        double length() const;   // Function to calculate distance from the point(0,0)

    public : 
        double m_x{};
        double m_y{};
    };

    export inline std::ostream& operator<< (std::ostream& out , const Point& p){
        out << "Point [ x : " << p.m_x << ", y : " << p.m_y <<
            " , length : " << p.length()    << " ]" ;
        return out;
    }

    //Implementations
    double Point::length() const{
        return sqrt(pow(m_x - 0, 2) +  pow(m_y - 0, 2) * 1.0); 
    }

    bool Point::operator==(const Point& other) const{
        return (this->length() == other.length());
    }

    std::partial_ordering Point::operator<=>(const Point& right) const{
        if(length() > right.length())
            return std::partial_ordering::greater;
        else if(length() == right.length())
            return std::partial_ordering::equivalent;
        else if(length() < right.length())
            return std::partial_ordering::less;
        else
            return std::partial_ordering::unordered;
    }

    export template<typename T>
    void print_collection( const T& collection){
        
        std::cout << " Collection [" ;
        for(const auto& elt : collection){
            std::cout << " " << elt ;
        }
        std::cout << "]" << std::endl;
    }


}   // namespace ranges_library_03