#pragma once

#include <string>

class Scores
{
public:
  Scores() = delete;
  Scores(const std::string &course_name);

  /*double& operator[](size_t index){
      assert((index >= 0) &&(index < 20));
      return m_scores[index];
  }

  double operator[](size_t index) const{
      assert((index >= 0) &&(index < 20));
      return m_scores[index];
  }*/

  double &operator[](size_t index);
  double operator[](size_t index) const;


  void print_info() const;

private:
  std::string m_course_name;
  double m_scores[20]{};
};
