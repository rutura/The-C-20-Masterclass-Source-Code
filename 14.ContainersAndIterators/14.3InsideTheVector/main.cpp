#include <cstddef>
#include <print>
#include <string>
#include <vector>

// Counts what happens to its objects, so the vector's work becomes visible.
// The moves are noexcept, otherwise the vector would copy (13.5).
struct Counted {
    static inline int constructed{0};
    static inline int copies{0};
    static inline int moves{0};

    explicit Counted(int v) : value{v} { ++constructed; }
    Counted(const Counted& other) : value{other.value} { ++copies; }
    Counted(Counted&& other) noexcept : value{other.value} { ++moves; }
    Counted& operator=(const Counted& other) { value = other.value; ++copies; return *this; }
    Counted& operator=(Counted&& other) noexcept { value = other.value; ++moves; return *this; }

    static void reset() { constructed = 0; copies = 0; moves = 0; }
    int value;
};

int main() {

    // size() is how many elements there are. capacity() is how many fit in the
    // block the vector currently owns. When size would exceed capacity, the
    // vector allocates a bigger block and moves everything over.
    std::println("--- watching the capacity grow");
    std::vector<int> v;
    std::size_t last_capacity{v.capacity()};
    int reallocations{0};
    for (int i{0}; i < 100; ++i) {
        v.push_back(i);
        if (v.capacity() != last_capacity) {
            std::println("size {:3}: capacity {:3} -> {:3}", v.size(), last_capacity, v.capacity());
            last_capacity = v.capacity();
            ++reallocations;
        }
    }
    std::println("{} reallocations for 100 elements", reallocations);

    // reserve() allocates once, up front. Use it when you know roughly how
    // many elements are coming. It changes capacity, never size.
    std::println("\n--- reserve");
    std::vector<int> reserved;
    reserved.reserve(100);
    const int* block{reserved.data()};
    for (int i{0}; i < 100; ++i) {
        reserved.push_back(i);
    }
    std::println("size {}, capacity {}, still the same block: {}",
                 reserved.size(), reserved.capacity(), reserved.data() == block);

    // clear() destroys the elements but keeps the memory, ready for reuse.
    // shrink_to_fit() asks (it is only a request) to give the extra back.
    reserved.clear();
    std::println("after clear: size {}, capacity {}", reserved.size(), reserved.capacity());
    reserved.shrink_to_fit();
    std::println("after shrink_to_fit: capacity {}", reserved.capacity());

    // push_back builds the object first, then moves it in.
    // emplace_back hands the arguments to the constructor, building it in place.
    std::println("\n--- push_back versus emplace_back");
    std::vector<Counted> items;
    items.reserve(10);                       // no reallocation to confuse the counts

    Counted::reset();
    items.push_back(Counted{1});
    std::println("push_back(Counted{{1}}): {} constructed, {} moves", Counted::constructed, Counted::moves);

    Counted::reset();
    items.emplace_back(2);
    std::println("emplace_back(2):        {} constructed, {} moves", Counted::constructed, Counted::moves);

    // Inserting at the front pushes every existing element one place along.
    std::println("\n--- insert at the front versus at the back");
    for (int i{3}; i <= 9; ++i) {
        items.emplace_back(i);
    }
    Counted::reset();
    items.emplace_back(10);
    std::println("emplace_back on {} elements: {} moves", items.size() - 1, Counted::moves);

    items.reserve(20);
    Counted::reset();
    items.emplace(items.begin(), 0);
    std::println("emplace at begin() of {} elements: {} moves", items.size() - 1, Counted::moves);

    // A vector is one contiguous block, so the pointer from data() works with
    // C code, and the elements sit next to each other for the cache.
    std::println("\ncontiguous: &items[1] - &items[0] is {} bytes (sizeof(Counted) is {})",
                 reinterpret_cast<const char*>(&items[1]) - reinterpret_cast<const char*>(&items[0]),
                 sizeof(Counted));
    return 0;
}
