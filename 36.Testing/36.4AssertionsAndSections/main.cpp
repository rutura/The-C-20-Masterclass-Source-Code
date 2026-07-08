#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "bank_account.h"

TEST_CASE("Depositing and withdrawing changes the balance"){
	BankAccount account(100.0);

	// SECTION lets several scenarios share the same starting state (a fresh
	// account with balance 100) without repeating setup code -- Catch2 runs
	// the TEST_CASE once per SECTION, replaying everything above the section.
	SECTION("depositing increases the balance"){
		account.deposit(50.0);
		REQUIRE(account.balance() == 150.0);
	}

	SECTION("withdrawing decreases the balance"){
		account.withdraw(30.0);
		REQUIRE(account.balance() == 70.0);
	}

	SECTION("sections can nest"){
		account.deposit(10.0);
		SECTION("then withdraw"){
			account.withdraw(60.0);
			REQUIRE(account.balance() == 50.0);
		}
	}
}

TEST_CASE("Invalid operations throw"){
	BankAccount account(100.0);

	REQUIRE_THROWS_AS(account.deposit(-5.0), std::invalid_argument);
	REQUIRE_THROWS_AS(account.withdraw(0.0), std::invalid_argument);
	REQUIRE_THROWS_AS(account.withdraw(1000.0), std::runtime_error);
}

TEST_CASE("A third of a deposit split three ways needs an approximate comparison"){
	BankAccount account(0.0);
	account.deposit(1.0 / 3.0);
	account.deposit(1.0 / 3.0);
	account.deposit(1.0 / 3.0);

	// Exact equality on doubles is asking for trouble -- 0.333... added
	// three times will not land on exactly 1.0 bit-for-bit. Catch::Approx
	// (or the WithinRel matcher) compares within a tolerance instead.
	REQUIRE(account.balance() == Catch::Approx(1.0));
}
