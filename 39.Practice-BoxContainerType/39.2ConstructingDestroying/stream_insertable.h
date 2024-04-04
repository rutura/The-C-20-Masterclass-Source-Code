#ifndef STREAM_INSERTABLE_H
#define STREAM_INSERTABLE_H
#include <fmt/format.h>

class StreamInsertable
{
  friend std::ostream &operator<<(std::ostream &out, const StreamInsertable &operand);
  friend struct fmt::formatter<StreamInsertable>;

public:
  virtual void stream_insert(std::ostream &out) const = 0;
  virtual void stream_insert(fmt::basic_memory_buffer<char> &out) const = 0;
};
/**
 * @brief Specialization of the fmt::formatter struct for StreamInsertable types.
 *
 * This struct defines how StreamInsertable types are formatted using the fmt library.
 * It provides parsing and formatting functionality to generate a string representation
 * of the StreamInsertable object.
 */
template<> struct fmt::formatter<StreamInsertable>
{
  constexpr auto parse(format_parse_context &ctx) { return ctx.begin(); }

  template<typename FormatContext> auto format(const StreamInsertable &obj, FormatContext &ctx)
  {
    // Create a memory buffer to store the formatted string
    basic_memory_buffer<char> buf;

    // Insert the object's representation into the buffer
    obj.stream_insert(buf);

    // Format the buffer content into the output context
    return format_to(ctx.out(), "{}", buf);
  }
};

/**
 * @brief Generates a string representation of an object that supports stream insertion.
 *
 * This function generates a string representation of an object that supports stream insertion.
 *
 * @tparam T The type of the object.
 * @param obj The object to be converted into a string.
 * @return String representation of the object.
 */
template<typename T> std::string make_streamable(const T &obj)
{
  fmt::memory_buffer buf;
  obj.stream_insert(buf);
  return fmt::to_string(buf);
}

/**
 * @brief Formats an array of integer pointers into a string representation.
 *
 * @param out Reference to a fmt::basic_memory_buffer<char> where the formatted string will be stored.
 * @param array Pointer to the integer array to be formatted.
 * @param size Number of elements in the array.
 */
void format_int_pointer_array(fmt::basic_memory_buffer<char> &out, int const *array, size_t size);

#endif// STREAM_INSERTABLE_H