#include <print>
#include <unordered_map>
#include <unordered_set>

template <typename T>
void show_collection(const T& collection) {
    std::print(" [");
    for (const auto& elt : collection) {
        std::print(" {}", elt);
    }
    std::println("]");
}

template <typename T>
void show_map_collection(const T& collection) {
    std::print(" [");
    for (const auto& [key, value] : collection) {
        std::print(" ({},{})", key, value);
    }
    std::println("]");
}

int main() {

    // unordered_set/unordered_map trade the ordering set/map guarantee for
    // faster average-case lookup - elements come out in whatever order the
    // hash table happens to store them, not sorted by key.
    std::unordered_set<int> collection1{11, 16, 2, 912, 15, 6, 15, 2};
    std::unordered_map<int, int> collection2{{1, 11}, {0, 12}, {4, 13}, {2, 14}, {3, 15}};

    std::print("collection1 : ");
    show_collection(collection1);

    std::print("collection2 : ");
    show_map_collection(collection2);

    // Most other operations mirror std::set/std::map - see the standard
    // library reference for the full list.

    return 0;
}
