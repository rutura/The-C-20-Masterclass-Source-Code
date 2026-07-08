#include <catch2/catch_test_macros.hpp>
#include "rectangle.h"

// Catch2::Catch2WithMain supplies int main() for us -- this file only
// declares test cases. Building and running this executable runs every
// TEST_CASE below and reports pass/fail, instead of us eyeballing numbers.

TEST_CASE("Rectangle area is width times height"){
	Rectangle rect(4.0, 3.0);
	REQUIRE(rect.area() == 12.0);
}

TEST_CASE("Rectangle perimeter is twice the sum of width and height"){
	Rectangle rect(4.0, 3.0);
	REQUIRE(rect.perimeter() == 14.0);
}

TEST_CASE("A non-square rectangle exposes bugs a square would hide"){
	// This is exactly the case 36.2WhyTesting never tried -- if perimeter()
	// were still "2 * width + height", this REQUIRE would fail immediately
	// instead of silently passing like it did with a 4x4 square.
	Rectangle rect(10.0, 2.0);
	CHECK(rect.area() == 20.0);
	CHECK(rect.perimeter() == 24.0);
}
