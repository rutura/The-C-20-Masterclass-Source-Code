
#pragma once
#include <utility>

namespace csv2 {

namespace trim_policy {
struct no_trimming {
public:
  static std::pair<size_t, size_t> trim(const char *buffer, size_t start, size_t end) {
    (void)(buffer); // to silence unused parameter warning
    return {start, end};
  }
};

template <char... character_list> struct trim_characters {
private:
  constexpr static bool is_trim_char(char) { return false; }

  template <class... Tail> constexpr static bool is_trim_char(char c, char head, Tail... tail) {
    return c == head || is_trim_char(c, tail...);
  }

public:
  static std::pair<size_t, size_t> trim(const char *buffer, size_t start, size_t end) {
    size_t new_start = start, new_end = end;
    while (new_start != new_end && is_trim_char(buffer[new_start], character_list...))
      ++new_start;
    while (new_start != new_end && is_trim_char(buffer[new_end - 1], character_list...))
      --new_end;
    return {new_start, new_end};
  }
};

using trim_whitespace = trim_characters<' ', '\t'>;
} // namespace trim_policy

template <char character> struct delimiter {
  constexpr static char value = character;
};

template <char character> struct quote_character {
  constexpr static char value = character;
};

template <bool flag> struct first_row_is_header {
  constexpr static bool value = flag;
};

}