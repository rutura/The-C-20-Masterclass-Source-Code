#include <catch2/catch_test_macros.hpp>
#include "rectangle.h"

// A prompt like "write Catch2 tests for this Rectangle class" reliably
// produces the first three TEST_CASEs below -- solid coverage of the
// obvious cases, generated in seconds instead of hand-typed.
TEST_CASE("Rectangle area is width times height"){
	Rectangle rect(5.0, 3.0);
	REQUIRE(rect.area() == 15.0);
}

TEST_CASE("Rectangle perimeter is twice the sum of width and height"){
	Rectangle rect(5.0, 3.0);
	REQUIRE(rect.perimeter() == 16.0);
}

TEST_CASE("A square is a rectangle with equal sides"){
	Rectangle square(4.0, 4.0);
	REQUIRE(square.area() == 16.0);
	REQUIRE(square.perimeter() == 16.0);
}

// What generated suites often don't think to cover on their own: boundary
// and degenerate cases. A zero-width "rectangle" is a real edge case this
// class currently allows silently -- worth testing (and worth deciding, as
// the class's author, whether that's actually the behavior you want). This
// is the review step: treat generated tests as a solid first draft to
// extend and question, not a finished, trustworthy suite to accept as-is.
TEST_CASE("A zero-width rectangle has zero area"){
	Rectangle degenerate(0.0, 5.0);
	REQUIRE(degenerate.area() == 0.0);
}
