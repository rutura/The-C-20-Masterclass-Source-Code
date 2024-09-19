#pragma once

const double PI{3.1415926535897932384626433832795};

class Cylinder
{
public :
    //Constctors
    Cylinder() = default;
    Cylinder(double rad_param, double height_param);
    //Functions (methods)
    [[nodiscard]] double volume() const;

    //Setter and getter methods
    [[nodiscard]] double get_base_radius() const;
    [[nodiscard]] double get_height() const;

    void set_base_radius(double rad_param);

    void set_height(double height_param);

private :
    //Member variables
    double base_radius{1};
    double height{1};
};
