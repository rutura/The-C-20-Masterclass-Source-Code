#include "stream_insertable.h"


std::ostream &operator<<(std::ostream &out, const StreamInsertable &operand)
{
  operand.stream_insert(out);
  return out;
}


void format_int_pointer_array(fmt::basic_memory_buffer<char> &out, int const *array, size_t size)
{
  // Begin formatting with opening square bracket
  format_to_n(std::back_inserter(out), 1, "[");

  // Iterate through each element in the array
  for (size_t i = 0; i < size; ++i) {
    // Format the current element and append it to the output buffer
    format_to_n(std::back_inserter(out), 1, "{}", (array[i]));

    // If it's not the last element, append a comma and space
    if (i < size - 1) {
      format_to_n(std::back_inserter(out), 1, ", ");
    }
  }

  // End formatting with closing square bracket
  format_to_n(std::back_inserter(out), 1, "]");
}
