#include <print>

int main() {

    // A for loop packs the three pieces of a counter-controlled loop
    // into one header: initialization ; continuation condition ; update.
    //   for (int page{1}; page <= 10; ++page) { ... }
    //        \__________/  \_________/   \____/
    //           once       before each   after each
    //                      iteration     iteration

    // --- Read pages 1 through 10 ---
    for (int page{1}; page <= 10; ++page) {
        std::print("{} ", page);
    }
    std::println("");

    // --- Add up the left-hand (even) page numbers from 2 through 20 ---
    // The update step can be any expression - here it's += 2.
    int left_page_total{0};
    for (int page{2}; page <= 20; page += 2) {
        left_page_total += page;
    }
    std::println("Sum of left-hand pages 2..20: {}", left_page_total);

    // --- Count down the chapters left to read ---
    for (int chapters_left{5}; chapters_left >= 1; --chapters_left) {
        std::print("{} to go... ", chapters_left);
    }
    std::println("done!");

    // --- One row per chapter: chapter N has N sections ---
    int sections_read{0};
    for (int chapter{1}; chapter <= 5; ++chapter) {
        for (int section{1}; section <= chapter; ++section) {
            ++sections_read;
        }
        std::println("After chapter {}: {} sections read", chapter, sections_read);
    }

    // The loop variable's scope is the loop body: `page`, `chapters_left`,
    // `chapter`, `section` are each gone once their loop ends.

    return 0;
}
