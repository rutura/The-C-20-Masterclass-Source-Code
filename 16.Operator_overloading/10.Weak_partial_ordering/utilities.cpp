#include "utilities.h"

#include <string>
#include <cmath>
#include <string_view>
#include <fmt/format.h>

void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

//#1: Weak ordering example1
/*
void weak_ordering_ex1(){
	ComparableString cmp_str1("Fog");
	ComparableString cmp_str2("Dogy");

	fmt::println("cmp_str1 > cmp_str2 : {}", (cmp_str1 > cmp_str2));
	fmt::println("cmp_str1 < cmp_str2 : {}", (cmp_str1 < cmp_str2));

	fmt::println("cmp_str1 == cmp_str2 : {}", (cmp_str1 == cmp_str2));
}
*/


//#2: Weak ordering example 2
/*
std::weak_ordering case_insensitive_compare(const char *str1, const char *str2)
{

  // Turn them all to uppercase
  std::string string1(str1);
  std::string string2(str2);

  for (auto &c : string1) { c = toupper(c); }

  for (auto &c : string2) { c = toupper(c); }

  int cmp = string1.compare(string2);
  if (cmp > 0)
    return std::weak_ordering::greater;
  else if (cmp == 0)
    return std::weak_ordering::equivalent;
  else
    return std::weak_ordering::less;
}

void weak_ordering_ex2(){
	CaseInsensitiveString ci_str1("Hello");
	CaseInsensitiveString ci_str2("ZELLO");


	fmt::println("ci_str1 <= ci_str2 : {}", (ci_str1 <= ci_str2));
	fmt::println("ci_str1 <= Kello : {}", (ci_str1 <= "Kello"));
	fmt::println("Kello <= ci_str2 : {}", ("Kello" <= ci_str2));

	// You need to put in a == operator. Compiler won't generate one for you.
	fmt::println("ci_str1 == ci_str2 : {}", (ci_str1 == ci_str2));
}
*/


//#3: Partial ordering example

// Valid comparable points are within the [100,100] bounds

void partial_ordering_example(){

	Point p1(110, 110);
	Point p2(20, 20);

	auto result1 = (p1 > p2);
	fmt::println("p1 > p2 : {}", result1);

	auto result2 = (p1 >= p2);
	fmt::println("p1 >= p2 : {}", result2);

	auto result3 = (p1 == p2);
	fmt::println("p1 == p2 : {}", result3);

	auto result4 = (p1 != p2);
	fmt::println("p1 != p2 : {}", result4);

	auto result5 = (p1 < p2);
	fmt::println("p1 < p2 : {}", result5);

	auto result6 = (p1 <= p2);
	fmt::println("p1 <= p2 : {}", result6);
}