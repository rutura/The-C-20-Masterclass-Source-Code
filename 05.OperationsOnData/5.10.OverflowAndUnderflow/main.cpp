#include <print>
#include <limits>

int main() {

    // 5.8 showed how to ask a type exactly how far it can stretch with
    // std::numeric_limits. Overflow and underflow are what actually happens
    // once a value tries to go past those limits.

    // An unsigned char (0-255) tracking, say, a loyalty-point counter that's
    // capped low on purpose: push it past its max and it wraps back around
    // to 0 instead of becoming 256 - it never signals an error.
    unsigned char loyaltyPoints{std::numeric_limits<unsigned char>::max()}; // 255
    std::println("loyaltyPoints             : {}", static_cast<int>(loyaltyPoints));

    ++loyaltyPoints; // overflow: wraps around
    std::println("loyaltyPoints after +1    : {}", static_cast<int>(loyaltyPoints)); // 0

    ++loyaltyPoints;
    std::println("loyaltyPoints after +2    : {}", static_cast<int>(loyaltyPoints)); // 1

    // Underflow is the same idea in the other direction: go below a type's
    // minimum and it wraps back around to the top instead of going negative.
    unsigned char redemptionsLeft{0};
    std::println("");
    std::println("redemptionsLeft           : {}", static_cast<int>(redemptionsLeft));

    --redemptionsLeft; // underflow: wraps around
    std::println("redemptionsLeft after -1  : {}", static_cast<int>(redemptionsLeft)); // 255

    // This is exactly the danger flagged back in 4.3 with unsigned
    // subtraction ("receiptsOnFile - 300") - overflow/underflow is the
    // general rule that mistake is a symptom of: unsigned types never go
    // out of range, they just wrap, silently, with no warning at runtime.
    unsigned int receiptsOnFile{250};
    unsigned int receiptsAfterVoiding{receiptsOnFile - 300}; // underflows
    std::println("");
    std::println("receiptsAfterVoiding      : {} (wrapped, not -50)", receiptsAfterVoiding);

    return 0;
}
