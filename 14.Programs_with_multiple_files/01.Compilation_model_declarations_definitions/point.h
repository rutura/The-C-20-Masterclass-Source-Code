#pragma once

class Point {
private:
    double x;
    double y;

public:
    // Constructors
    Point();  // Default constructor
    Point(double x, double y);  // Parameterized constructor

    // Destructor (not strictly necessary for this simple class)
    ~Point();

    // Accessors
    double get_x() const;
    double get_y() const;

    // Mutators
    void set_x(double x);
    void set_y(double y);

    // Distance
    double distance_from_origin()const;
};
