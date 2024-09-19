#pragma once
/*
Basic Concepts

    Templates: 
        . Templates in C++ allow you to write generic and reusable code. Instead of writing the same code for different data types, you can write a template that works with any data type.
    Template Parameters: 
        . These are placeholders for data types. When you use a template, you specify the actual data types that replace these placeholders.
    Template Template Parameters: 
        . These are placeholders for entire template classes. This means you can pass a template class as a parameter to another template.

Example

    Let's create a simple example to demonstrate template template parameters. We'll use a basic container (like a vector or list) and a class that operates on this container.
        Step 1: Basic Template Class: See Container below
            . Container is a template class that works with any type T.
            . It has a vector to store elements and two methods: 
                . add to add elements,  and 
                . print to display them.

        Step 2: Template Template Parameter: See Processor below
            . Processor is a template class with two template parameters:
                . ContainerType: This is a template template parameter. It represents a template class that takes one type parameter.
                . T: This is the type of elements that the container will hold.

            . The process method takes a reference to a ContainerType instance and an element of type T. It adds the element to the container and then prints the container's contents.

        Step 3: Using the Templates: See template_template_parameters_demo in utilities.ixx
            . We create an instance of Container for integers called myContainer.
            . We create an instance of Processor that works with Container and integers.
            . We use the process method to add elements to myContainer and print its contents.
*/


#include <fmt/format.h>
#include <iostream>
#include <vector>


namespace template_template_parameters {

//The container template.
template<typename T> class Container
{
public:
  void add(const T &element) { data.push_back(element); }

  void print() const
  {
    for (const auto &element : data) { fmt::print("{} ", element); }
    fmt::print("\n");
  }

private:
  std::vector<T> data;
};

//Template template parameter.
template<template <typename> class ContainerType, typename T> class Processor
{
public:
  void process(ContainerType<T> &container, const T &element)
  {
    container.add(element);
    container.print();
  }
};

}//namespace template_template_parameters