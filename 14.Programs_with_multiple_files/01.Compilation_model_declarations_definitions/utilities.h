#pragma once

// Declaration
//double add(double a, double b);


// Declaration and definition
struct D_Vector
{
    double m_x;
    double m_y;
};

//Trigger ODR
/*
struct Point{

};
*/

double add(double a, double b);
void use_point();
void use_person();