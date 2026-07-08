#include <catch2/catch_test_macros.hpp>
#include "boxcontainer.h"

// Same test suite as 36.5TestingTheBoxContainer -- this lecture's focus is
// the CMakeLists.txt (enable_testing() + catch_discover_tests()), not new
// test content. Build normally to run every test via ./build/rooster, or
// build then run `ctest` from the build/ directory to see each TEST_CASE
// reported as its own pass/fail line, runnable individually by name.

// This is the same BoxContainer built up lecture by lecture in
// Practice-BoxContainerType. Writing tests for a class students already
// understand keeps the focus on testing technique, not on decoding a new
// example -- and shows that retrofitting tests onto existing code is
// normal, not something you only do for brand-new classes.

TEST_CASE("A freshly constructed BoxContainer is empty"){
	BoxContainer box(5);
	REQUIRE(box.size() == 0);
	REQUIRE(box.capacity() == 5);
}

TEST_CASE("add() grows the size and expands capacity when full"){
	BoxContainer box(2);
	box.add(10);
	box.add(20);
	REQUIRE(box.size() == 2);
	REQUIRE(box.capacity() == 2);

	// Adding a third item overflows the initial capacity of 2, so add()
	// should trigger expand() internally.
	box.add(30);
	REQUIRE(box.size() == 3);
	REQUIRE(box.capacity() > 2);
}

TEST_CASE("remove_item() removes exactly one matching item"){
	BoxContainer box(5);
	box.add(1);
	box.add(2);
	box.add(2);
	box.add(3);

	bool removed = box.remove_item(2);

	REQUIRE(removed == true);
	REQUIRE(box.size() == 3);
}

TEST_CASE("remove_item() returns false when the item isn't found"){
	BoxContainer box(5);
	box.add(1);

	bool removed = box.remove_item(99);

	REQUIRE(removed == false);
	REQUIRE(box.size() == 1);
}

TEST_CASE("remove_all() removes every matching occurrence"){
	BoxContainer box(10);
	box.add(7);
	box.add(3);
	box.add(7);
	box.add(7);

	size_t removed_count = box.remove_all(7);

	REQUIRE(removed_count == 3);
	REQUIRE(box.size() == 1);
}

TEST_CASE("The copy constructor makes an independent copy"){
	BoxContainer original(5);
	original.add(1);
	original.add(2);

	BoxContainer copy(original);
	copy.add(3);

	// The copy growing should not affect the original -- if the copy
	// constructor accidentally shared the underlying array, this would fail.
	REQUIRE(original.size() == 2);
	REQUIRE(copy.size() == 3);
}

TEST_CASE("operator+= appends the right-hand box's items"){
	BoxContainer box1(5);
	box1.add(1);
	box1.add(2);

	BoxContainer box2(5);
	box2.add(3);
	box2.add(4);

	box1 += box2;

	REQUIRE(box1.size() == 4);
}

TEST_CASE("operator+ combines two boxes without modifying either operand"){
	BoxContainer box1(5);
	box1.add(1);
	box1.add(2);

	BoxContainer box2(5);
	box2.add(3);

	BoxContainer combined = box1 + box2;

	REQUIRE(combined.size() == 3);
	REQUIRE(box1.size() == 2);
	REQUIRE(box2.size() == 1);
}

TEST_CASE("Copy assignment replaces the target's contents"){
	BoxContainer box1(5);
	box1.add(1);

	BoxContainer box2(5);
	box2.add(2);
	box2.add(3);
	box2.add(4);

	box1 = box2;

	REQUIRE(box1.size() == 3);
}
