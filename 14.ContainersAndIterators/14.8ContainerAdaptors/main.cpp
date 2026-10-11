#include <functional>
#include <map>
#include <print>
#include <queue>
#include <stack>
#include <string>
#include <utility>
#include <vector>

// stack, queue and priority_queue are not containers of their own. They are
// ADAPTORS: a small interface (the few operations that make sense) on top of
// a real container. No iterators, no begin() and end(): you only touch the
// ends, and to see everything you take elements out.

struct Alarm {
    int severity;
    std::string text;
};

int main() {

    // stack: last in, first out. push, top, pop. An undo list.
    std::println("--- stack (LIFO)");
    std::stack<std::string> undo;
    undo.push("set interval 30");
    undo.push("calibrate north");
    undo.push("reboot");
    std::println("size {}, top is '{}'", undo.size(), undo.top());
    while (!undo.empty()) {
        std::println("undoing: {}", undo.top());
        undo.pop();                              // pop returns nothing: read top() first
    }

    // queue: first in, first out. push at the back, front and pop at the front.
    std::println("\n--- queue (FIFO)");
    std::queue<std::string> uploads;
    uploads.push("north.dat");
    uploads.push("south.dat");
    uploads.push("east.dat");
    std::println("front '{}', back '{}'", uploads.front(), uploads.back());
    while (!uploads.empty()) {
        std::println("sending {}", uploads.front());
        uploads.pop();
    }

    // Both sit on a deque by default. A different container is the second
    // template argument, as long as it offers the operations the adaptor needs.
    std::stack<int, std::vector<int>> on_vector;
    on_vector.push(1);
    std::println("\na stack on a vector: top {}", on_vector.top());

    // priority_queue: the LARGEST element is always at the top. A binary heap
    // inside a vector: push and pop cost O(log n), top costs O(1).
    //
    //   push 5, 1, 8, 3     top() is 8, whatever the order of arrival
    //
    std::println("\n--- priority_queue");
    std::priority_queue<int> largest_first;
    for (int v : {5, 1, 8, 3}) {
        largest_first.push(v);
    }
    std::print("popping: ");
    while (!largest_first.empty()) {
        std::print("{} ", largest_first.top());
        largest_first.pop();
    }
    std::println();

    // std::greater turns it into a smallest-first queue (the third argument
    // is the container, the fourth is the comparison).
    std::priority_queue<int, std::vector<int>, std::greater<>> smallest_first;
    for (int v : {5, 1, 8, 3}) {
        smallest_first.push(v);
    }
    std::println("smallest first, top is {}", smallest_first.top());

    // Pairs compare field by field, so a pair of (count, name) sorts by count.
    std::println("\n--- the pair trick: who has the most readings?");
    std::map<std::string, int> counts{{"north", 40}, {"south", 12}, {"east", 31}, {"west", 7}, {"centre", 25}};
    std::priority_queue<std::pair<int, std::string>> ranking;
    for (const auto& [station, count] : counts) {
        ranking.push({count, station});
    }
    for (int place{1}; place <= 3; ++place) {
        std::println("{}. {} ({})", place, ranking.top().second, ranking.top().first);
        ranking.pop();
    }

    // Your own ordering: a comparison that says "a comes AFTER b" (a < b puts
    // a lower in the queue). decltype(x) is "the type of x".
    std::println("\n--- a comparison of your own");
    auto less_severe{[](const Alarm& a, const Alarm& b) { return a.severity < b.severity; }};
    std::priority_queue<Alarm, std::vector<Alarm>, decltype(less_severe)> alarms{less_severe};
    alarms.push({2, "low battery"});
    alarms.push({5, "sensor offline"});
    alarms.push({1, "clock drift"});
    alarms.push({4, "storm warning"});
    while (!alarms.empty()) {
        std::println("[{}] {}", alarms.top().severity, alarms.top().text);
        alarms.pop();
    }

    // Keeping only the K largest of a long stream: a SMALLEST-first queue of
    // size K. Every new value that beats the smallest replaces it.
    std::println("\n--- top 3 of a stream with a small heap");
    std::priority_queue<int, std::vector<int>, std::greater<>> best_three;
    for (int reading : {17, 29, 4, 31, 22, 8, 35, 19}) {
        best_three.push(reading);
        if (best_three.size() > 3) {
            best_three.pop();                    // drop the smallest of the four
        }
    }
    std::print("best three: ");
    while (!best_three.empty()) {
        std::print("{} ", best_three.top());
        best_three.pop();
    }
    std::println("(smallest first)");
    return 0;
}
