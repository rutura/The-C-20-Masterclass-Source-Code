#pragma once

const double adjustment{ 0.724 };

namespace No_Adjust {
double add(double x, double y) { return x + y; }
}// namespace No_Adjust

namespace Adjust {
double add(double x, double y) { return x + y - adjustment; }
}// namespace Adjust


//Declarations
namespace No_Adjust {
double mult(double x, double y);// Declarations
double div(double x, double y);

}// namespace No_Adjust

namespace Adjust {
double mult(double x, double y);// Declarations
double div(double x, double y);
}// namespace Adjust


//Definitions
namespace No_Adjust {
    double mult(double x, double y) { return x * y; }
    double div(double x, double y) { return x / y; }

}// namespace No_Adjust

namespace Adjust {
    double mult(double x, double y) { return x * y - adjustment; }
    double div(double x, double y) { return x / y - adjustment; }
}// namespace Adjust
