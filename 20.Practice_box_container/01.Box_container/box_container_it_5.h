#pragma once

#include "stream_insertable.h"

namespace iteration_5 {

/* *****************************************************************************************************************/
/* *****************************************************************************************************************/
//char container
class CharContainer : public iteration_1::StreamInsertable
{
  using value_type = char;// Allows us to change what's stored in the vector on the fly
  // Can make it store int, double,...
  static const size_t DEFAULT_CAPACITY = 5;
  static const size_t EXPAND_STEPS = 5;

public:
  CharContainer(size_t capacity = DEFAULT_CAPACITY);
  CharContainer(const CharContainer &source);
  ~CharContainer();

  //StreamInsertable Interface
  virtual void stream_insert(std::ostream &out) const;

  // Helper getter methods
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; };

  //Method to add items to the box
  void add(const value_type &item);
  bool remove_item(const value_type &item);
  size_t remove_all(const value_type &item);

  //In class operators
  void operator +=(const CharContainer &operand);
  void operator =(const CharContainer &source);

private :
  void expand(size_t new_capacity);

private :
  value_type *m_items;
  size_t m_capacity;
  size_t m_size;
};

//Free operators
CharContainer operator +(const CharContainer &left, const CharContainer &right);

/* *****************************************************************************************************************/
/* *****************************************************************************************************************/
//double container

class DoubleContainer : public iteration_1::StreamInsertable
{
  using value_type = double;// Allows us to change what's stored in the vector on the fly
  // Can make it store int, double,...
  static const size_t DEFAULT_CAPACITY = 5;
  static const size_t EXPAND_STEPS = 5;

public:
  DoubleContainer(size_t capacity = DEFAULT_CAPACITY);
  DoubleContainer(const DoubleContainer &source);
  ~DoubleContainer();

  //StreamInsertable Interface
  virtual void stream_insert(std::ostream &out) const;

  // Helper getter methods
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; };


  //Method to add items to the box
  void add(const value_type &item);
  bool remove_item(const value_type &item);
  size_t remove_all(const value_type &item);

  //In class operators
  void operator +=(const DoubleContainer &operand);
  void operator =(const DoubleContainer &source);

private :
  void expand(size_t new_capacity);

private :
  value_type *m_items;
  size_t m_capacity;
  size_t m_size;
};

//Free operators
DoubleContainer operator +(const DoubleContainer &left, const DoubleContainer &right);

/* *****************************************************************************************************************/
/* *****************************************************************************************************************/
//int container

class IntContainer : public iteration_1::StreamInsertable
{
  using value_type = int;// Allows us to change what's stored in the vector on the fly
  // Can make it store int, double,...
  static const size_t DEFAULT_CAPACITY = 5;
  static const size_t EXPAND_STEPS = 5;

public:
  IntContainer(size_t capacity = DEFAULT_CAPACITY);
  IntContainer(const IntContainer &source);
  ~IntContainer();

  //StreamInsertable Interface
  virtual void stream_insert(std::ostream &out) const;

  // Helper getter methods
  size_t size() const { return m_size; }
  size_t capacity() const { return m_capacity; };

  //Method to add items to the box
  void add(const value_type &item);
  bool remove_item(const value_type &item);
  size_t remove_all(const value_type &item);

  //In class operators
  void operator +=(const IntContainer &operand);
  void operator =(const IntContainer &source);

private :
  void expand(size_t new_capacity);

private :
  value_type *m_items;
  size_t m_capacity;
  size_t m_size;
};

//Free operators
IntContainer operator +(const IntContainer &left, const IntContainer &right);


}// namespace iteration_5