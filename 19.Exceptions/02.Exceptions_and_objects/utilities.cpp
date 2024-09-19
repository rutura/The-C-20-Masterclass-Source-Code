#include "utilities.h"

#include "polymorphic_exceptions.h"
#include "throw_class_objects.h"
#include "throw_class_objects_with_inheritance.h"

#include <string_view>
#include <fmt/format.h>


void print_msg(std::string_view msg) { fmt::println("{}", msg); }


void throw_class_objects_demo()
{
  for (size_t i{ 0 }; i < 5; ++i) {
    try { throw_class_objects::do_something(i); } catch (throw_class_objects::SomethingIsWrong &ex) {
      fmt::println("Exception cought : {}", ex.what());
    }
  }
}

void throw_class_objects_with_inheritance_demo()
{
  for (size_t i{ 0 }; i < 5; ++i) {
    try { throw_class_objects_with_inheritance::do_something(i); } catch (
      throw_class_objects_with_inheritance::CriticalError &
      ex) { fmt::println("CriticalError Exception cought : {}", ex.what()); } catch (
      throw_class_objects_with_inheritance::SmallError &
      ex) { fmt::println("SmallError Exception cought : {}", ex.what()); } catch (
      throw_class_objects_with_inheritance::Warning &ex) { fmt::println("Warning Exception cought : {}", ex.what()); }
    catch (throw_class_objects_with_inheritance::SomethingIsWrong &ex) {
      fmt::println("SomethingIsWrong Exception cought : {}", ex.what());
    }
  }
}


void polymorphic_exceptions_demo()
{
  for (size_t i{ 0 }; i < 5; ++i) {
    try { polymorphic_exceptions::do_something(i); }
    /*
    catch(polymorphic_exceptions::CriticalError& ex){
            fmt::println( "CriticalError Exception cought : {}" , ex.what() );
    }
    catch(polymorphic_exceptions::SmallError& ex){
            fmt::println( "SmallError Exception cought : {}" , ex.what() );
    }
    catch(polymorphic_exceptions::Warning& ex){
            fmt::println( "Warning Exception cought : {}" , ex.what() );
    }
    */
    catch (polymorphic_exceptions::SomethingIsWrong &ex) {
      fmt::println("SomethingIsWrong Exception cought : {}", ex.what());
    }
  }
}