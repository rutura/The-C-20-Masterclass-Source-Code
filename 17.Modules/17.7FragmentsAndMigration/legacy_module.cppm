// A module that WRAPS an existing header: step one of a migration.
module;

#include "legacy.h"                  // global module fragment: the header, as it is

export module legacy;

// A using-declaration brings a name from another scope into this one. Written
// with `export`, it makes the name part of the module's interface. `::name`
// means "the one in the global scope", where the header declared it.
export using ::Calibration;
export using ::celsius_to_kelvin;
export using ::apply;

// The macro LEGACY_VERSION came with the header, but macros are never exported:
// importers of `legacy` do not see it. If they need the value, export a constant.
export constexpr int legacy_version{LEGACY_VERSION};
