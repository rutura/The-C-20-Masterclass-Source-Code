module;

#include <fmt/format.h>

export module point;

// #7: Move constructors
/*
export class Point
{
private:
  double *x{};
  double *y{};

  void invalidate()
  {
    x = nullptr;
    y = nullptr;
  }

public:
  Point(double x_param, double y_param);
  ~Point();

  // Copy constructor
  Point(const Point &source_point);

  // Move constructor
  Point(Point &&source_point);


  // Setters
  void set_x(double x)
  {
    *(this->x) = x;// Dereference and assign
  }
  void set_y(double y)
  {
    *(this->y) = y;// Dereference and assign
  }

  // Getters
  double *get_x() const { return x; }

  double *get_y() const { return y; }

  double *steal_x()
  {
    double *new_x = x;
    x = nullptr;
    return new_x;
  }

  double *steal_y()
  {
    double *new_y = y;
    y = nullptr;
    return new_y;
  }

  // Utilities
  void print_info() const { fmt::println("Point [ x : {}, y: {}]", *x, (*y)); }
};


//Implementations
Point::Point(double x_param, double y_param) : x(new double(x_param)), y(new double(y_param))
{
  fmt::println("Point constructed  : {}", fmt::ptr(this));
}

// Copy constructor
Point::Point(const Point &source_point) : x(new double(*(source_point.get_x()))), y(new double(*(source_point.get_y())))
{
  fmt::println("Body of copy constructor");
}

// Move constructor
Point::Point(Point &&source_point) : x(source_point.steal_x()), y(source_point.steal_y())
{
  // source_point.invalidate();
  fmt::println("Body of move constructor");
}


Point::~Point()
{
  delete x;
  delete y;
}
*/


// #8: Deleted constructors
export class Point
{
private:
  double *x{};
  double *y{};

  void invalidate()
  {
    x = nullptr;
    y = nullptr;
  }

public:
  Point() = delete;
  Point(double x_param, double y_param);
  ~Point();
  // Copy constructor
  Point(const Point &source_point) = delete;

  // Move constructor
  Point(Point &&source_point) = delete;


  // Setters
  void set_x(double x)
  {
    *(this->x) = x;// Dereference and assign
  }
  void set_y(double y)
  {
    *(this->y) = y;// Dereference and assign
  }

  // Getters
  double *get_x() const { return x; }

  double *get_y() const { return y; }

  double *steal_x()
  {
    double *new_x = x;
    x = nullptr;
    return new_x;
  }

  double *steal_y()
  {
    double *new_y = y;
    y = nullptr;
    return new_y;
  }

  // Utilities
  void print_info() const { fmt::println("Point [ x : {}, y: {}]", *x, (*y)); }
};

//Implementations
Point::Point(double x_param, double y_param) : x(new double(x_param)), y(new double(y_param))
{
  fmt::println("Point constructed  : {}", fmt::ptr(this));
}
/*
//Copy constructor
Point::Point(const Point& source_point)
        : x(new double(*(source_point.get_x()))),
                y(new double(*(source_point.get_y())))
{
        fmt::println( "Body of copy constructor" );
}

//Move constructor
Point::Point( Point&& source_point)
        : x(source_point.steal_x()),
                y(source_point.steal_y())
{
    //source_point.invalidate();
        fmt::println( "Body of move constructor" );
}
*/


Point::~Point()
{
  delete x;
  delete y;
}