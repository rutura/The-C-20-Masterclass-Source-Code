import <iostream>;
import math;

//Using exported concept
template <Multipliable T>
T my_add(T a, T b)
{
	return a + b;
}

int main()
{
	//Add two numbers using my_add
	std::cout << my_add(1, 2) << std::endl;

	const char* str1{ "Hello" };
	const char* str2{ "World" };

	//Try to add two strings using my_add
	//std::cout << my_add(str1, str2) << std::endl;

	//Print the version from the math module
	std::cout << "Math version: " << VERSION << std::endl;

}
