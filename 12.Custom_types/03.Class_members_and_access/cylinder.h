#pragma once


class Cylinder {
    public :
        //Constctors
        Cylinder() = default;
    Cylinder(double rad_param,double height_param);
    //Functions (methods)
    double volume() const;

    //Setter and getter methods
    double get_base_radius() const{
        return base_radius;
    }
    double get_height() const {
        return height;
    }

    void set_base_radius(double rad_param);

    void set_height(double height_param);
    private :
        //Member variables
        double base_radius{1};
    double height{1};
};