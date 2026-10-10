#pragma once

#include <cstdint>

// A colour is plain data with no rules to protect: any three bytes are a
// valid colour. So it is an aggregate, a struct (10.11), initialized by
// listing the values or by naming them:
//
//     Color orange{240, 140, 40};
//     Color blue{.r = 20, .g = 30, .b = 90};
struct Color {
    std::uint8_t r{0};
    std::uint8_t g{0};
    std::uint8_t b{0};
};
