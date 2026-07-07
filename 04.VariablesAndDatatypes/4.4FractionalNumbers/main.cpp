#include <print>

int main() {

    // Not every arcade stat is a whole number - accuracy and reaction time
    // need a fractional part. C++ has three floating-point types for that,
    // each trading off size for precision.

    float accuracyPercent{93.3333333333333f};   // ~7 significant digits
    double reactionTimeSeconds{0.185185185185}; // ~15-16 significant digits
    long double preciseAverage{93.3333333333333333L};

    std::println("sizeof(float)      : {}", sizeof(float));
    std::println("sizeof(double)     : {}", sizeof(double));
    std::println("sizeof(long double): {}", sizeof(long double));

    // {:.15f} asks std::println to print 15 digits after the decimal point,
    // which exposes each type's real precision limit.
    std::println("accuracyPercent    : {:.15f}", accuracyPercent);
    std::println("reactionTimeSeconds: {:.15f}", reactionTimeSeconds);
    std::println("preciseAverage     : {:.15f}", preciseAverage);

    // float's limited precision is why it's a poor fit for a running total -
    // this "obviously wrong" digit drift is the classic symptom.
    float totalCoinsValue = 1'924'000.23f; // looks fine printed normally...
    std::println("totalCoinsValue    : {:.5f}", totalCoinsValue); // ...but isn't, at this precision

    // Scientific notation is handy once numbers get very large or very small -
    // like the odds of a perfect run, or a frame time measured in seconds.
    std::println("");
    double perfectRunOdds{3.498e-11};   // 3.498 * 10^-11
    double crowdAtLaunch{1.924e8};      // 1.924 * 10^8
    std::println("perfectRunOdds : {}", perfectRunOdds);
    std::println("crowdAtLaunch  : {}", crowdAtLaunch);

    // Dividing by zero doesn't crash for floating-point types the way it does
    // for integers - it produces special values instead: infinity and NaN
    // ("not a number"), both worth recognizing if a stat ever looks broken.
    std::println("");
    double zero{};
    double bestReactionTime{-5.6};

    double infinityResult{bestReactionTime / zero};
    std::println("{} / {} = {}", bestReactionTime, zero, infinityResult);

    double nanResult{zero / zero};
    std::println("{} / {} = {}", zero, zero, nanResult);

    return 0;
}
