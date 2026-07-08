#include <algorithm>
#include <list>
#include <print>

template <typename T>
void print_collection(const T& collection) {
    auto it = collection.begin();
    std::print(" Collection [");
    while (it != collection.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println("]");
}

int main() {

    std::list<int> numbers = {11, 12, 13, 14, 15};

    std::println("---------------------");
    std::println("");
    std::println("element access : ");
    print_collection(numbers);
    std::println("front element : {}", numbers.front());
    std::println("back element : {}", numbers.back());

    std::println("");
    std::println("iterators : ");
    auto it = numbers.begin();
    std::print("(iterators) list of numbers : [");
    while (it != numbers.end()) {
        std::print(" {}", *it);
        ++it;
    }
    std::println("]");

    auto it_back = numbers.rbegin();
    std::print("(iterators) list of numbers (reverse) : [");
    while (it_back != numbers.rend()) {
        std::print(" {}", *it_back);
        ++it_back;
    }
    std::println("]");

    std::println("---------------------");
    std::println("");
    std::println("capacity : ");
    std::println("list max_size : {}", numbers.max_size());
    std::println("list is empty : {}", numbers.empty());
    std::println("list size : {}", numbers.size());

    std::println("---------------------");
    std::println("");
    std::println("modifiers : ");

    std::println("");
    std::println("clear :");
    print_collection(numbers);
    numbers.clear();
    print_collection(numbers);
    std::println("numbers is empty : {}", numbers.empty());

    // Unlike forward_list, list is doubly-linked, so it has an ordinary
    // insert() (not insert_after()) that places the element right before
    // the given iterator.
    std::println("");
    std::println("insert : ");
    numbers = {11, 12, 13, 14, 15};
    print_collection(numbers);
    auto it_insert = std::find(numbers.begin(), numbers.end(), 13);

    if (it_insert != numbers.end())
        numbers.insert(it_insert, 333); // inserted right before 13
    print_collection(numbers);

    std::println("");
    std::println("emplace : ");
    print_collection(numbers);
    it_insert = std::find(numbers.begin(), numbers.end(), 14); // emplace in front of 14
    if (it_insert != numbers.end())
        numbers.emplace(it_insert, 444);
    print_collection(numbers);

    std::println("");
    std::println("erase : ");
    print_collection(numbers);
    auto it_erase = std::find(numbers.begin(), numbers.end(), 333);

    if (it_erase != numbers.end()) {
        std::println("Found 333 !");
    } else {
        std::println("Couldn't find 333 !");
    }

    if (it_erase != numbers.end())
        numbers.erase(it_erase);
    print_collection(numbers);

    std::println("");
    std::println("pop_front : ");
    print_collection(numbers);
    numbers.pop_front();
    print_collection(numbers);

    std::println("");
    std::println("pop_back : ");
    print_collection(numbers);
    numbers.pop_back();
    print_collection(numbers);

    std::println("");
    std::println("push_front : ");
    print_collection(numbers);
    numbers.push_front(111);
    print_collection(numbers);

    std::println("");
    std::println("push_back : ");
    print_collection(numbers);
    numbers.push_back(222);
    print_collection(numbers);

    std::println("");
    std::println("emplace front (333) and back (444) : ");
    print_collection(numbers);
    numbers.emplace_front(333);
    numbers.emplace_back(444);
    print_collection(numbers);

    std::println("");
    std::println("resize : ");
    print_collection(numbers);
    std::println("numbers size : {}", numbers.size());

    numbers.resize(20);
    print_collection(numbers);
    std::println("numbers size : {}", numbers.size());

    numbers.resize(3); // resizing down loses elements for good - resizing
                        // back up won't bring them back
    print_collection(numbers);
    std::println("numbers size : {}", numbers.size());

    numbers.resize(20);
    print_collection(numbers);
    std::println("numbers size : {}", numbers.size());

    std::println("");
    std::println("swap : ");
    std::list<int> other_numbers{200, 400, 600};

    std::print("numbers : ");
    print_collection(numbers);
    std::print("other_numbers : ");
    print_collection(other_numbers);

    numbers.swap(other_numbers);

    std::print("numbers : ");
    print_collection(numbers);
    std::print("other_numbers : ");
    print_collection(other_numbers);

    std::println("---------------------");
    std::println("Other operations : ");

    std::println("");
    std::println("merge : ");
    std::list<int> numbers1{1, 5, 6};
    std::list<int> numbers2{9, 2, 4};

    std::print("numbers1 : ");
    print_collection(numbers1);
    std::print("numbers2 : ");
    print_collection(numbers2);

    numbers1.merge(numbers2);

    std::print("numbers1 : ");
    print_collection(numbers1);
    std::print("numbers2 : ");
    print_collection(numbers2);

    // splice moves elements from one list into another - numbers2 is moved
    // into numbers1, right before the position found for 6.
    std::println("");
    std::println("splice : ");
    numbers1 = {1, 5, 6, 8, 3};
    numbers2 = {9, 2, 4, 7, 13, 11, 17};

    std::print("numbers1 : ");
    print_collection(numbers1);
    std::print("numbers2 : ");
    print_collection(numbers2);

    auto it_splice = std::find(numbers1.begin(), numbers1.end(), 6);

    if (it_splice != numbers1.end())
        numbers1.splice(it_splice, numbers2);

    std::print("numbers1 : ");
    print_collection(numbers1);
    std::print("numbers2 : ");
    print_collection(numbers2);

    std::println("");
    std::println("remove : ");
    numbers = {1, 100, 2, 3, 10, 1, 11, -1, 12};
    print_collection(numbers);

    numbers.remove(1); // removes every element equal to 1
    print_collection(numbers);

    // The predicate here could just as well be a function pointer or a
    // functor - a lambda is the most common choice in modern code.
    numbers.remove_if([](int n) { return n > 10; });
    print_collection(numbers);

    std::println("");
    std::println("reverse : ");
    numbers = {1, 100, 2, 3, 10, 1, 11, -1, 12};
    print_collection(numbers);
    numbers.reverse();
    print_collection(numbers);

    std::println("");
    std::println("unique : ");
    numbers = {1, 100, 100, 2, 3, 10, 1, 11, 11, -1, 12, 10, 1};
    print_collection(numbers);
    numbers.unique(); // only removes contiguous duplicates
    print_collection(numbers);

    std::println("");
    std::println("sort : ");
    print_collection(numbers);
    numbers.sort();
    print_collection(numbers);
    numbers.unique(); // after sorting, all duplicates are adjacent
    print_collection(numbers);

    return 0;
}
