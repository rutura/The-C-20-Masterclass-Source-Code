#include "boxcontainer.h"

template<> const char *BoxContainer<const char *>::get_max() const
{
  fmt::println("Specialized method called to get max on const char*");
  size_t max_index = 0;

  for (size_t i{}; i < m_size; ++i) {

    if ((strcmp(m_items[i], m_items[max_index])) > 0) { max_index = i; }
  }

  return m_items[max_index];
}
