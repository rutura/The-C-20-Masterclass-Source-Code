// RAII (Resource Acquisition Is Initialization) is the idiom this entire
// chapter is built on, generalized beyond memory: acquire a resource in a
// constructor, release it in the destructor. Whatever happens in between -
// normal return, early return, even an exception - the destructor still
// runs when the object goes out of scope, so the resource always gets
// released. Chapter 11 already used this for file streams (ofstream closes
// automatically); std::unique_ptr and std::shared_ptr, starting next
// lecture, are the standard library's ready-made RAII wrappers for
// heap-allocated memory specifically.

#include <print>
#include <stdexcept>

// A resource that isn't memory - here, just an int standing in for
// something expensive to acquire (a file handle, a network connection, a
// mutex lock like chapter 29's std::lock_guard).
class ScopedResource {
public:
    explicit ScopedResource(int id) : m_id(id) {
        std::println("Acquiring resource {}", m_id);
    }

    // The destructor is the whole idea: it runs automatically, so "release
    // the resource" can never be forgotten the way a manual release()
    // call further down the function could be.
    ~ScopedResource() {
        std::println("Releasing resource {}", m_id);
    }

    // RAII types are usually not copyable - copying would mean two objects
    // both think they own (and will release) the same resource. Deleting
    // the copy operations makes that a compile error instead of a
    // double-release bug at runtime.
    ScopedResource(const ScopedResource&) = delete;
    ScopedResource& operator=(const ScopedResource&) = delete;

    int id() const { return m_id; }

private:
    int m_id;
};

void doWorkThatMightThrow(bool shouldThrow) {
    ScopedResource resource(1);
    std::println("Using resource {}", resource.id());

    if (shouldThrow) {
        throw std::runtime_error("something went wrong mid-function");
        // resource's destructor still runs while the exception unwinds
        // the stack - nothing after this line needs to "remember" to
        // clean up.
    }

    std::println("Finished using resource {} normally", resource.id());
}

int main() {

    std::println("--- Normal path ---");
    doWorkThatMightThrow(false);

    std::println("");
    std::println("--- Exception path ---");
    try {
        doWorkThatMightThrow(true);
    } catch (const std::exception& e) {
        std::println("Caught: {}", e.what());
    }
    // Notice "Releasing resource 1" printed either way, in both sections
    // above - RAII doesn't care which path the function took.

    std::println("");
    std::println("--- Nested scopes release in reverse order ---");
    {
        ScopedResource outer(10);
        {
            ScopedResource inner(20);
            std::println("Both resources alive here");
        } // inner destroyed here, before outer
        std::println("Only outer alive here");
    } // outer destroyed here

    return 0;
}
