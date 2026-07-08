#include <print>
#include <memory>

template <typename T>
T largest(const T& a, const T& b){
	return (a > b) ? a : b;
}

// Uncommenting this call produces a genuinely long, hard-to-read template
// error: largest(3, 4.5) tries to deduce T as both int and double from the
// two arguments, and deduction fails with pages of compiler diagnostic
// about candidate templates and substitution failures. This is exactly the
// kind of error an AI assistant is good at summarizing -- "the templated
// function received two different types where it expected one" -- letting
// you skip the multi-page wall of text and get straight to the fix
// (explicit template argument, or matching argument types).
//
// int mixed = largest(3, 4.5);

int main(){

	std::println("largest(3, 7)     : {}", largest(3, 7));
	std::println("largest(3.5, 2.1) : {}", largest(3.5, 2.1));

	// Segfaults are the other classic "paste this into an assistant" moment.
	// Dereferencing a unique_ptr after it's been reset to nullptr is a real,
	// common bug shape, not a contrived one.
	std::unique_ptr<int> ptr = std::make_unique<int>(42);
	ptr.reset();

	// Uncommenting this line segfaults -- ptr no longer owns anything.
	// std::println("*ptr : {}", *ptr);

	std::println("ptr is null : {}", ptr == nullptr);

	return 0;
}
