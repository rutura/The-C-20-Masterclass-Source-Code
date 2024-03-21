#include <fmt/format.h>

/*
 * - Changes the stream to fmt's
 * - Demonstrated more on the implicit conversions
 *  Cppreference: https://en.cppreference.com/w/cpp/language/implicit_conversion
 */
void func(double val) {//an int or any other variable when passed, is implicity converted to duoble
	fmt::println("val: {}", val);
}
double func2() {
	int val = 20;
	return val; // implicitly converted to double
}

struct ThisClass {
	operator int() const { return val; }
private:
	double val {20.5f};
};

int main(){

	//		. The compiler applies implicit conversions
	// 			when types are different in 
	//			an expression
	//		. Conversions are always done from the smallest
	//			to the largest type in this case int is 
	//			transformed to double before the expression
	//			is evaluated.Unless we are doing an assignment
	
	double price { 45.6 };
    int units {10};
    
    auto total_price = price * units; // units will be implicitly converted to double

	fmt::println("Total price: {}", total_price);
	fmt::println("Size of total price: {}", sizeof(total_price));

	//Implicit conversions in assignments
	// The assignment operation is going to cause an implicit
	// narrowing conversion , y is converted to int before assignment
	int x;
    double y {45.44};
    x = y; // double to int
	fmt::println("The value of x is : {}", x);// 45
	fmt::println("sizeof x: {}", sizeof(x)); // 4


	// function implicit ocnversion
	int val = 20;
	func(val);// val is implicitly converted to double

	double r_val = func2();

	fmt::println("returned val: {}", r_val);

	// switch case implicit coversios
	ThisClass this_class;
	switch (this_class) {
		case 20:
			fmt::println("Class value: 20");
		break;
		case 21:
			fmt::println("CLass value: 21");
			break;
		default:
			fmt::println("Failed to convert");
			break;
	}

	// if statement implicit conversions
	double my_val = 40.5f;
	if(my_val) {// if T2 is bool
		fmt::println("my_val implicitly converted");
	}

    return 0;
}