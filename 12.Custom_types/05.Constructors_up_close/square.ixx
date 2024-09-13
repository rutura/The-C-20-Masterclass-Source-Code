module;

#include <string>

export module square;


// #3: Explicit constructors

/*
export class Square
{
public:
  explicit Square(double side_param, const std::string &color_param = "black");
  ~Square();
  double surface() const;

private:
  double m_side;
  std::string m_color;
};
*/

// #4: Constructor delegation
export class Square
{
public:
  explicit Square(double side_param);
  Square(double side_param, const std::string &color_param, int shading_param);
  ~Square();
  double surface() const;

private:
  double m_side;
  std::string m_color;
  int m_shading;
  double m_position;
};