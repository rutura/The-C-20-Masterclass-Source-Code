module;

export module cylinder;

namespace Geom {

export class Cylinder
{
public:
  Cylinder(double base_rad, double height);

  double volume() const { return PI * m_base_rad * m_base_rad * m_height; }

private:
  inline static const double PI{ 3.1415926535897932384626433832795 };
  double m_base_rad{ 1 };
  double m_height{ 1 };
};

}// namespace Geom

//Implementations
namespace Geom {

Cylinder::Cylinder(double base_rad, double height) : m_base_rad{ base_rad }, m_height{ height } {}

}// namespace Geom