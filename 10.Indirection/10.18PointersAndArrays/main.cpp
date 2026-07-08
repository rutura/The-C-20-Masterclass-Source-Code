#include <print>

int main() {

    int scores[10]{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    int* p_score{scores}; // an array decays to a pointer to its first element

    std::println("scores : {}", static_cast<const void*>(scores));
    std::println("p_score : {}", static_cast<const void*>(p_score));
    std::println("&scores[0] : {}", static_cast<const void*>(&scores[0]));

    std::println("");
    std::println("Printing out data at array address : ");
    std::println("*scores : {}", *scores);
    std::println("scores[0] : {}", scores[0]);
    std::println("*p_score : {}", *p_score);
    std::println("p_score[0] : {}", p_score[0]);

    // Differences: p_score can be reassigned to point elsewhere, but the
    // array name itself can't - "scores" isn't a variable holding an
    // address, it's a fixed label for the whole array.
    int number{21};
    p_score = &number;

    // scores = &number; // compiler error: "incompatible types in
    // assignment of 'int*' to 'int[10]'" - the array name is a special
    // kind of pointer-like expression that identifies the whole array, not
    // a real, reassignable pointer variable.

    std::println("p_score : {}", static_cast<const void*>(p_score));

    // std::size() only works on the actual array - a decayed pointer has
    // lost the size information the compiler would need.
    std::println("size : {}", std::size(scores));
    // std::println("size : {}", std::size(p_score)); // compiler error

    return 0;
}
