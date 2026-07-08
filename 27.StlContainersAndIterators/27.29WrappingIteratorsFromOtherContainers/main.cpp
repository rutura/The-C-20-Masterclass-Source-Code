#include <algorithm>
#include <format>
#include <print>
#include <ranges>
#include <string>
#include <vector>

// A container doesn't need to build its own iterator from scratch - it can
// simply expose (wrap) the iterators of whatever it stores its data in
// internally, which is exactly what most of the standard library's own
// adapters (stack, queue, ...) do too.
template <typename T>
class VectorWrapper {
public:
    std::vector<T>::iterator begin() { return m_items.begin(); }
    std::vector<T>::iterator end() { return m_items.end(); }

    std::vector<T>::const_iterator begin() const { return m_items.cbegin(); }
    std::vector<T>::const_iterator end() const { return m_items.cend(); }

    std::vector<T>::const_iterator cbegin() { return m_items.cbegin(); }
    std::vector<T>::const_iterator cend() { return m_items.cend(); }

    void add(T item) {
        m_items.push_back(item);
    }

    const std::vector<T>& items() const { return m_items; }

private:
    std::vector<T> m_items;
};

template <typename T>
struct std::formatter<VectorWrapper<T>> : std::formatter<std::string> {
    auto format(const VectorWrapper<T>& vec, std::format_context& ctx) const {
        std::string out = "Items : ";
        for (const auto& i : vec.items()) {
            out += std::format("{} ", i);
        }
        return std::formatter<std::string>::format(out, ctx);
    }
};

int main() {

    VectorWrapper<std::string> greeting;
    greeting.add("Hello");
    greeting.add("World!");
    greeting.add("How");
    greeting.add("are");
    greeting.add("you");
    greeting.add("all");
    greeting.add("doing?");

    std::println("greeting : {}", greeting);

    std::println("Range based for loop : ");
    for (const auto& i : greeting) {
        std::print("{} ", i);
    }
    std::println("");

    std::println("taking only 2 : ");
    for (const auto& i : greeting | std::views::take(2)) {
        std::print("{} ", i);
    }
    std::println("");

    return 0;
}
