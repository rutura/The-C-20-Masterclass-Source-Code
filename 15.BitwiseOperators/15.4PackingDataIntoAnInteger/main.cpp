#include <print>
#include <cstdint>

int main() {

    // Sometimes several small values are packed into one larger integer -
    // a color is the classic example: four 0-255 channels (red, green,
    // blue, alpha) fit comfortably into one 32-bit value, 8 bits each.
    std::uint32_t red{0xAA};
    std::uint32_t green{0xBC};
    std::uint32_t blue{0xDE};
    std::uint32_t alpha{0x00};

    // Shift each channel into its byte position, then OR them all together.
    std::uint32_t packedColor = (red << 24) | (green << 16) | (blue << 8) | alpha;
    std::println("packedColor : {:#010x}", packedColor);

    // Unpacking reverses the process: mask out the byte of interest, then
    // shift it down to an ordinary 0-255 value.
    std::uint32_t redMask{0xFF000000};
    std::uint32_t greenMask{0x00FF0000};
    std::uint32_t blueMask{0x0000FF00};
    std::uint32_t alphaMask{0x000000FF};

    std::println("");
    std::println("red   : {:#04x}", (packedColor & redMask) >> 24);
    std::println("green : {:#04x}", (packedColor & greenMask) >> 16);
    std::println("blue  : {:#04x}", (packedColor & blueMask) >> 8);
    std::println("alpha : {:#04x}", (packedColor & alphaMask) >> 0);

    // The payoff: one std::uint32_t moves around as easily as any other
    // number - copied, compared, stored - while still carrying four
    // independent values inside it.

    return 0;
}
