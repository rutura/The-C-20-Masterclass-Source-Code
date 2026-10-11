#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <numeric>
#include <print>

// A fixed-size ring of the most recent readings (the idea of the ring buffer
// in the 9.12 project). When it is full, a new reading overwrites the oldest.
// The storage is circular, but a user should see "oldest to newest", and
// should be able to use range-based for and the standard algorithms on it.
// That takes an iterator.

template <std::size_t Capacity>
class RecentReadings {
public:
    void add(double value) {
        slots_[(start_ + size_) % Capacity] = value;
        if (size_ < Capacity) {
            ++size_;
        } else {
            start_ = (start_ + 1) % Capacity;          // full: the oldest is gone
        }
    }

    std::size_t size() const { return size_; }

    // The iterator remembers the ring and a LOGICAL position (0 is the oldest).
    // It knows how to turn that into the circular slot.
    class const_iterator {
    public:
        // These five names are what the standard algorithms look for.
        using iterator_category = std::forward_iterator_tag;
        using value_type = double;
        using difference_type = std::ptrdiff_t;
        using pointer = const double*;
        using reference = const double&;

        const_iterator() = default;                    // a forward iterator must be default constructible
        const_iterator(const RecentReadings* ring, std::size_t position)
            : ring_{ring}, position_{position} {}

        reference operator*() const {
            return ring_->slots_[(ring_->start_ + position_) % Capacity];
        }
        pointer operator->() const { return &**this; }

        const_iterator& operator++() {                 // prefix
            ++position_;
            return *this;
        }
        const_iterator operator++(int) {               // postfix: copy, then advance (12.3)
            const_iterator before{*this};
            ++position_;
            return before;
        }

        friend bool operator==(const const_iterator&, const const_iterator&) = default;

    private:
        const RecentReadings* ring_{nullptr};
        std::size_t position_{0};
    };

    const_iterator begin() const { return const_iterator{this, 0}; }
    const_iterator end() const { return const_iterator{this, size_}; }

private:
    std::array<double, Capacity> slots_{};
    std::size_t start_{0};
    std::size_t size_{0};
};

// The compiler can check that we built a real forward iterator.
static_assert(std::forward_iterator<RecentReadings<4>::const_iterator>);

int main() {

    RecentReadings<4> recent;
    for (double reading : {18.5, 19.0, 21.5}) {
        recent.add(reading);
    }

    std::println("--- a range-based for loop works (7.2)");
    for (double value : recent) {
        std::print("{} ", value);
    }
    std::println();

    // Two more readings than there is room for: the oldest are overwritten.
    recent.add(22.0);
    recent.add(23.5);
    std::println("\n--- after two more readings, the ring has wrapped");
    for (double value : recent) {
        std::print("{} ", value);                      // 19 21.5 22 23.5: oldest to newest
    }
    std::println();

    // And because it is a proper iterator pair, the algorithms accept it.
    std::println("\n--- the standard algorithms accept it");
    std::println("sum:     {}", std::accumulate(recent.begin(), recent.end(), 0.0));
    std::println("maximum: {}", *std::max_element(recent.begin(), recent.end()));
    std::println("count above 21: {}", std::count_if(recent.begin(), recent.end(),
                                                      [](double v) { return v > 21.0; }));
    auto found{std::find(recent.begin(), recent.end(), 22.0)};
    std::println("22.0 is at position {}", std::distance(recent.begin(), found));

    // What we left out: a random-access iterator also needs +, -, [], < and
    // more. Each one is a few lines, and the standard offers helpers (and C++20
    // concepts to check them). A forward iterator is the usual place to stop.
    return 0;
}
