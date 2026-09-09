#include <print>

// The headers now live in geometry/ and finance/, but these #includes
// use the BARE file names - no "geometry/..." prefix. That works because
// the CMakeLists.txt adds those two folders to the compiler's header
// search path with target_include_directories().
#include "geometry.h"
#include "money.h"

int main() {

    const double radius{2.0};
    std::println("circle r={}: area {:.2f}, circumference {:.2f}",
                 radius, circle_area(radius), circle_circumference(radius));

    const double price{50.0};
    std::println("price {}: with 20% tax {:.2f}, then 15% off {:.2f}",
                 price,
                 add_tax(price, 0.20),
                 apply_discount(add_tax(price, 0.20), 15.0));

    return 0;
}
