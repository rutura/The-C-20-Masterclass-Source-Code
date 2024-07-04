module;

export module create_namespace;

const double adjustment{ 0.724 };

namespace No_Adjust {
    export double add(double x, double y) { return x + y; }
}// namespace No_Adjust

namespace Adjust {
    export double add(double x, double y) { return x + y - adjustment; }
}// namespace Adjust


//Declarations
namespace No_Adjust {
export double mult(double x, double y);// Declarations
export double div(double x, double y);

}// namespace No_Adjust

namespace Adjust {
export double mult(double x, double y);// Declarations
export double div(double x, double y);
}// namespace Adjust


//Definitions
namespace No_Adjust {
    //The export keyword is not needed on definitions. But you can put it there.
    double mult(double x, double y) { return x * y; }
    double div(double x, double y) { return x / y; }

}// namespace No_Adjust

namespace Adjust {
    double mult(double x, double y) { return x * y - adjustment; }
    double div(double x, double y) { return x / y - adjustment; }
}// namespace Adjust
