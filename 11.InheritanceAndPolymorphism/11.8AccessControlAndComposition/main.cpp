#include <cstddef>
#include <print>
#include <string>
#include <vector>

// Three levels of access, for members of a class:
//   public     everyone
//   protected  this class and its derived classes
//   private    this class only
class Base {
public:
    int open{1};
protected:
    int shared{2};
private:
    int secret{3};

public:
    int reveal_secret() const { return secret; }       // a member can use its own private
};

// PUBLIC inheritance: "is a". The base's public stays public, its protected
// stays protected. This is the one you will use 95% of the time.
class PublicDerived : public Base {
public:
    int use_shared() const { return shared; }          // protected: allowed in a derived class
    // int use_secret() const { return secret; }       // error: private to Base
};

// PRIVATE inheritance: "implemented in terms of". Everything from the base
// becomes private inside the derived class, and the conversion Derived -> Base
// is not allowed outside it. Nothing outside can tell a PrivateDerived is
// built on a Base.
class PrivateDerived : private Base {
public:
    int peek() const { return open; }                  // fine inside the class
};

// What private inheritance is usually trying to say is HAS-A. Compare the
// two ways of reusing a std::vector<double> for a stack of readings:
class StackByInheritance : private std::vector<double> {      // implemented in terms of a vector
public:
    using std::vector<double>::size;                           // choose what to expose
    void push(double value) { push_back(value); }
};

class StackByComposition {                                     // has a vector: the same, and clearer
public:
    std::size_t size() const { return items_.size(); }
    void push(double value) { items_.push_back(value); }

private:
    std::vector<double> items_;
};

// The question that decides inheritance or composition: can you say "IS A"
// and mean it for EVERY use? "A TemperatureSensor is a Sensor": yes. "A Station
// is a Logger": no, a station HAS a logger. If code that works with the base
// would be surprised by the derived class, it is not an is-a.
class Logger {
public:
    void log(const std::string& message) const { std::println("  log: {}", message); }
};

class StationWrong : public Logger {                           // exposes log() to the world, claims "is a Logger"
public:
    void start() const { log("starting"); }
};

class StationRight {                                           // has a logger, shows nothing of it
public:
    void start() const { logger_.log("starting"); }

private:
    Logger logger_;
};

int main() {

    PublicDerived derived;
    std::println("public member through a public derived class: {}", derived.open);
    std::println("protected member, used inside the derived class: {}", derived.use_shared());
    std::println("private member, read by Base's own function: {}", derived.reveal_secret());

    // None of these compiles, from outside:
    //     derived.shared;                    // error: protected
    //     derived.secret;                    // error: private
    //     PrivateDerived hidden; hidden.open;   // error: private inheritance made it private
    //     Base& base{hidden};                   // error: no conversion with private inheritance
    PrivateDerived hidden;
    std::println("\nprivate inheritance, reached through the class's own function: {}", hidden.peek());

    StackByInheritance stack_one;
    StackByComposition stack_two;
    stack_one.push(1.5);
    stack_two.push(1.5);
    std::println("\ntwo stacks, same behaviour: {} and {}", stack_one.size(), stack_two.size());

    std::println("\nthe wrong and the right way to share a logger:");
    StationWrong wrong;
    StationRight right;
    wrong.start();
    right.start();
    wrong.log("anyone can call this on a StationWrong");      // the leak: a Station is not a Logger
    // right.log("...");                                       // error: a StationRight has no log()

    // Rule of thumb: prefer composition. Inherit when you need an is-a that
    // you will use polymorphically (11.3 to 11.5). Reuse of code alone is not
    // a reason to inherit.
    return 0;
}
