#include <iostream>
#include <print>

int main(){

    // switch compares one integer (or char, or enum) against a list of
    // constant `case` labels and jumps to the match. It's the natural
    // fit when you're branching on many discrete values of a single
    // expression - clearer than a long else-if ladder doing the same.

    int one_star{ 0 };
    int two_star{ 0 }; 
    int three_star{ 0 }; 
    int four_star{ 0 }; 
    int five_star{ 0 }; 

    std::print("Enter a review score (0-100), -1 to stop: ");
    int score{};

    while (std::cin >> score && score != -1) {

        int bucket{ score / 20 };


        switch (bucket) {
        case 0:
            ++one_star;
            break;
        case 1:
            ++two_star;
            break;
        case 2:
            ++three_star;
            break;
        case 3:
            ++four_star;
            break;
        case 4:
        case 5:
            ++five_star;
            break;
        default:
            std::println("  ignoring out-of-range score {}", score);
            break;
        }

        /*
        if (bucket == 0) {
            ++one_star;
        }
        else if (bucket == 1) {
            ++two_star;
        }
        else if (bucket == 2) {
            ++three_star;
        }
        else if (bucket == 3) {
            ++four_star;
        }
        else if (bucket == 4 || bucket == 5) {
            ++five_star;
        }
        else {
            std::println("  ignoring out-of-range score {}", score);
        }
        */

        std::print("Enter a review score (0-100), -1 to stop: ");
    }

    std::println("\n1 star : {}\n2 star : {}\n3 star : {}\n4 star : {}\n5 star : {}",
        one_star, two_star, three_star, four_star, five_star);


}