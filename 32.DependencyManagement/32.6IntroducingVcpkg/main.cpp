#include <fmt/core.h>

// Same fmt library as the FetchContent lectures -- what's different is
// where it comes from. vcpkg reads vcpkg.json (next to this file), installs
// fmt ahead of time, and find_package() in CMakeLists.txt locates the
// already-built package -- see docker/README.md's "Using vcpkg" section for
// the exact build command (it needs an extra -DCMAKE_TOOLCHAIN_FILE flag
// FetchContent never required).
int main(){

	fmt::print("fmt installed and found via vcpkg\n");

	return 0;
}
