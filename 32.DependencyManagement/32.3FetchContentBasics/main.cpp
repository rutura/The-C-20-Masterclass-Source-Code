#include <fmt/core.h>
#include <fmt/ranges.h>
#include <string>
#include <vector>

int main(){

	std::vector<std::string> ingredients{"flour", "sugar", "eggs", "butter"};

	// The hand-written join() from 37.2WhyDependencyManagement, replaced by
	// a library that already solved this (and formatting/joining in
	// general) more thoroughly than our few lines did. fmt::join builds a
	// formatted range lazily -- no intermediate std::string is built just
	// to throw it away.
	fmt::print("{}\n", fmt::join(ingredients, ", "));

	// fmt can also do things std::format/std::print can't yet on some
	// standard library implementations, and was the library std::format
	// itself was modeled on.
	fmt::print("{:>10}\n", "right-aligned");

	return 0;
}
