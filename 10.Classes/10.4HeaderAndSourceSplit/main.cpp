#include <print>

#include "sensor.h"

// main.cpp sees only the declaration in sensor.h. It is compiled without ever
// looking at sensor.cpp, and the linker joins the two afterwards, exactly as
// in 6.11 and 7.12. If you change a function BODY in sensor.cpp, only that one
// file needs recompiling. If you change sensor.h, everything that includes it
// does.
int main() {

    Sensor north{12, "north", 1.5};
    Sensor east{13, "east"};

    std::println("{}", north.describe());
    std::println("{}", east.describe());

    east.set_offset(-2.0);
    std::println("{}", east.describe());

    // The caller cannot tell, and does not need to, which functions were
    // written inside the class and which in sensor.cpp.
    std::println("id of north: {}", north.id());
    std::println("a raw 70.0 from north reads {:.1f}", north.calibrated(70.0));

    return 0;
}
