#include "utilities.h"

#include "catching_std_exceptions.h"
#include "deriving_from_std_exceptions.h"
#include "throwing_std_exceptions.h"

#include <iostream>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void catching_std_exceptions_demo()
{
  catching_std_exceptions::Animal animal;
  try { catching_std_exceptions::Feline &feline_ref = dynamic_cast<catching_std_exceptions::Feline &>(animal); } catch (
    std::exception &ex) { fmt::println("Something is wrong : {}", ex.what()); }

  fmt::println("END.");
}

void throwing_std_exceptions_demo()
{

  throwing_std_exceptions::Students students("John Snow",
    "Terry Boomd",
    "Nicholai Itchenko",
    "Bilom Atunde",
    "Lily Park");

  try {
    // fmt::println( students.get_student(2) );
    fmt::println("{}", students.get_student(-2));
  } catch (std::exception &ex) { fmt::println("Exception cought : {}", ex.what()); }
  fmt::println("END.");
}

void deriving_from_std_exceptions_demo()
{
  try { deriving_from_std_exceptions::divide(10, 0); } catch (std::exception &ex) {


    // We know that the thrown exception contains a DivideByZeroException
    // part do ws can downcast safely and call non virtual functions
    deriving_from_std_exceptions::DivideByZeroException *d_z =
      dynamic_cast<deriving_from_std_exceptions::DivideByZeroException *>(&ex);
    if (d_z) { fmt::println("{}: dividing {} by {}", ex.what(), d_z->get_a(), d_z->get_b()); }

    //fmt::println("Something went wrong: {}", ex.what());
  }
}