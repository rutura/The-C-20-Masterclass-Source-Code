#pragma once

#include <iostream>

namespace box {

// BoxContainer with a stream insertion operator

template<typename T> class BoxContainer
{
  friend std::ostream &operator<<<>(std::ostream &, const BoxContainer<T> &);

  static const size_t DEFAULT_CAPACITY = 5;
  static const size_t EXPAND_STEPS = 5;

public:
  BoxContainer(size_t capacity = DEFAULT_CAPACITY);
  BoxContainer(const BoxContainer<T> &source);
  ~BoxContainer();

  // Method to add items to the box
  void add(const T &item);
  bool remove_item(const T &item);
  size_t remove_all(const T &item);
  // In class operators
  void operator+=(const BoxContainer<T> &operand);
  void operator=(const BoxContainer<T> &source);
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; };
  T get_item(size_t index) const { return m_items[index]; }

private:
  void expand(size_t new_capacity);

private:
  T *m_items;
  size_t m_capacity;
  size_t m_size;
};

// Free operators
template<typename T> BoxContainer<T> operator+(const BoxContainer<T> &left,
  const BoxContainer<T> &right);

}//namespace box