#pragma once

#include <fmt/format.h>
#include <iostream>

namespace iteration_1 {

class StreamInsertable
{
  friend std::ostream &operator<<(std::ostream &out, const StreamInsertable &operand);

public :
  virtual ~StreamInsertable() = default;
  virtual void stream_insert(std::ostream &out) const =0;
};

//Implementation
inline std::ostream &operator<<(std::ostream &out, const StreamInsertable &operand)
{
  operand.stream_insert(out);
  return out;
}
}// namespace iteration_1