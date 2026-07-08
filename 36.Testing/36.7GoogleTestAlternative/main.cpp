#include <gtest/gtest.h>
#include "bank_account.h"

// Same BankAccount, same scenarios as 36.4AssertionsAndSections -- only the
// testing framework changed, so the syntax differences are easy to compare
// side by side. GoogleTest is the other major C++ testing framework you'll
// run into in industry, especially on projects that already use it.

// GoogleTest groups tests with TEST(SuiteName, TestName) instead of Catch2's
// single free-form string, and uses EXPECT_*/ASSERT_* macros instead of
// REQUIRE/CHECK. ASSERT_* stops the test immediately on failure (like
// REQUIRE); EXPECT_* records the failure and keeps going (like CHECK).

TEST(BankAccountTest, DepositIncreasesBalance){
	BankAccount account(100.0);
	account.deposit(50.0);
	EXPECT_EQ(account.balance(), 150.0);
}

TEST(BankAccountTest, WithdrawDecreasesBalance){
	BankAccount account(100.0);
	account.withdraw(30.0);
	EXPECT_EQ(account.balance(), 70.0);
}

TEST(BankAccountTest, InvalidDepositThrows){
	BankAccount account(100.0);
	EXPECT_THROW(account.deposit(-5.0), std::invalid_argument);
}

TEST(BankAccountTest, WithdrawingTooMuchThrows){
	BankAccount account(100.0);
	EXPECT_THROW(account.withdraw(1000.0), std::runtime_error);
}

TEST(BankAccountTest, ApproximateFloatingPointComparison){
	BankAccount account(0.0);
	account.deposit(1.0 / 3.0);
	account.deposit(1.0 / 3.0);
	account.deposit(1.0 / 3.0);

	// GoogleTest's equivalent of Catch2's Approx is EXPECT_NEAR, which takes
	// an explicit tolerance rather than inferring one.
	EXPECT_NEAR(account.balance(), 1.0, 0.0001);
}

// GTest::gtest_main supplies int main() for us, same convenience as
// Catch2::Catch2WithMain -- this file only declares tests.
