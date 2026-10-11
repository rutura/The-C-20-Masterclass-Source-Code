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

// ---- Exercise 2 ------------------------------------------------------------

int count_reallocations(bool reserve_first) {
    std::vector<int> values;
    if (reserve_first) {
        values.reserve(1'000);
    }
    std::size_t capacity{values.capacity()};
    int changes{0};
    for (int i{0}; i < 1'000; ++i) {
        values.push_back(i);
        if (values.capacity() != capacity) {
            capacity = values.capacity();
            ++changes;
        }
    }
    return changes;
}

// ---- Exercise 6 ------------------------------------------------------------

struct Coordinate {
    int x;
    int y;
    bool operator==(const Coordinate&) const = default;
};

template <>
struct std::hash<Coordinate> {
    std::size_t operator()(const Coordinate& cell) const noexcept {
        return std::hash<int>{}(cell.x) * 31 + std::hash<int>{}(cell.y);
    }
};

// ---- Exercise 7 ------------------------------------------------------------

struct Task {
    int priority;
    std::string name;
};

// ---- Exercise 8 ------------------------------------------------------------

class Strided {
public:
    Strided(const std::vector<int>& data, std::size_t stride) : data_{&data}, stride_{stride} {}

    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = int;
        using difference_type = std::ptrdiff_t;
        using pointer = const int*;
        using reference = const int&;

        const_iterator() = default;
        const_iterator(const Strided* owner, std::size_t position) : owner_{owner}, position_{position} {}

        reference operator*() const { return (*owner_->data_)[position_ * owner_->stride_]; }
        const_iterator& operator++() {
            ++position_;
            return *this;
        }
        const_iterator operator++(int) {
            const_iterator before{*this};
            ++position_;
            return before;
        }
        friend bool operator==(const const_iterator&, const const_iterator&) = default;

    private:
        const Strided* owner_{nullptr};
        std::size_t position_{0};
    };

    const_iterator begin() const { return const_iterator{this, 0}; }
    const_iterator end() const { return const_iterator{this, (data_->size() + stride_ - 1) / stride_}; }

private:
    const std::vector<int>* data_;
    std::size_t stride_;
};

int main() {

    std::println("--- Exercise 1: iterators by hand ---");
    std::vector<double> readings{18.5, 21.5, 19.0, 23.5, 20.0};
    auto highest{readings.begin()};
    for (auto it{readings.begin()}; it != readings.end(); ++it) {
        if (*it > *highest) {
            highest = it;
        }
    }
    std::println("highest {} at index {}", *highest, std::distance(readings.begin(), highest));
    std::print("backwards:");
    for (auto it{readings.rbegin()}; it != readings.rend(); ++it) {
        std::print(" {}", *it);
    }
    std::println();

    std::println("\n--- Exercise 2: reserve ---");
    std::println("with reserve: {} reallocations after the reserve", count_reallocations(true));
    std::println("without reserve: at least 5? {}", count_reallocations(false) >= 5);

    std::println("\n--- Exercise 3: erase while iterating ---");
    std::vector<int> temperatures{4, -2, -5, 9, -1, 7, -8};
    for (auto it{temperatures.begin()}; it != temperatures.end();) {
        if (*it < 0) {
            it = temperatures.erase(it);
        } else {
            ++it;
        }
    }
    std::print("kept:");
    for (int t : temperatures) {
        std::print(" {}", t);
    }
    std::println();

    std::println("\n--- Exercise 4: list and splice ---");
    std::list<std::string> jobs{"upload", "calibrate", "reboot", "report"};
    std::print("before:");
    for (const auto& job : jobs) {
        std::print(" {}", job);
    }
    std::println();
    auto reboot{std::next(jobs.begin(), 2)};
    jobs.splice(jobs.begin(), jobs, reboot);
    std::print("after: ");
    for (const auto& job : jobs) {
        std::print(" {}", job);
    }
    std::println();
    std::println("the iterator still points to: {}", *reboot);

    std::println("\n--- Exercise 5: counting words with a map ---");
    std::istringstream sentence{"the north wind and the south wind and the west wind"};
    std::map<std::string, int> words;
    std::string word;
    while (sentence >> word) {
        ++words[word];
    }
    auto most{words.begin()};
    for (auto it{words.begin()}; it != words.end(); ++it) {
        std::println("{} {}", it->first, it->second);
        if (it->second > most->second) {
            most = it;
        }
    }
    std::println("most frequent: {} ({})", most->first, most->second);

    std::println("\n--- Exercise 6: a hash for your own type ---");
    std::unordered_set<Coordinate> visited;
    Coordinate position{0, 0};
    visited.insert(position);
    int step{0};
    for (char move : std::string{"NNESSWW"}) {
        ++step;
        switch (move) {
            case 'N': ++position.y; break;
            case 'S': --position.y; break;
            case 'E': ++position.x; break;
            case 'W': --position.x; break;
            default: break;
        }
        if (!visited.insert(position).second) {
            std::println("revisited ({}, {}) at step {}", position.x, position.y, step);
            break;
        }
    }
    std::println("distinct cells before the revisit: {}", visited.size());

    std::println("\n--- Exercise 7: priority queue ---");
    auto comes_after{[](const Task& a, const Task& b) {
        return a.priority != b.priority ? a.priority < b.priority : a.name > b.name;
    }};
    std::priority_queue<Task, std::vector<Task>, decltype(comes_after)> tasks{comes_after};
    tasks.push({2, "upload"});
    tasks.push({5, "alarm"});
    tasks.push({2, "calibrate"});
    tasks.push({5, "battery"});
    tasks.push({1, "report"});
    while (!tasks.empty()) {
        std::println("[{}] {}", tasks.top().priority, tasks.top().name);
        tasks.pop();
    }

    std::println("\n--- Exercise 8: an iterator of your own ---");
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Strided every_third{numbers, 3};
    std::print("every 3rd:");
    for (int n : every_third) {
        std::print(" {}", n);
    }
    std::println();
    std::println("sum: {}", std::accumulate(every_third.begin(), every_third.end(), 0));
    return 0;
}
