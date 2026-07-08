#include <print>
#include <string>
#include <vector>
#include "point.h"

// A frequent piece of bad move-semantics advice: "always std::move your
// return value to avoid a copy." Applied here, it looks helpful and
// compiles cleanly -- but it actively defeats copy elision (NRVO), which
// the compiler would otherwise apply for free, and in some cases can force
// a move where a plain return would have elided the copy/move entirely.
// Chapter 17 (MoveSemantics) covers what std::move actually does and does
// not do; a suggestion like this is worth recognizing, not accepting
// because it mentions the right vocabulary word.
std::vector<int> make_numbers_bad(){
	std::vector<int> result{1, 2, 3, 4, 5};
	return std::move(result); // Don't do this -- see comment above.
}

// The correct version: just return it. The compiler applies NRVO (or, at
// worst, an implicit move) on its own -- std::move here would only get in
// the way.
std::vector<int> make_numbers_good(){
	std::vector<int> result{1, 2, 3, 4, 5};
	return result;
}

int main(){

	Point p1(3.0, 4.0);
	Point p2(3.0, 4.0);

	// This is what the six-operators-vs-one-defaulted-<=> difference from
	// point.h actually buys you: it still just works.
	std::println("p1 == p2 : {}", p1 == p2);
	std::println("p1 <  p2 : {}", p1 < p2);

	// Both versions produce the same observable result -- the difference
	// is what the compiler was allowed to optimize, not what the program
	// prints. That's exactly why this class of mistake is easy to miss:
	// nothing about running the program tells you a copy elision
	// opportunity was thrown away.
	auto numbers_bad = make_numbers_bad();
	auto numbers_good = make_numbers_good();
	std::println("numbers_bad.size()  : {}", numbers_bad.size());
	std::println("numbers_good.size() : {}", numbers_good.size());

	return 0;
}
