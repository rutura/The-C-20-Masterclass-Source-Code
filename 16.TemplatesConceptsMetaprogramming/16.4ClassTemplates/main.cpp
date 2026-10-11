#include <cstddef>
#include <initializer_list>
#include <print>
#include <string>
#include <utility>
#include <vector>

// std::vector<int>, std::vector<double>, std::map<std::string, int> ...
// all the containers you use are CLASS TEMPLATES: one definition with the type
// left blank, and the compiler writes the class for each type you ask for.
// This lecture writes one.

// A history of what a station has measured: the values, in order.
// T is whatever is being measured: a temperature, a count, a station name.
template <typename T>
class History {
public:
    History() = default;

    // std::initializer_list<T> is the type of a braced list of values such as
    // {4, 12, 7}: it is how std::vector v{1, 2, 3} receives its elements. A
    // constructor that takes one lets you write History{4, 12, 7}, and it lets
    // the compiler DEDUCE T from the values (class template argument
    // deduction, 7.2).
    History(std::initializer_list<T> start) : items_{start} {}

    void add(const T& value) { items_.push_back(value); }
    std::size_t size() const { return items_.size(); }
    const T& latest() const { return items_.back(); }

    // A member function can be written outside the class. It then needs the
    // template header again, and the class name carries its parameter.
    const T& largest() const;

    // The mean needs T to be a number. Nothing says so: it simply will not
    // compile for a T that is not one. (And only if somebody calls it.)
    double mean() const {
        double total{0.0};
        for (const T& item : items_) {
            total += item;
        }
        return total / static_cast<double>(items_.size());
    }

private:
    std::vector<T> items_;
};

template <typename T>
const T& History<T>::largest() const {
    const T* best{&items_.front()};
    for (const T& item : items_) {
        if (*best < item) {
            best = &item;
        }
    }
    return *best;
}

// A second small class template, to show a deduction guide.
template <typename T>
class Box {
public:
    Box(T value) : value_{std::move(value)} {}
    const T& get() const { return value_; }

private:
    T value_;
};

// When the compiler deduces T from a string literal it picks const char*,
// which is rarely what you want. A DEDUCTION GUIDE says: for this argument,
// use this instantiation instead.
Box(const char*) -> Box<std::string>;

// A type with no operator< and no conversion to a number.
struct Note {
    std::string text;
};

int main() {

    std::println("--- one definition, one class per type");
    History<double> temperatures;                 // a History of doubles
    temperatures.add(18.5);
    temperatures.add(24.0);
    temperatures.add(21.5);
    std::println("temperatures: {} values, latest {}, largest {}, mean {:.2f}",
                 temperatures.size(), temperatures.latest(), temperatures.largest(), temperatures.mean());

    History<std::string> stations;                // a different class, made from the same template
    stations.add("north");
    stations.add("south");
    std::println("stations: {} names, latest {}, largest {}", stations.size(), stations.latest(), stations.largest());
    // stations.mean();                           // error, but only because it is CALLED: += on a string does not give a number

    // Only the member functions you call are compiled for a type. A Note has
    // no operator<, so largest() could not work for it, yet the class is fine:
    History<Note> notes;
    notes.add(Note{"check the battery"});
    std::println("notes: {} note, latest '{}'", notes.size(), notes.latest().text);
    // notes.largest();                           // error, reported inside largest(), at `*best < item`

    std::println("\n--- the compiler deduces T from the values");
    History counts{4, 12, 7};                     // History<int>
    History readings{18.5, 24.0};                 // History<double>
    std::println("counts has {} values, readings has {}", counts.size(), readings.size());
    counts.add(30);
    std::println("largest count: {}", counts.largest());

    std::println("\n--- a deduction guide");
    Box number{21.5};                             // Box<double>: deduced from the value
    Box name{"north"};                            // Box<std::string>, thanks to the guide
    std::println("number: {}   name: {} ({} letters)", number.get(), name.get(), name.get().size());
    // Without the guide, `name` would be a Box<const char*>, and name.get().size() would not compile.

    // Different instantiations are different, unrelated types:
    //     History<int> a;  History<double> b;  a = b;     // error
    // and each one has its own copy of any static member the template declares.
    return 0;
}
