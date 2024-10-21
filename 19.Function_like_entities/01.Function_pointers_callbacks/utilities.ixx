module;

#include <fmt/format.h>

#include <iostream>
#include <string>
#include <string_view>

export module utilities;

import function_pointers_01;
import function_pointers_02;
import box_container_it_5;
import function_pointers_03;

using iteration_5::BoxContainer;


export void function_pointers_01_demo() {

  using function_pointers_01::add;

  //double (*f_ptr)(double, double) = &add;
  //double(*f_ptr) (double,double) = add;

  //double(*f_ptr) (double,double) {&add};
  //double(*f_ptr) (double,double){add};

  //auto f_ptr = &add;
  //auto f_ptr = add;

  //auto *f_ptr = &add;
  //auto *f_ptr = add;

  // Things gone wroong
  //double (*f_ptr)(double, double) = nullptr;

  //fmt::println("add(10,30) : {}", f_ptr(10, 30));
}

export void function_pointers_02_demo() {

  using function_pointers_02::encrypt;
  using function_pointers_02::decrypt;
  using function_pointers_02::modify;
  using function_pointers_02::get_best;
  using function_pointers_02::larger_in_size;
  using function_pointers_02::greater_lexicographically;
  using function_pointers_02::str_comparator;

    std::string msg{"Hello"};
    modify(msg, encrypt);
    fmt::println("outcome : {}", msg);

    fmt::println("------");

    BoxContainer<std::string> quote;
    quote.add("The");
    quote.add("sky");
    quote.add("is");
    quote.add("blue");
    quote.add("my");
    quote.add("friend");
    std::cout << "Initial: " << quote << "\n";
    std::cout << modify(quote,encrypt) << "\n";
    std::cout << modify(quote,decrypt)<< "\n";

    fmt::println("larger in size : {}", get_best( quote, larger_in_size));
    fmt::println("greater lexicographicaly : {}", get_best(quote, greater_lexicographically));

    // Using the type alias
    str_comparator callback{ larger_in_size};

    fmt::println("larger in size : {}",get_best(quote, callback));
}

export void function_pointers_03_demo() {

  using function_pointers_03::get_best;
  using function_pointers_03::larger_in_size;
  using function_pointers_03::greater_lexicographically;
  using function_pointers_03::larger_int;
  using function_pointers_03::smaller;
	
  BoxContainer<std::string> quote;
  quote.add("The");
  quote.add("sky");
  quote.add("is");
  quote.add("blue");
  quote.add("my");
  quote.add("friend");

  std::cout << "Gettting the best : \n";
  std::cout << "larger in size : " << get_best(quote, larger_in_size) << "\n";
  std::cout << "greater lexicographicaly : " << get_best( quote, greater_lexicographically) << "\n";

  fmt::println("------------");

  BoxContainer<int> ints;
  ints.add(10);
  ints.add(3);
  ints.add(233);
  ints.add(23);
  ints.add(4);

  std::cout << "larger int: " << get_best(ints, larger_int) << "\n";
  std::cout << "smaller int: " <<  get_best(ints, smaller) << "\n";
}