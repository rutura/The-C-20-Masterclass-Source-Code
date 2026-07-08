#include <print>
#include "rectangle.h"

// A manual, ad-hoc check: run the program, read the numbers, eyeball them.
// It "works" for the one case we happened to try -- a square, where the
// perimeter bug (2 * width + height instead of 2 * (width + height))
// silently produces a number close enough to look plausible at a glance.
int main(){

	Rectangle square(4.0, 4.0);

	std::println("area      : {}", square.area());
	std::println("perimeter : {}", square.perimeter());

	// Nothing here actually confirms the numbers are correct -- we're just
	// printing and trusting our own eyes. A non-square rectangle would
	// expose the bug immediately, but we didn't think to try one, and
	// nothing forced us to. That's the problem this chapter solves.

	return 0;
}
