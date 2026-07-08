#include <print>
#include <string>
#include <vector>

// Something as simple as "join these strings with a separator" doesn't
// exist as a single standard library call -- you either write it yourself
// (and get the off-by-one comma wrong at least once), or reach for a
// library that already solved it. This is the tedious hand-written version.
std::string join(const std::vector<std::string>& items, const std::string& separator){
	std::string result;

	for(size_t i{0}; i < items.size(); ++i){
		result += items[i];
		if (i != items.size() - 1)
			result += separator;
	}

	return result;
}

int main(){

	std::vector<std::string> ingredients{"flour", "sugar", "eggs", "butter"};

	std::println("{}", join(ingredients, ", "));

	// Now imagine we also need to: trim whitespace from user input, parse a
	// JSON config file, make an HTTPS request, or format a number with
	// thousands separators. Each of those is its own multi-hundred-line
	// problem that thousands of other C++ programmers have already solved
	// correctly (and battle-tested) in an existing library. Writing every
	// one of those from scratch, by hand, in every project, doesn't scale --
	// which is exactly the problem dependency management tools solve.

	return 0;
}
