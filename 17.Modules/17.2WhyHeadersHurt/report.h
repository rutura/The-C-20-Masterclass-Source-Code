#pragma once

// A header that uses std::string but forgot to include <string>. It compiles
// only when some other header, included earlier, happened to bring <string> in.
// Nothing in this file says so.
inline std::string label_for(double celsius) {
    return celsius > 20.0 ? "warm" : "cool";
}
