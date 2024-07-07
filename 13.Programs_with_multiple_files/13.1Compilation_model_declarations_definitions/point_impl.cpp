module;

#include <cmath>

module point;

// Default constructor
Point::Point() : x(0.0), y(0.0) {}

// Parameterized constructor
Point::Point(double x, double y) : x(x), y(y) {}

// Destructor (not strictly necessary for this simple class)
Point::~Point() {}

// Accessors
double Point::get_x() const {
    return x;
}

double Point::get_y() const {
    return y;
}

// Mutators
void Point::set_x(double x) {
    this->x = x;
}

void Point::set_y(double y) {
    this->y = y;
}


double Point::distance_from_origin()const{
    return std::sqrt(x*x + y*y);
}