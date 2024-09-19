#include "explicit_instantiation_declaration.h"

namespace explicit_instantiation_declaration{

    //Explicit template instantiation definitions
    template int add<int>(int, int);
    template class Point<int>;

}   // namespace explicit_instantiation_declaration