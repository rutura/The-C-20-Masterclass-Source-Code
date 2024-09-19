#include "utilities.h"

#include "boxcontainer.h"
#include "move_semantics_01.h"
#include "move_semantics_02.h"
#include "move_semantics_03.h"
#include "move_semantics_04.h"
#include "move_semantics_05.h"
#include "move_semantics_06.h"
#include "move_semantics_08.h"

#include <string_view>
#include <memory>
#include <iostream>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }


void move_semantics_01_demo() { move_semantics_01::try_out_move_semantics(); }

void move_semantics_02_demo() { move_semantics_02::try_out_move_semantics(); }

void move_semantics_03_demo()
{

  box::BoxContainer<int> box_array[2];
  std::cout << "--------" << std::endl;

  for (size_t i{ 0 }; i < 2; ++i) {
    box_array[i] = move_semantics_03::make_box(i + 1);//Copy assignment operator called at each iteration
    // We're copying data from the temporary and
    // throwing the temporary away (with data)
  }
  std::cout << "--------" << std::endl;
}

void move_semantics_04_demo()
{

  box::BoxContainer<int> box_array[2];
  std::cout << "--------" << std::endl;

  for (size_t i{ 0 }; i < 2; ++i) {
    box_array[i] = move_semantics_04::make_box(i + 1);//Move assignment operator called
  }
  std::cout << "--------" << std::endl;
}

void move_semantics_05_demo()
{
  box::BoxContainer<int> box1;
  move_semantics_05::populate_box(box1, 2);
  box::BoxContainer<int> box2;
  move_semantics_05::populate_box(box2, 15);

  std::cout << "box1 : " << box1 << "\n";
  std::cout << "box2 : " << box2 << "\n";

  move_semantics_05::swap_data(box1, box2);

  std::cout << "-----" << "\n";

  std::cout << "box1 : " << box1 << "\n";
  std::cout << "box2 : " << box2 << "\n";
}

void move_semantics_06_demo()
{

  box::BoxContainer<int> box1;
  move_semantics_06::populate_box(box1, 2);

  std::cout << "box1 : " << box1 << "\n";

  box::BoxContainer<int> box2(std::move(box1));

  std::cout << "box2 : " << box2 << "\n";
  std::cout << "box1 : " << box1 << "\n";


  std::cout << "------" << "\n";

  box1.add(34);
  box1.add(4);
  std::cout << "box1 : " << box1 << "\n";

}


void move_semantics_07_demo()
{

  /*
  box::BoxContainer<int> box1;
  move_semantics_07::populate_box(box1,2);

std::cout << "box1 : " << box1 << std::endl;

box::BoxContainer<int> box2;

  box2 = std::move(box1);

  std::cout << "------" << std::endl;

  std::cout << "box1 : " << box1 << std::endl;
  std::cout << "box2 : " << box2 << std::endl;


  std::cout << "------" << std::endl;

std::unique_ptr<int> ptr_int = std::make_unique<int>(33);

  std::cout << "*ptr_int : " << *ptr_int << std::endl;

  std::unique_ptr<int> ptr_int_copy = ptr_int; // Error.


  if(ptr_int){
          std::cout << "*ptr_int : " << *ptr_int << std::endl;
  }else{
          std::cout << "ptr_int doesn't contain any valid data" << std::endl;
  }
  std::cout << "*ptr_int_copy : " << *ptr_int_copy << std::endl;
  */

}

void move_semantics_08_demo()
{


  /*
  move_semantics_08::Item&& rvalue_ref {move_semantics_08::get_value()};

  //move_semantics_08::Item item1(std::move(rvalue_ref)); // Move constructor

  //std::cout << "-------" << std::endl;

  move_semantics_08::do_something(std::move(rvalue_ref));
  */

  box::BoxContainer<move_semantics_08::Item> items;
  items.add(move_semantics_08::get_value());

}