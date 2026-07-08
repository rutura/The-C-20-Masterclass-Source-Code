// std::pair (used earlier in this course) only ever holds two values.
// std::tuple generalizes that to any fixed number of values, of any mix of
// types - useful whenever a function needs to return several unrelated
// values without the ceremony of declaring a one-off struct for it.

#include <print>
#include <format>
#include <tuple>
#include <string>

// A function returning several unrelated values - a natural fit for
// std::tuple over a bespoke struct, since nothing else in the program
// needs a "student record" type just to return three things.
std::tuple<int, std::string, double> makeRecord() {
    return {1, "Alice", 91.5};
}

int main() {

    std::tuple<int, std::string, double> record{1, "Alice", 91.5};

    // std::get<index> accesses one element by its position, checked at
    // compile time - std::get<3> on a 3-element tuple simply won't compile.
    std::println("get<0>: {}", std::get<0>(record));
    std::println("get<1>: {}", std::get<1>(record));
    std::println("get<2>: {}", std::get<2>(record));

    // Structured bindings (already used with std::pair and map entries
    // earlier in this course) work on any tuple-like type, including
    // std::tuple itself - this is the readable way to actually consume one.
    auto [id, name, score] = makeRecord();
    std::println("");
    std::println("id: {}, name: {}, score: {}", id, name, score);

    // std::apply unpacks a tuple's elements directly into a function's
    // parameter list - useful when you already have a tuple and want to
    // call something that takes the values individually rather than as
    // one packaged tuple.
    auto describe = [](int recordId, const std::string& recordName, double recordScore) {
        return std::format("#{}: {} scored {:.1f}", recordId, recordName, recordScore);
    };
    std::println("");
    std::println("{}", std::apply(describe, record));

    // std::tie creates a tuple of references, letting you unpack into
    // *existing* variables instead of declaring new ones the way structured
    // bindings do - useful for something like updating three separate
    // out-parameters at once.
    int existingId{};
    std::string existingName;
    double existingScore{};
    std::tie(existingId, existingName, existingScore) = makeRecord();
    std::println("");
    std::println("existingId: {}, existingName: {}, existingScore: {}",
                  existingId, existingName, existingScore);

    // std::tie can also skip fields you don't care about with std::ignore.
    int onlyId{};
    std::tie(onlyId, std::ignore, std::ignore) = makeRecord();
    std::println("onlyId: {}", onlyId);

    // Tuples compare lexicographically out of the box - first differing
    // element decides, same as comparing strings character by character.
    std::tuple earlier{1, "Alice"};
    std::tuple later{1, "Bilal"};
    std::println("");
    std::println("earlier < later: {}", earlier < later);

    return 0;
}
