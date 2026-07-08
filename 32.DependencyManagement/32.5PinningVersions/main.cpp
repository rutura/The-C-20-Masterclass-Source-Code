#include <fmt/core.h>

int main(){

	// The point of this lecture lives in CMakeLists.txt, not here -- but we
	// still want something real to build against fmt, since "pin your
	// dependency versions" is meaningless without an actual dependency.
	fmt::print("Built against a pinned fmt version -- see CMakeLists.txt\n");

	return 0;
}
