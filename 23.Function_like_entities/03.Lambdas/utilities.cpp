#include "utilities.h""

#include "boxcontainer.h"
#include "lambdas_01.h"
#include "lambdas_02.h"
#include "lambdas_03.h"
#include "lambdas_04.h"
#include "lambdas_05.h"

#include <string>
#include <string_view>
#include <iostream>
#include <fmt/format.h>


void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void lambdas_01_demo()
{

  std::string str{ "Hello" };

  auto encrypt = [](const char &param) {
    // Callback function
    return static_cast<char>(param + 3);
  };

  auto decrypt = [](const char &param) {
    // Callback function
    return static_cast<char>(param - 3);
  };

  // Modifying through callbacks.
  fmt::println("Initial : {}", str);
  fmt::println("Encrypted : {}", lambdas_01::modify(str, encrypt));
  fmt::println("Decrypted : {}", lambdas_01::modify(str, decrypt));

  fmt::println("---------");

  // Passing lambda functions directly
  fmt::println("Initial : {}", str);
  fmt::println("Encrypted : {}",
    lambdas_01::modify(str,
      [](const char &param) {
        // Callback function
        return static_cast<char>(param + 3);
      }));
  fmt::println("Decrypted : {}",
    lambdas_01::modify(str,
      [](const char &param) {
        // Callback function
        return static_cast<char>(param - 3);
      }));


  fmt::println("--------");

  fmt::println("strings stored in BoxContainer : ");
  box::BoxContainer<std::string> quote;
  quote.add("The");
  quote.add("sky");
  quote.add("is");
  quote.add("blue");
  quote.add("my");
  quote.add("friend");
  std::cout << "Initial: " << quote << "\n";
  std::cout << "Encrypted: " << lambdas_01::modify(quote, encrypt) << "\n";
  std::cout << "Decrypted: " << lambdas_01::modify(quote, decrypt) << "\n";


  fmt::println("--------");

  auto larger_in_size = [](const std::string &str1, const std::string &str2) {
    if (str1.size() > str2.size()) return true;
    else return false;
  };

  auto greater_lexicographically = [](const std::string &str1, const std::string &str2) { return (str1 > str2); };

  fmt::println("Gettting the best : ");
  fmt::println("larger in size : {}", lambdas_01::get_best(quote, larger_in_size));
  fmt::println("greater lexicographicaly : {}", lambdas_01::get_best(quote, greater_lexicographically));
}

void lambdas_02_demo() { lambdas_02::capture_by_value_under_the_hood(); }

void lambdas_03_demo() { lambdas_03::capturing_by_ref_under_the_hood(); }

void lambdas_04_demo() { lambdas_04::mixing_it_up(); }

void lambdas_05_demo()
{
  lambdas_05::Item item{ 10, 20 };
  item.some_member_func();
}