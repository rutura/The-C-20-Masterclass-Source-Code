#include <print>

int main() {

    // Incrementing/decrementing a pointer moves it by sizeof(the pointed-to
    // type), not by one byte - ++p_score on an int* moves 4 bytes forward.
    int scores[10]{11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    int* p_score{scores};

    /*
    std::println("Values in scores array (p_score pointer increment) : ");

    std::println("Address : {} value : {}", static_cast<const void*>(p_score), *p_score);
    ++p_score;
    std::println("Address : {} value : {}", static_cast<const void*>(p_score), *p_score);
    ++p_score;
    std::println("Address : {} value : {}", static_cast<const void*>(p_score), *p_score);
    ++p_score;
    std::println("Address : {} value : {}", static_cast<const void*>(p_score), *p_score);
    */

    // Explicit addition of an integer moves by that many elements at once.
    /*
    p_score = scores;
    std::println("");
    std::println("Explicit addition of integer : ");
    std::println("scores[4] : {}", *(p_score + 4));
    */

    // A loop makes this much easier to work with than incrementing by hand.
    /*
    p_score = scores;
    std::println("");
    std::println("Pointer arithmetic on p_scores pointer and a for loop: ");
    for (size_t i{0}; i < std::size(scores); ++i) {
        std::println("Value : {}", *(p_score + i)); // same as scores[i]
    }
    */

    // The array name itself supports the same arithmetic as any pointer.
    /*
    std::println("");
    std::println("Pointer arithmetic on array name: ");
    for (size_t i{0}; i < std::size(scores); ++i) {
        std::println("Value : {}", *(scores + i));
    }
    */

    // Walking in reverse with array-index notation, using -1 since scores
    // already points at the first element.
    /*
    std::println("");
    std::println("Elements in reverse order with decrementing pointer arithmetic: ");
    for (size_t i{std::size(scores)}; i > 0; --i) {
        std::println("Value : {}", *(scores + i - 1));
    }
    */

    // Same walk, but decrementing a pointer directly instead of indexing.
    /*
    std::println("");
    std::println("Elements in reverse order -- arithmetic on the p_scores pointer: ");
    p_score = scores + std::size(scores) - 1;
    for (size_t i{std::size(scores)}; i > 0; --i) {
        std::println("Value : {}", *(p_score--));
    }
    */

    // The same reverse walk again, this time with plain array-index notation.
    /*
    std::println("");
    std::println("Elements in reverse order with array index notation: ");
    for (size_t i{std::size(scores)}; i > 0; --i) {
        std::println("Value : {}", scores[i - 1]);
    }
    */

    // Distance and comparison: two pointers into the same array can be
    // subtracted (giving the number of elements between them) and compared
    // with the usual relational operators - the further into the array,
    // the larger the address.
    int* pointer1{scores + 0};
    int* pointer2{scores + 8};

    std::println("");
    std::println("pointer2 - pointer1 : {}", pointer2 - pointer1); // 8
    std::println("pointer1 - pointer2 : {}", pointer1 - pointer2); // -8

    std::ptrdiff_t pos_diff = pointer2 - pointer1;
    std::ptrdiff_t neg_diff = pointer1 - pointer2;
    std::println("pointer2 - pointer1 (ptrdiff_t) : {}", pos_diff);
    std::println("pointer1 - pointer2 (ptrdiff_t) : {}", neg_diff);
    std::println("sizeof(std::ptrdiff_t) : {}", sizeof(std::ptrdiff_t));

    std::println("");
    std::println("pointer1 > pointer2 : {}", (pointer1 > pointer2));
    std::println("pointer1 < pointer2 : {}", (pointer1 < pointer2));
    std::println("pointer1 >= pointer2 : {}", (pointer1 >= pointer2));
    std::println("pointer1 <= pointer2 : {}", (pointer1 <= pointer2));
    std::println("pointer1 == pointer2 : {}", (pointer1 == pointer2));
    std::println("pointer1 != pointer2 : {}", (pointer1 != pointer2));

    p_score = scores;

    scores[0] = 31;          // array index notation
    *(scores + 1) = 32;      // same as scores[1] = 32, via pointer arithmetic on the array name
    *(p_score + 2) = 33;     // same as scores[2] = 33, via pointer arithmetic on p_score

    std::println("");
    std::println("Printing out the array after modification of 3 first elements: ");
    for (size_t i{0}; i < std::size(scores); ++i) {
        std::println("Value : {}", scores[i]);
    }

    return 0;
}
