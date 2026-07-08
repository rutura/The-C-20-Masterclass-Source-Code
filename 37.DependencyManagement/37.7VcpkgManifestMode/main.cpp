#include <fmt/core.h>
#include <nlohmann/json.hpp>

int main(){

	// Two dependencies declared in one manifest, both installed by the same
	// single vcpkg install step at configure time -- this is what manifest
	// mode scales to on a real project: a growing vcpkg.json instead of a
	// growing list of manually-run install commands.
	nlohmann::json config;
	config["library"] = "fmt";
	config["installed_via"] = "vcpkg manifest mode";

	fmt::print("{}\n", config.dump(2));

	return 0;
}
