#include "utilities.h"

#include "boxcontainer.h"
#include "function_pointers_01.h"
#include "function_pointers_02.h"
#include "function_pointers_03.h"

#include <fmt/format.h>

#include <iostream>
#include <string>
#include <string_view>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void function_pointers_01_demo()
{
  double (*f_ptr)(double, double) = &function_pointers_01::add;
  // double(*f_ptr) (double,double) = function_pointers_01::add;

  // double(*f_ptr) (double,double) {&function_pointers_01::add};
  // double(*f_ptr) (double,double){function_pointers_01::add};

  // auto f_ptr = &function_pointers_01::add;
  // auto f_ptr = function_pointers_01::add;

  // auto *f_ptr = &function_pointers_01::add;
  // auto *f_ptr = function_pointers_01::add;

  // Things gone wroong
  // double (*f_ptr)(double, double) = nullptr;

  fmt::println("add(10,30) : {}", f_ptr(10, 30));
}

void function_pointers_02_demo()
{
  std::string msg{ "Hello" };
  function_pointers_02::modify(msg, function_pointers_02::encrypt);
  fmt::println("outcome : {}", msg);

  fmt::println("------");

  box::BoxContainer<std::string> quote;
  quote.add("The");
  quote.add("sky");
  quote.add("is");
  quote.add("blue");
  quote.add("my");
  quote.add("friend");
  std::cout << "Initial: " << quote << "\n";
  std::cout << function_pointers_02::modify(quote,
      function_pointers_02::encrypt)
    << "\n";
  std::cout << function_pointers_02::modify(quote,
      function_pointers_02::decrypt)
    << "\n";

  fmt::println("larger in size : {}",
    function_pointers_02::get_best(
      quote,
      function_pointers_02::larger_in_size));
  fmt::println("greater lexicographicaly : {}",
    function_pointers_02::get_best(
      quote,
      function_pointers_02::greater_lexicographically));

  // Using the type alias
  function_pointers_02::str_comparator callback{
    function_pointers_02::larger_in_size };

  fmt::println("larger in size : {}",
    function_pointers_02::get_best(quote, callback));
}

void function_pointers_03_demo()
{

  box::BoxContainer<std::string> quote;
  quote.add("The");
  quote.add("sky");
  quote.add("is");
  quote.add("blue");
  quote.add("my");
  quote.add("friend");

  std::cout << "Gettting the best : \n";
  std::cout << "larger in size : "
    << function_pointers_03::get_best(
      quote,
      function_pointers_03::larger_in_size)
    << "\n";
  std::cout << "greater lexicographicaly : "
    << function_pointers_03::get_best(
      quote,
      function_pointers_03::greater_lexicographically)
    << "\n";

  fmt::println("------------");

  box::BoxContainer<int> ints;
  ints.add(10);
  ints.add(3);
  ints.add(233);
  ints.add(23);
  ints.add(4);

  std::cout << "larger int: "
    << function_pointers_03::get_best(ints,
      function_pointers_03::larger_int)
    << "\n";
  std::cout << "smaller int: " << function_pointers_03::get_best(ints, function_pointers_03::smaller) << "\n";
}