#include <fmt/format.h>

/*
 *cppreference: https://en.cppreference.com/w/cpp/language/explicit_cast
 *
 */

struct Interface {
	virtual void interface_func() = 0;
};
struct InterfaceImpl: Interface {
	void interface_func() override {
		fmt::println("{}", __PRETTY_FUNCTION__);
	}
};
struct ConstCastTestClass {
	void setVal(int newVal) const {// making this member func const makes its members readonly(const)
		const_cast<ConstCastTestClass*>(this)->val = newVal;// removing const in order to write
	}
	[[nodiscard]] auto getVal()const  {
		return val;
	}
private:
	int val{};
};

int main(){

	//Implicit cast will add up the doubles,
	//then turn result into int for assignment
	double x { 12.5 };
    double y { 34.6};

    int sum = x + y; 

	fmt::println("The sum is: {}", sum);

	//Explicity cast : cast then sum up
	sum = static_cast<int>(x) + static_cast<int>(y) ;
	fmt::println("The sum is: {}", sum);

	//Explicit cast : sum up then cast, same thing as implicit cast
	sum =  static_cast<int> (x + y);
	fmt::println("Sum up then cast, result: {}", sum);

	//Old style C-cast
	double PI {3.14};
	
	//int int_pi = (int)(PI);
    int int_pi = static_cast<int>(PI);
	fmt::println("PI: {}", PI);
	fmt::println("int_pi: {}", int_pi);

	// static cast with classes
	InterfaceImpl(interface_impl);
	Interface& interface = interface_impl;
	static_cast<InterfaceImpl&>(interface);// downcast to child
	interface.interface_func();

	//reinterpret-cast
	Interface* new_interface = reinterpret_cast<Interface *>(&interface_impl);
	new_interface->interface_func();

	// const cast
	const int val1 = 32;
	int val2 = 33;

	ConstCastTestClass(const_cast_test);
	const_cast_test.setVal(val1);
	fmt::println("ConstCastTestClass val:{}", const_cast_test.getVal());
	const_cast_test.setVal(val2);
	fmt::println("ConstCastTestClass val after set:{}", const_cast_test.getVal());

    return 0;
}