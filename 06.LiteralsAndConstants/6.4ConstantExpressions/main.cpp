#include <fmt/format.h>

/*
 * - Added mathematical constants
 * - Changed the output stream to fmt's
 * cppreference:
 * Mathematical reference: https://en.cppreference.com/w/cpp/numeric/constants
 * constexpr: https://en.cppreference.com/w/cpp/language/constexpr
 */
int main(){

	constexpr int SOME_LIB_MAJOR_VERSION {1237};
	
	constexpr int eye_count {2};
	
	constexpr double PI {3.14};

    //eye_count = 4;
	fmt::println("eye count: {}", eye_count);
	fmt::println("PI: {}", PI);


	//int leg_count {2}; // Non constexpr
	                    // leg_count is not known at compile time
	//constexpr int arm_count{leg_count}; // Error 


	constexpr int room_count{10};
	constexpr int door_count{room_count};// OK
	
	const int table_count{5};
	constexpr int chair_count{ table_count * 5};// Works


   // static_assert( SOME_LIB_MAJOR_VERSION == 123);

   // int age = 5;
   // static_assert( age == 5);

	fmt::println("App doing its thing...");

	/*
	 * Mathematical constants
	 */
	using namespace std::numbers;
	fmt::println("e_v: {}, log2e_v: {}, log10e_v: {}", e_v, log2e_v, log10e_v);
	fmt::println("phi_v: {}, egamma_v: {}, inv_sqrt3_v: {}", phi_v, egamma_v, inv_sqrt3_v);
    return 0;
}