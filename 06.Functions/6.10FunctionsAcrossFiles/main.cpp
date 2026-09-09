#include <print>

// These bring in DECLARATIONS, not code. After the #include, the
// compiler knows how to call circle_area(), add_tax(), and the rest -
// enough to type-check every call below and emit main.o with "unresolved"
// slots where those calls are. The LINKER fills those slots from
// geometry.o and money.o.
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
