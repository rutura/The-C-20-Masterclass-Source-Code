#include "utilities.h"

#include "boxcontainer.h"
#include "functors_01.h"
#include "functors_02.h"
#include "functors_03.h"
#include "functors_04.h"

#include <fmt/format.h>

#include <functional>
#include <iostream>
#include <string>
#include <string_view>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void functors_01_demo()
{
  // Modifying through functors
  std::string msg{ "Hello world!" };
  functors_01::Encrypt encryptor;
  functors_01::Decrypt decryptor;

  fmt::print("Original message: {}\n", msg);
  functors_01::modify(msg, encryptor);
  fmt::print("Encrypted message: {}\n", msg);
  functors_01::modify(msg, decryptor);
  fmt::print("Decrypted message: {}\n", msg);

  // Modifying through function pointers
  std::string msg2{ "Hello world!" };
  fmt::print("Original message: {}\n", msg2);
  functors_01::modify(msg2, functors_01::encrypt);
  fmt::print("Encrypted message: {}\n", msg2);
  functors_01::modify(msg2, functors_01::decrypt);
  fmt::print("Decrypted message: {}\n", msg2);
}

void functors_02_demo()
{
  std::plus<int> adder;
  std::minus<int> substracter;
  std::greater<int> compare_greater;

  fmt::println("10 + 7: {}", adder(10, 7));// 17
  fmt::println("10 - 7: {}", substracter(10, 7));// 3
  fmt::println(" 10 > 7: {}", compare_greater(10, 7));// true

  fmt::println("---------------------------------");

  box::BoxContainer<std::string> quote;
  quote.add("The");
  quote.add("sky");
  quote.add("is");
  quote.add("blue");
  quote.add("my");
  quote.add("friend");

  std::greater<std::string> string_comparator{};

  // fmt::println("quote : {}", quote);
  std::cout << "quote: " << quote << "\n";
  //  Built in functor
  fmt::println("greater string : {}",
    functors_02::get_best(quote, string_comparator));
  // Custom function pointer
  fmt::println(
    "greater string : {}",
    functors_02::get_best(quote, functors_02::custom_greater<std::string>));
  // Custom functor
  functors_02::Greater<std::string> greater_string_custom_functor;
  fmt::println("greater string :{} ",
    functors_02::get_best(quote, greater_string_custom_functor));

  fmt::println("---------------------------------");

  box::BoxContainer<int> ints;
  ints.add(10);
  ints.add(3);
  ints.add(6);
  ints.add(72);
  ints.add(23);
  ints.add(4);

  std::greater<int> int_comparator{};
  functors_02::Greater<int> greater_int_custom_functor;

  std::cout << "ints: " << ints << "\n";
  fmt::println("greater int :{} ", functors_02::get_best(ints, int_comparator));
  fmt::println("greater int :{} ",
    functors_02::get_best(ints,
      functors_02::custom_greater<int>));
  fmt::println("greater int :{} ",
    functors_02::get_best(ints, greater_int_custom_functor));
  fmt::println("lesser int : {}", functors_02::get_best(ints, std::less<int>{}));
}


void functors_03_demo()
{

  box::BoxContainer<double> doubles;
  doubles.add(10.1);
  doubles.add(20.2);
  doubles.add(30.3);
  doubles.add(15);

  std::cout << "doubles: " << doubles << "\n";
  fmt::println("range_sum :{} ", functors_03::range_sum(doubles, functors_03::IsInRange<double>(10.0, 15.5)));
  fmt::println("range_sum :{} ", functors_03::range_sum(doubles, functors_03::IsInRange<double>(10.0, 41.5)));


  fmt::println("------");
  /*
  //Constraints not satisfied.
  box::BoxContainer<std::string> strings;
  strings.add("Hello");
  strings.add("World");
  functors_03::	range_sum(strings,functors_03::IsInRange<std::string> ("Hello","World"));
  */

  fmt::println("-----");

  box::BoxContainer<int> ints;
  ints.add(10);
  ints.add(3);
  ints.add(6);
  ints.add(72);
  ints.add(23);
  ints.add(4);

  std::cout << "ints: " << ints << "\n";
  fmt::println("range_sum :{} ", functors_03::range_sum(ints, functors_03::IsInRange<int>(10, 20)));// 10
  fmt::println("range_sum :{} ", functors_03::range_sum(ints, functors_03::IsInRange<int>(10, 30)));// 33

}


void functors_04_demo() { functors_04::lambda_sandbox(); }