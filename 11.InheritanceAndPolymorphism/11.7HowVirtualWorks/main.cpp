#include <cstdint>
#include <cstring>
#include <print>

struct Plain {
    int value{0};
    void work() const {}                  // an ordinary member function
};

struct WithVirtual {
    int value{0};
    virtual void work() const {}          // one virtual function
    virtual ~WithVirtual() = default;
};

struct Derived : WithVirtual {
    void work() const override {}
};

// Read the first 8 bytes of an object as a number. On MSVC, GCC and Clang for
// 64-bit machines, that is where the hidden "vptr" lives. This is how those
// compilers happen to do it, not something the language promises, and it is
// here only to let you SEE the mechanism.
std::uintptr_t first_word(const void* object) {
    std::uintptr_t word{0};
    std::memcpy(&word, object, sizeof word);
    return word;
}

// A call through a base reference. Look at what the compiler generates for the
// call below, in NOTES.md, with g++ -S or Compiler Explorer.
void call_work(const WithVirtual& object) {
    object.work();
}

int main() {

    // An object with a virtual function carries a hidden extra pointer.
    std::println("sizeof(Plain)       = {}  (just the int)", sizeof(Plain));
    std::println("sizeof(WithVirtual) = {}  (the int, padding, and the hidden pointer)", sizeof(WithVirtual));
    std::println("sizeof(void*)       = {}", sizeof(void*));

    // Every object of the same class holds the SAME vptr: it points at that
    // class's table of virtual functions (the "vtable"), which exists once
    // per class. A different class has a different table.
    WithVirtual first;
    WithVirtual second;
    Derived third;

    std::println("\nhidden pointer of first:  0x{:x}", first_word(&first));
    std::println("hidden pointer of second: 0x{:x}   same class, same table: {}",
                 first_word(&second), first_word(&first) == first_word(&second));
    std::println("hidden pointer of third:  0x{:x}   Derived has its own table: {}",
                 first_word(&third), first_word(&first) != first_word(&third));

    // Calling through a base reference: the compiler cannot know the real
    // type, so it follows the hidden pointer to the table, picks the entry for
    // work(), and jumps through it. One extra memory read per call.
    call_work(first);
    call_work(third);

    // Costs, in plain terms:
    //   - space: one pointer per OBJECT (8 bytes here)
    //   - time:  one indirect call per virtual call, and the compiler can
    //            rarely inline it. Usually negligible, but not in the
    //            innermost loop of a program that does millions of calls.
    // A non-virtual function costs nothing: it is a direct call.
    return 0;
}
