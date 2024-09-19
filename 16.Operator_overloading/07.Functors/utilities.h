#pragma once

#include <string>

class Print
{
public:
  void operator()(const std::string &name) const;

  std::string operator()(const std::string &last_name, const std::string &first_name) const;
};

void functors();
void print_msg(std::string_view msg);
void do_something(const Print &printer);