#include "animal.h"
#include "bird.h"
#include "cat.h"
#include "crow.h"
#include "dog.h"
#include "pigeon.h"
#include "stream_insertable.h"
#include <fmt/format.h>
#include <memory>

class Point : public StreamInsertable
{
public:
  Point() = default;
  Point(double x, double y) : m_x(x), m_y(y) {}

  virtual void stream_insert(std::ostream &out) const override { out << "Point [x: " << m_x << ",y: " << m_y << "]"; }
  void stream_insert(fmt::basic_memory_buffer<char> &out) const override
  {
    fmt::format_to_n(std::back_inserter(out), out.capacity(), "Point [x: {}, y: {}]", m_x, m_y);
  }

private:
  double m_x;
  double m_y;
};

template<typename T> std::string make_streamable(const T &obj)
{
  fmt::memory_buffer buf;
  obj.stream_insert(buf);
  return fmt::to_string(buf);
}


int main()
{

  Point p1(10, 20);
  fmt::println("p1 : {}", make_streamable(p1));
  // operator<<(std::cout,p1);

  fmt::println("------------");

  std::unique_ptr<Animal> animal0 = std::make_unique<Dog>("stripes", "dog1");
  fmt::println("{}", make_streamable(*animal0));

  std::unique_ptr<Animal> animal1 = std::make_unique<Bird>("white", "bird1");
  fmt::println("{}", make_streamable(*animal1));


  fmt::println("--------------");
  // Can even put animals in an array and print them polymorphically.
  std::shared_ptr<Animal> animals[]{ std::make_shared<Dog>("stripes", "dog2"),
    std::make_shared<Cat>("black stripes", "cat2"),
    std::make_shared<Crow>("black wings", "crow2"),
    std::make_shared<Pigeon>("white wings", "pigeon2") };
  fmt::println("Printing out animals array : ");
  for (const auto &a : animals) { fmt::println("{}", make_streamable(*a)); }

  return 0;
}