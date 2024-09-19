#include <fmt/format.h>

namespace throwing_std_exceptions {

class Students
{
public:
  Students() = delete;

  Students(std::string_view s1, std::string_view s2, std::string_view s3, std::string_view s4, std::string_view s5)
  {
    m_students[0] = s1;
    m_students[1] = s2;
    m_students[2] = s3;
    m_students[3] = s4;
    m_students[4] = s5;
  }

  ~Students() = default;

  std::string_view get_student(size_t index)
  {
    const std::string message = "Index out of range, valid range[" + std::to_string(0) + "," + std::to_string(4) + "]";

    if ((index < 0) || (index >= 5)) throw std::out_of_range(message);
    return m_students[index];
  }

private:
  std::string m_students[5];
};

}// namespace throwing_std_exceptions