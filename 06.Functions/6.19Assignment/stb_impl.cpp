// This one .cpp is where stb_image_write's function BODIES get compiled.
// The macro switches the header from "declarations only" to "declarations
// + definitions" for this single translation unit. Every other file that
// includes the header (without the macro) gets just the declarations.
//
// This is the standard single-header pattern: put the #define in exactly
// one .cpp, or you get "multiple definition" linker errors.

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
