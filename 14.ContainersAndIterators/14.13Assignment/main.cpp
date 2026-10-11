#include <cstddef>
#include <functional>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <print>
#include <queue>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>

/*
    Chapter 14 assignment - Containers and iterators

    Eight small jobs for the weather station, one container idea each. Write
    the functions and classes ABOVE main(), and the lines that use them in
    main() under the exercise's heading.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`
      - Use the container whose strengths fit the job (14.11), not always a vector.
*/

// Write your functions and classes here, above main().


int main() {

    /*
        Exercise 1 - iterators by hand

        With readings {18.5, 21.5, 19.0, 23.5, 20.0}: find the highest reading
        WITHOUT std::max_element and WITHOUT a range-based for loop. Walk the
        vector with an iterator, remember the iterator to the highest element,
        and print the value and its index (use std::distance). Then print the
        readings backwards with the reverse iterators rbegin() and rend().

        Sample output:
            highest 23.5 at index 3
            backwards: 20 23.5 19 21.5 18.5
    */
    std::println("--- Exercise 1: iterators by hand ---");
    // TODO


    /*
        Exercise 2 - reserve

        Write int count_reallocations(bool reserve_first): it adds the numbers
        0 to 999 to a std::vector<int> with push_back, calling reserve(1000)
        first when the argument is true, and returns how many times capacity()
        changed AFTER that (compare it with the previous capacity after every
        push_back).

        Print the result with a reserve, and whether the result without one is
        at least 5 (the exact number depends on your standard library, 14.3).

        Sample output:
            with reserve: 0 reallocations after the reserve
            without reserve: at least 5? true
    */
    std::println("\n--- Exercise 2: reserve ---");
    // TODO


    /*
        Exercise 3 - erase while iterating

        From {4, -2, -5, 9, -1, 7, -8} remove every negative number with a
        loop over iterators (not std::erase_if, that is chapter 15). Use the
        iterator that erase() returns, and advance only when nothing was
        erased: note the two negatives in a row. Print what is left.

        Sample output:
            kept: 4 9 7
    */
    std::println("\n--- Exercise 3: erase while iterating ---");
    // TODO


    /*
        Exercise 4 - list and splice

        In a std::list<std::string> {"upload", "calibrate", "reboot", "report"}
        move the element "reboot" to the front WITHOUT copying or moving any
        string: use splice. Keep an iterator to "reboot" from before the move
        and print the element it points to afterwards: it is still valid
        (14.5).

        Sample output:
            before: upload calibrate reboot report
            after:  reboot upload calibrate report
            the iterator still points to: reboot
    */
    std::println("\n--- Exercise 4: list and splice ---");
    // TODO


    /*
        Exercise 5 - counting words with a map

        Count the words of "the north wind and the south wind and the west wind"
        (read them with a std::istringstream and operator>>) in a
        std::map<std::string, int>. Print each word with its count in
        alphabetical order, then the most frequent word. If two words tie, the
        one that comes first alphabetically wins.

        Sample output:
            and 2
            north 1
            south 1
            the 3
            west 1
            wind 3
            most frequent: the (3)
    */
    std::println("\n--- Exercise 5: counting words with a map ---");
    // TODO


    /*
        Exercise 6 - a hash for your own type

        Write struct Coordinate {int x; int y;} with a defaulted operator==
        and a std::hash specialization (14.7). A walker starts at (0, 0) and
        follows the moves "NNESSWW" (N is y+1, S is y-1, E is x+1, W is x-1).
        Keep the cells it has been to in a std::unordered_set<Coordinate>;
        stop at the first cell it has already visited (insert() tells you:
        its .second is false). Print where and at which step, then how many
        different cells were visited before that.

        Sample output:
            revisited (0, 0) at step 6
            distinct cells before the revisit: 6
    */
    std::println("\n--- Exercise 6: a hash for your own type ---");
    // TODO


    /*
        Exercise 7 - priority queue

        Write struct Task {int priority; std::string name;} and put these into a
        std::priority_queue: {2, "upload"}, {5, "alarm"}, {2, "calibrate"},
        {5, "battery"}, {1, "report"}. Higher priority comes out first; among
        equal priorities, the name that comes first alphabetically comes out
        first. You need a comparison of your own (14.8). Pop everything and
        print "[priority] name".

        Sample output:
            [5] alarm
            [5] battery
            [2] calibrate
            [2] upload
            [1] report
    */
    std::println("\n--- Exercise 7: priority queue ---");
    // TODO


    /*
        Exercise 8 - an iterator of your own

        Write class Strided: it is built from a const std::vector<int>& and a
        stride, and lets you walk every stride-th element with a range-based
        for loop. It needs begin() and end() returning a forward iterator (the
        pattern of 14.10: the five type names, a default constructor,
        operator*, prefix and postfix ++, ==). Let the iterator hold a
        position counted in elements of the VIEW (0, 1, 2, ...) and compute
        the real index as position * stride. Where does end() point for a
        vector of 10 elements and a stride of 3?

        With {1, ..., 10} and a stride of 3, print the elements, and their sum
        using std::accumulate on begin() and end().

        Sample output:
            every 3rd: 1 4 7 10
            sum: 22
    */
    std::println("\n--- Exercise 8: an iterator of your own ---");
    // TODO

    return 0;
}
