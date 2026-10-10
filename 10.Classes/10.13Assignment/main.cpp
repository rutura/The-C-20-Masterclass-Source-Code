#include <cstddef>
#include <format>
#include <memory>
#include <print>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

/*
    Chapter 10 assignment - Classes

    Eight small classes for the weather station. Each exercise asks for ONE
    class, with its sample output below. Write the class ABOVE main(), and the
    lines that use it in main() under the exercise's heading.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - Data members are private. Mark every member function that does not
        change the object const.
      - No `new` and no `delete` in your answers, except in exercise 5, where
        the whole point is to write them correctly.
*/

// Write your classes here, above main().


int main() {

    /*
        Exercise 1 - a class that protects its data

        Write class Thermometer with one private member, `celsius_` (a double,
        starting at 0.0), and these public members:

            bool set_celsius(double celsius);       // false and no change if below -273.15
            double celsius() const;
            double fahrenheit() const;              // celsius * 9 / 5 + 32

        -273.15 is absolute zero: no temperature can be lower. A value below
        it must be refused, leaving the old value in place.

        Set 21.5 and print the temperature in both scales. Then try -300,
        print whether it was accepted, and print the temperature again.

        Sample output:
            21.5 C = 70.7 F
            set_celsius(-300): rejected, still 21.5 C
    */
    std::println("--- Exercise 1: Thermometer ---");
    // TODO


    /*
        Exercise 2 - constructors

        Write class Alarm with private members:

            const int id_;
            std::string name_;
            double threshold_{30.0};

        and these constructors, using member initializer lists, with the two
        shorter ones DELEGATING to the full one:

            Alarm(int id, const std::string& name, double threshold);
            Alarm(int id, const std::string& name);       // threshold 30.0
            Alarm();                                      // id 0, name "unnamed"

        and a function `std::string describe() const` returning text like
        "Alarm #7 'hot' triggers above 35.0" (std::format with {:.1f}).

        Make one Alarm with each constructor and print its describe().

        Sample output:
            Alarm #7 'hot' triggers above 35.0
            Alarm #8 'default-level' triggers above 30.0
            Alarm #0 'unnamed' triggers above 30.0
    */
    std::println("--- Exercise 2: Alarm ---");
    // TODO


    /*
        Exercise 3 - const member functions and mutable

        Write class Lookup holding a std::vector<int> of values, with:

            void add(int value);
            int get(std::size_t index) const;         // returns the value, and counts the read
            std::size_t reads() const;                // how many times get() has been called

        get() must be const, and still count its calls: that needs a member
        that is `mutable`.

        Then write a FREE function

            void print_all(const Lookup& lookup, std::size_t count);

        that prints the first `count` values using get(). Because its parameter
        is a const reference, it can only compile if get() is const.

        Add 10, 20, 30, call print_all for all three, then print reads().

        Sample output:
            10 20 30
            reads: 3
    */
    std::println("--- Exercise 3: Lookup ---");
    // TODO


    /*
        Exercise 4 - RAII

        Write class ScopeLabel whose constructor prints "enter <name>" and whose
        destructor prints "leave <name>". It takes the name as a std::string and
        must remember it.

        Use it to show the order of construction and destruction:

          a) two nested scopes in main, "outer" and "inner":
                { ScopeLabel outer{"outer"}; { ScopeLabel inner{"inner"}; } }

          b) a function  void work(bool bail_out)  that creates a ScopeLabel
             "work", and returns immediately if bail_out is true, otherwise
             prints "working". Call it with true.

        Sample output:
            enter outer
            enter inner
            leave inner
            leave outer
            enter work
            leave work
    */
    std::println("--- Exercise 4: ScopeLabel ---");
    // TODO


    /*
        Exercise 5 - the rule of five

        Write class Buffer that OWNS a heap block of ints:

            explicit Buffer(std::size_t size);       // new int[size]{}, all zeros
            ~Buffer();                               // delete[]
            Buffer(const Buffer& other);             // deep copy
            Buffer& operator=(const Buffer& other);  // deep copy, safe for b = b
            Buffer(Buffer&& other) noexcept;         // steal, leave `other` empty
            Buffer& operator=(Buffer&& other) noexcept;

            int get(std::size_t index) const;
            void set(std::size_t index, int value);
            std::size_t size() const;

        Use std::exchange (<utility>) in the move operations, as in 10.8. Then:

            Buffer a{3};   a.set(0, 7);
            Buffer b{a};            // copy
            b.set(0, 99);
            Buffer c{std::move(a)}; // move

        and print what you find.

        Sample output:
            copy: b[0] = 99, original a[0] = 7
            moved c: size 3, c[0] = 7, a (moved-from) size 0
    */
    std::println("--- Exercise 5: Buffer ---");
    // TODO


    /*
        Exercise 6 - the rule of zero

        Write class SafeBuffer with the same interface as Buffer (constructor
        from a size, get, set, size), but storing a std::vector<int> and
        writing NO destructor, NO copy and NO move operations.

        Then print the answers the compiler gives about it, with
        std::is_copy_constructible_v and std::is_nothrow_move_constructible_v
        (from <type_traits>).

        Sample output:
            SafeBuffer copyable: true, nothrow movable: true
    */
    std::println("--- Exercise 6: SafeBuffer ---");
    // TODO


    /*
        Exercise 7 - static and this

        Write class Ticket that gives every ticket a unique, increasing number:

            static inline int issued_{0};             // how many tickets exist
            int number_;                              // this ticket's number
            std::string note_;

            explicit Ticket(const std::string& note); // takes the next number
            Ticket& with_note(const std::string& note);   // replaces the note, returns *this
            static int issued();
            std::string describe() const;             // "ticket 1: 'storm warning'"

        Tickets must NOT be copyable (= delete the copy constructor and the
        copy assignment): a copy would have the same number as the original.

        Make two tickets, "storm warning" and "hail", and then change the
        second one's note with a chained call: second.with_note("frost").
        Print both, then Ticket::issued().

        Sample output:
            ticket 1: 'storm warning'
            ticket 2: 'frost'
            issued so far: 2
    */
    std::println("--- Exercise 7: Ticket ---");
    // TODO


    /*
        Exercise 8 - composition and aggregates

        Write:

            struct Range { double low; double high; };      // an aggregate
            enum class Level { low, normal, high };

            std::string level_name(Level level);            // "low", "normal", "high"

        and class Gauge that HAS a name and a Range:

            Gauge(const std::string& name, Range range);
            Level classify(double value) const;      // low if below range.low,
                                                     // high if above range.high,
                                                     // otherwise normal
            Range range() const;

        Build the Range with designated initializers, {.low = 15.0, .high = 30.0}.
        Unpack the gauge's range into two variables with a structured binding
        (auto [low, high]{gauge.range()};) and print them. Then classify 10, 22
        and 35.

        Sample output:
            range 15 to 30
            10 -> low
            22 -> normal
            35 -> high
    */
    std::println("--- Exercise 8: Gauge ---");
    // TODO

    return 0;
}
