#include <memory>
#include <print>
#include <string_view>

// ---------------------------------------------------------------------------
// The BUG: a base class with a NON-virtual destructor.
// ---------------------------------------------------------------------------
// Written out in full, because the point is what is MISSING:
class Base {
public:
    ~Base() {                                    // not virtual
        std::println("  ~Base");
    }
    virtual void work() const {}
};

class Derived : public Base {
public:
    Derived() : buffer_{new int[100]} {}

    ~Derived() {
        std::println("  ~Derived: freeing the buffer");
        delete[] buffer_;
    }

    void work() const override {}

private:
    int* buffer_;
};

// ---------------------------------------------------------------------------
// The FIX: make the base destructor virtual.
// ---------------------------------------------------------------------------
class GoodBase {
public:
    virtual ~GoodBase() {
        std::println("  ~GoodBase");
    }
    virtual void work() const {}
};

class GoodDerived : public GoodBase {
public:
    GoodDerived() : buffer_{new int[100]} {}

    ~GoodDerived() override {
        std::println("  ~GoodDerived: freeing the buffer");
        delete[] buffer_;
    }

    void work() const override {}

private:
    int* buffer_;
};

int main(int argc, char* argv[]) {

    std::println("virtual destructor, deleting through a base pointer:");
    GoodBase* good{new GoodDerived{}};
    delete good;                       // runs ~GoodDerived, then ~GoodBase

    std::println("\nthe same through a unique_ptr to the base:");
    {
        std::unique_ptr<GoodBase> owner{std::make_unique<GoodDerived>()};
    }                                  // unique_ptr deletes through the base pointer

    // The buggy version is NOT run by default, because deleting a derived
    // object through a base pointer with a non-virtual destructor is
    // undefined behaviour. Run the program with the argument "broken" to see it
    // for yourself, ideally under a sanitizer (9.12):
    //
    //     rooster broken
    if (argc >= 2 && std::string_view{argv[1]} == "broken") {
        std::println("\nNON-virtual destructor, deleting through a base pointer:");
        Base* bad{new Derived{}};
        delete bad;                    // undefined behaviour: ~Derived never runs
        std::println("(~Derived was never called: its buffer was leaked)");
    }

    // The rule: a class meant to be used through a base-class pointer (any
    // class with virtual functions) gets a VIRTUAL destructor. If you do not
    // need a body, "virtual ~X() = default;" is all it takes. A class that is
    // never used that way (a plain value type) does not need one.
    return 0;
}
