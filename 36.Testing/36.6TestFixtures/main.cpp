#include <catch2/catch_test_macros.hpp>
#include "boxcontainer.h"

// A fixture is just a class: its constructor runs before each TEST_CASE_METHOD
// that uses it (setup), and its destructor runs after (teardown). Catch2
// creates a fresh instance per test case, so tests never see leftover state
// from a previous one -- no manual "reset the box before every test" code.
class PopulatedBoxFixture
{
protected:
	PopulatedBoxFixture() : box(10) {
		// Setup: every test using this fixture starts from the same
		// three-item box, instead of repeating these three lines everywhere.
		box.add(1);
		box.add(2);
		box.add(3);
	}

	// No custom destructor needed here -- BoxContainer's own destructor
	// (freeing m_items) is the teardown. A fixture with a raw resource of
	// its own (a temp file, a socket) would release it here.

	BoxContainer box;
};

TEST_CASE_METHOD(PopulatedBoxFixture, "A populated box starts with three items"){
	REQUIRE(box.size() == 3);
}

TEST_CASE_METHOD(PopulatedBoxFixture, "Adding to a populated box increases its size"){
	box.add(4);
	REQUIRE(box.size() == 4);
}

TEST_CASE_METHOD(PopulatedBoxFixture, "Removing from a populated box decreases its size"){
	bool removed = box.remove_item(2);
	REQUIRE(removed == true);
	REQUIRE(box.size() == 2);
}

TEST_CASE_METHOD(PopulatedBoxFixture, "Each test case gets its own fresh fixture instance"){
	// If this ran after "Adding to a populated box increases its size" and
	// somehow reused that box, size() would be 4 here instead of 3 -- but
	// each TEST_CASE_METHOD constructs a brand new PopulatedBoxFixture.
	REQUIRE(box.size() == 3);
}
