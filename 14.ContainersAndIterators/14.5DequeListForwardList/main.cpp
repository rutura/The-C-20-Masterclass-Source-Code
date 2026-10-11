#include <deque>
#include <forward_list>
#include <list>
#include <print>
#include <string>

// A queue of jobs for the weather station: new urgent ones go to the FRONT.

int main() {

    // vector: one block. Cheap at the back, expensive at the front.
    // deque ("deck", double-ended queue): many fixed-size blocks plus an index
    // of them. Cheap at BOTH ends, and still random access.
    //
    //   vector     [ a b c d e . . . ]          one block
    //   deque      [*]──► [ a b c ]
    //              [*]──► [ d e f ]             a table of blocks
    //              [*]──► [ g . . ]
    //
    std::println("--- deque: both ends");
    std::deque<std::string> jobs;
    jobs.push_back("upload");
    jobs.push_back("calibrate");
    jobs.push_front("ALARM");                 // vector has no push_front
    jobs.push_front("shutdown");
    for (const auto& job : jobs) {
        std::print("{} ", job);
    }
    std::println();
    std::println("jobs[2] = {}   (random access, like a vector)", jobs[2]);
    jobs.pop_front();
    std::println("after pop_front: {}", jobs.front());

    // list: every element is its own node with a pointer to the next and the
    // previous. No random access, but a node never moves once it exists.
    //
    //   list     [a]⇄[b]⇄[c]⇄[d]       each box is a separate allocation
    //
    std::println("\n--- list: nodes that never move");
    std::list<std::string> queue{"north", "east", "west"};
    auto east{++queue.begin()};               // an iterator to "east"
    const std::string* address{&*east};       // and a pointer to the element itself

    queue.push_front("far north");
    queue.insert(east, "north east");         // insert BEFORE east
    queue.push_back("south");
    std::println("still the same element: {} (iterator), {} (pointer)",
                 *east, address == &*east);

    // The same sequence of inserts on a vector may have moved everything.
    // Stable positions are the real reason to choose a list.

    std::println("\n--- list: splice moves nodes, nothing is copied");
    std::list<std::string> urgent{"fix antenna", "replace battery"};
    queue.splice(queue.begin(), urgent);      // moves ALL of urgent's nodes to the front
    std::println("urgent now has {} items, queue has {}", urgent.size(), queue.size());
    for (const auto& item : queue) {
        std::print("[{}] ", item);
    }
    std::println();

    queue.remove("north");                    // erases every element equal to "north"
    queue.sort();                             // std::sort needs random access; list has its own
    std::println("sorted, first is {}", queue.front());

    // forward_list: a list with only the "next" pointer. One pointer less per
    // node, no size(), no back(), and insertion goes AFTER a position.
    std::println("\n--- forward_list: the smallest");
    std::forward_list<int> ids{10, 20, 30};
    ids.push_front(5);
    auto after_first{ids.begin()};
    ids.insert_after(after_first, 7);         // 5 7 10 20 30
    for (int id : ids) {
        std::print("{} ", id);
    }
    std::println();
    return 0;
}
