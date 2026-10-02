#include <print>

// How an argument reaches a function - the two ways.
//
//   PASS BY VALUE      the parameter is a COPY of the argument.
//                      Changing the parameter does not affect the caller.
//
//   PASS BY REFERENCE  the parameter (written T&) is an ALIAS for the
//                      caller's variable. Changing the parameter changes
//                      the caller's variable.

// By value: `balance` is a copy of the caller's account balance. The
// deduction happens on the copy; the caller's balance is untouched and
// only sees the result if it uses the return value.

double charged_copy(double balance, double fee) {
	balance -= fee;
	return balance;
}


// By reference: `balance` refers to the caller's variable itself, so the
// deduction lands on the real account.
void charge(double& balance, double fee) {
	balance -= fee;
}

int main(){
	int original{ 100 };
	/*
	int copy{ original };

	copy = 250;                   // only the copy changes

	std::println("original: {}", original);   // 100
	std::println("copy:     {}", copy);        // 250

	std::println("&original: {}", static_cast<void*>(&original));   // e.g. 0x7ffc5968e520
	std::println("&copy:     {}", static_cast<void*>(&copy));       // e.g. 0x7ffc5968e524 - different!
	*/


	/*
	int& alias{ original };

	alias = 250;

	std::println("Original: {}", original);
	std::println("alias:    {}", alias);       // 250

	original = 500;

	std::println("Original: {}", original);
	std::println("alias:    {}", alias);       // 500

	std::println("&original: {}", static_cast<void*>(&original));   // e.g. 0x7ffc5968e520
	std::println("&alias:    {}", static_cast<void*>(&alias));      // e.g. 0x7ffc5968e520 - same!
	*/


	//Pass by value
	double checking{ 100.0 };
	std::println("checking = {} before charged_copy", checking);
	std::println("charged_copy(checking, 15) returns {}", charged_copy(checking, 15.0));
	std::println("checking = {} after charged_copy  (unchanged)\n", checking);
	

	std::println("");
	std::println("");
	std::println("");


	//Pass by reference
	double savings{ 100.0 };
	std::println("savings = {} before charge", savings);
	charge(savings, 15.0);
	std::println("savings = {} after charge  (charged)", savings);


}