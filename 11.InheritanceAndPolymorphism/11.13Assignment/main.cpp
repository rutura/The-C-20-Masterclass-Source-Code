#include <format>
#include <memory>
#include <print>
#include <string>
#include <variant>
#include <vector>

/*
    Chapter 11 assignment - Inheritance and polymorphism

    Eight small jobs for the weather station's instruments. Each exercise has
    a sample run below it. Write the classes ABOVE main(), and the lines that
    use them in main() under the exercise's heading.

    Rules:
      - Use std::print / std::println. Never std::cout, never std::endl.
      - Brace-initialize every variable: int n{0};  double x{1.5};
      - Qualify everything with std:: - no `using namespace std;`.
      - Mark every overriding function `override`.
      - Give every base class that is used through a pointer a virtual
        destructor.
      - No `new` and no `delete`: use std::make_unique and std::unique_ptr.
*/

// Provided for exercise 7. A small hierarchy, for you to take apart with
// dynamic_cast. You do not need to change it.
class Sensor {
public:
    virtual ~Sensor() = default;
    virtual std::string label() const { return "sensor"; }
};

class Thermometer : public Sensor {
public:
    std::string label() const override { return "thermometer"; }
};

class Anemometer : public Sensor {
public:
    explicit Anemometer(double gust) : gust_{gust} {}
    std::string label() const override { return "anemometer"; }
    double gust() const { return gust_; }                    // only an Anemometer has this

private:
    double gust_;
};

// Write your classes here, above main().


int main() {

    /*
        Exercise 1 - construction and destruction order

        Write class Instrument whose constructor takes a name and prints
        "  Instrument <name> built", and whose destructor prints
        "  Instrument <name> destroyed". Then write class Barometer, derived
        from Instrument with : public, whose constructor takes a name, passes
        it to the base constructor, and prints "  Barometer built"; its
        destructor prints "  Barometer destroyed".

        Create one Barometer called "roof" in main, inside its own { } scope.

        Sample output:
              Instrument roof built
              Barometer built
              Barometer destroyed
              Instrument roof destroyed
    */
    std::println("--- Exercise 1: construction order ---");
    // TODO


    /*
        Exercise 2 - virtual and override

        Write class Gauge with two VIRTUAL functions:

            virtual double read() const;               // returns 0.0
            virtual std::string unit() const;          // returns "units"

        and two derived classes, each overriding both, with `override`:

            class Thermometer2 : Gauge    reads 21.5, unit "C"
            class Barometer2   : Gauge    reads 1013.2, unit "hPa"

        (The "2" avoids a clash with the provided classes above.) Write a
        free function

            void show(const Gauge& gauge);       // prints "<read> <unit>"

        and call it with a Thermometer2, a Barometer2 and a plain Gauge. The
        function only knows about Gauge, yet each call must print its own
        object's values.

        Sample output:
            21.5 C
            1013.2 hPa
            0 units
    */
    std::println("--- Exercise 2: virtual and override ---");
    // TODO


    /*
        Exercise 3 - a polymorphic container

        Using the Gauge classes from exercise 2, build a
        std::vector<std::unique_ptr<Gauge>> holding two Thermometer2s and one
        Barometer2, created with std::make_unique. Loop over it ONCE, printing
        each gauge's unit and adding up the readings, then print the total.

        Sample output:
            C
            C
            hPa
            total: 1056.2
    */
    std::println("--- Exercise 3: a polymorphic container ---");
    // TODO


    /*
        Exercise 4 - an abstract class

        Write an abstract class Alarm with:

            virtual bool triggered(double value) const = 0;      // pure virtual
            virtual ~Alarm() = default;
            std::string name() const;                             // not virtual; returns the name

        and a constructor taking the name. Then write two concrete classes,
        each taking a name and a limit in its constructor:

            HighAlarm    triggered when value is ABOVE its limit
            LowAlarm     triggered when value is BELOW its limit

        Put one HighAlarm "heat" with limit 30 and one LowAlarm "frost" with
        limit 0 in a vector of unique_ptr<Alarm>. For the value 35.0, print
        each alarm's name and whether it triggered.

        Sample output:
            heat: triggered
            frost: quiet
    */
    std::println("--- Exercise 4: an abstract class ---");
    // TODO


    /*
        Exercise 5 - the virtual destructor

        Write class Base with a VIRTUAL destructor that prints "~Base", and
        class Derived : public Base whose destructor prints "~Derived". Hold a
        Derived in a std::unique_ptr<Base> (make_unique<Derived>) inside a
        { } scope, and let it go out of scope. Both destructors must run,
        Derived first.

        Then answer in a comment: what would have happened if ~Base were not
        virtual?

        Sample output:
            ~Derived
            ~Base
    */
    std::println("--- Exercise 5: the virtual destructor ---");
    // TODO


    /*
        Exercise 6 - slicing

        Using the Gauge classes from exercise 2:

            Thermometer2 thermometer;
            Gauge sliced{thermometer};                    // copies a Gauge out of it
            const Gauge& referenced{thermometer};         // refers to the real thing

        Print sliced.unit() and referenced.unit(). In a comment, say in one
        sentence why they differ.

        Sample output:
            sliced:     units
            referenced: C
    */
    std::println("--- Exercise 6: slicing ---");
    // TODO


    /*
        Exercise 7 - dynamic_cast

        Using the PROVIDED Sensor, Thermometer and Anemometer at the top of the
        file, build a std::vector<std::unique_ptr<Sensor>> with: a Thermometer,
        an Anemometer with gust 18.5, a Thermometer, and an Anemometer with
        gust 24.0. Loop over it. For every element that really is an
        Anemometer (use dynamic_cast on the raw pointer from .get()), count it
        and remember the largest gust. Print the count and the largest gust.

        Sample output:
            2 anemometers, largest gust 24
    */
    std::println("--- Exercise 7: dynamic_cast ---");
    // TODO


    /*
        Exercise 8 - std::variant

        Define

            using Value = std::variant<int, double, std::string>;

        and write a function

            std::string describe(const Value& value);

        that returns "integer 7", "decimal 2.5" or "text 'hail'" depending on
        what the variant holds. Each case needs different text, so use a
        visitor struct with three operator() overloads with std::visit, as in
        11.11 (or, if you prefer, std::holds_alternative and std::get).

        Build a std::vector<Value> holding 7, 2.5 and std::string{"hail"} and
        print describe() of each.

        Sample output:
            integer 7
            decimal 2.5
            text 'hail'
    */
    std::println("--- Exercise 8: variant ---");
    // TODO

    return 0;
}
