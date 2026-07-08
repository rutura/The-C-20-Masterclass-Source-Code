#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

#include <stdexcept>

class BankAccount
{
public:
	BankAccount(double balance = 0.0) : m_balance{balance} {
	}

	double balance() const {
		return m_balance;
	}

	void deposit(double amount){
		if (amount <= 0.0)
			throw std::invalid_argument("deposit amount must be positive");
		m_balance += amount;
	}

	void withdraw(double amount){
		if (amount <= 0.0)
			throw std::invalid_argument("withdrawal amount must be positive");
		if (amount > m_balance)
			throw std::runtime_error("insufficient funds");
		m_balance -= amount;
	}

private:
	double m_balance{};
};

#endif // BANK_ACCOUNT_H
