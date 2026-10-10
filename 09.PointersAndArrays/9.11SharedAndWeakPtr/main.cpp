#include <memory>
#include <print>
#include <string>

struct Probe {
    std::string name;

    ~Probe() {
        std::println("  probe {} shut down", name);
    }
};

// Two screens that both show the same probe. Neither one is "the" owner:
// the probe must live as long as the LONGEST-lived screen.
struct Dashboard {
    std::string title;
    std::shared_ptr<Probe> probe;
};

// Two nodes that point at each other with shared_ptr. Each one keeps the
// other alive, so neither count can ever reach zero.
struct LeakyNode {
    std::string name;
    std::shared_ptr<LeakyNode> partner;

    ~LeakyNode() {
        std::println("  LeakyNode {} destroyed", name);
    }
};

// Same two nodes, but the back reference is a weak_ptr: it can look, it does
// not keep anything alive.
struct SafeNode {
    std::string name;
    std::weak_ptr<SafeNode> partner;

    ~SafeNode() {
        std::println("  SafeNode {} destroyed", name);
    }
};

void leaky_pair() {
    auto a{std::make_shared<LeakyNode>("a")};
    auto b{std::make_shared<LeakyNode>("b")};
    a->partner = b;
    b->partner = a;
}   // a and b go out of scope: each count drops from 2 to 1, not to 0

void safe_pair() {
    auto a{std::make_shared<SafeNode>("a")};
    auto b{std::make_shared<SafeNode>("b")};
    a->partner = b;
    b->partner = a;
}   // counts fall to 0, both destructors run

int main() {

    // A shared_ptr keeps a COUNT of how many owners there are. Each copy adds
    // one. The object is destroyed when the last owner goes away.
    auto probe{std::make_shared<Probe>("north")};
    std::println("owners: {}", probe.use_count());

    {
        Dashboard wall{"wall screen", probe};
        Dashboard phone{"phone", probe};
        std::println("owners with two dashboards: {}", probe.use_count());
    }
    std::println("owners after both dashboards are gone: {}\n", probe.use_count());

    // A weak_ptr watches an object without owning it. lock() turns it into a
    // temporary shared_ptr if the object is still there, or an empty one if not.
    std::weak_ptr<Probe> watcher{probe};
    std::println("owners (a watcher does not count): {}", probe.use_count());

    if (auto locked{watcher.lock()}) {
        std::println("watcher found the probe {}, owners now {}", locked->name, probe.use_count());
    }

    std::println("\nreleasing the last owner:");
    probe.reset();
    std::println("watcher expired: {}", watcher.expired());

    if (auto locked{watcher.lock()}; !locked) {
        std::println("lock() gave an empty pointer, nothing to use\n");
    }

    // The cycle problem, side by side. Count the destructor messages.
    std::println("leaky_pair():");
    leaky_pair();
    std::println("  (no messages: both nodes leaked)\n");

    std::println("safe_pair():");
    safe_pair();

    // Choosing: unique_ptr by default (9.10). shared_ptr only when ownership
    // truly belongs to several parties. weak_ptr for a back reference or an
    // observer that must not keep the object alive.
    return 0;
}
