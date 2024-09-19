#include "base_acc_spec.h"
#include "inh_basics.h"
#include "priv_inh.h"
#include "protected_members.h"
#include "resurect.h"

#include <iostream>
#include <fmt/format.h>

void print_msg(std::string_view msg) { fmt::println("{}", msg); }

void inheritance_basics()
{
  inh_basics::Player p1("Basketball");
  p1.set_first_name("John");
  p1.set_last_name("Snow");
  std::cout << "player: " << p1 << "\n";
}

void protected_members_func()
{
  protected_members::Player p1("Basketball", "John", "Snow");
  std::cout << "player: " << p1 << "\n";
}

void base_access_specifiers()
{
  base_acc_spec::Person person1("Daniel Gray", 27, "Blue Sky St 233 #56");
  std::cout << "Person: " << person1 << "\n";

  fmt::println("---------------");

  base_acc_spec::Player player;
  player.m_full_name = "Samuel Jackson";
  // player.m_age = 55; Compier error
  // player.m_address = "2i892317322"; Compiler

  fmt::println("------------------");

  base_acc_spec::Nurse nurse1;
  // nurse1.m_full_name = "Davy Johnes";Compiler error
  // nurse1.m_age = 51; // Compiler error

  fmt::println("---------------");
  base_acc_spec::Engineer engineer1;
  // engineer1.m_full_name = "Olivier Godson"; // Compiler error
  // engineer1.m_age = 55; // Compiler error
  // engineer1.m_address = "dsakfd;aslfjd;laskf"; // Compiler error
}

void zooming_on_private_inheritance()
{
  priv_inh::Engineer eng1;
  priv_inh::CivilEngineer ce1;
  fmt::println("Done");
}

void resurect_members_back_in_context()
{
  resurect::Engineer eng1;
  resurect::CivilEngineer ce1;
  fmt::println("Done");

}