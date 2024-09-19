#pragma once

namespace Geom {

class Point
{
  public:
    Point();
    Point(double x, double y);
    void print_info() const;
    ~Point();

  private:
    double m_x;
    double m_y;
};

}// namespace Geom