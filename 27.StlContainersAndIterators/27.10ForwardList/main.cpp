#include <algorithm>
#include <forward_list>
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

    std::forward_list<int> numbers = {100, 2, 3, 4, 5};
    print_collection(numbers);

    std::println("front element : {}", numbers.front());

    std::println("---------------------");
    std::println("");
    std::println("modifiers : ");

    std::println("");
    std::println("clear :");
    print_collection(numbers);
    numbers.clear();
    print_collection(numbers);

    // forward_list is singly-linked, so it has no insert() at begin() the
    // way list/vector do - before_begin() gives a position "before the
    // first element" that insert_after() can target instead.
    std::println("");
    std::println("insert_after : ");
    numbers = {11, 12, 13, 14, 15};
    print_collection(numbers);
    auto it_insert = numbers.before_begin();
    numbers.insert_after(it_insert, 333);
    print_collection(numbers);

    std::println("");
    std::println("emplace_after : ");
    print_collection(numbers);
    it_insert = numbers.before_begin();
    numbers.emplace_after(it_insert, 444);
    print_collection(numbers);

    std::println("");
    std::println("erase_after : ");
    print_collection(numbers);
    auto it_erase = std::find(numbers.begin(), numbers.end(), 13);

    if (it_erase != numbers.end()) {
        std::println("Found 13 !");
    } else {
        std::println("Couldn't find 13 !");
    }

    numbers.erase_after(it_erase); // erases the element after it_erase (14)
    print_collection(numbers);

    std::println("");
    std::println("pop_front : ");
    print_collection(numbers);
    numbers.pop_front();
    print_collection(numbers);

    std::println("");
    std::println("resize : ");
    print_collection(numbers);
    numbers.resize(10);
    print_collection(numbers);
    numbers.resize(3); // resizing down loses elements for good - resizing
                        // back up won't bring them back
    print_collection(numbers);
    numbers.resize(10);
    print_collection(numbers);

    std::println("");
    std::println("swap : ");
    std::forward_list<int> other_numbers{200, 400, 600};

    std::print("numbers : ");
    print_collection(numbers);
    std::print("other_numbers : ");
    print_collection(other_numbers);

    numbers.swap(other_numbers);

    std::print("numbers : ");
    print_collection(numbers);
    std::print("other_numbers : ");
    print_collection(other_numbers);

    std::println("");
    std::println("merge : ");
    std::forward_list<int> numbers1{1, 5, 6};
    std::forward_list<int> numbers2{9, 2, 4};

    std::print("numbers1 : ");
    print_collection(numbers1);
    std::print("numbers2 : ");
    print_collection(numbers2);

    numbers1.merge(numbers2);

    std::print("numbers1 : ");
    print_collection(numbers1);
    std::print("numbers2 : ");
    print_collection(numbers2);

    // splice_after moves a range of elements from one forward_list into
    // another, without copying them.
    std::println("");
    std::println("splice_after : ");
    numbers1 = {1, 5, 6, 8, 3};
    numbers2 = {9, 2, 4, 7, 13, 11, 17};

    std::print("numbers1 : ");
    print_collection(numbers1);
    std::print("numbers2 : ");
    print_collection(numbers2);

    numbers1.splice_after(numbers1.before_begin(), numbers2, numbers2.before_begin(), numbers2.cend());

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

    numbers.remove_if([](int n) { return n > 10; });
    print_collection(numbers);

    std::println("");
    std::println("reverse : ");
    numbers = {1, 100, 2, 3, 10, 1, 11, -1, 12};
    print_collection(numbers);
    numbers.reverse();
    print_collection(numbers);

    // unique() only removes contiguous duplicates - the two separated 1's
    // both survive, but the adjacent pairs (100,100 and 11,11) collapse.
    std::println("");
    std::println("unique : ");
    numbers = {1, 100, 100, 2, 3, 10, 1, 11, 11, -1, 12, 10, 1};
    print_collection(numbers);
    numbers.unique();
    print_collection(numbers);

    std::println("");
    std::println("sort : ");
    print_collection(numbers);
    numbers.sort();
    print_collection(numbers);

    // Sorting first groups all duplicates together, so a second unique()
    // call now removes every remaining duplicate, not just adjacent ones.
    numbers.unique();
    print_collection(numbers);

    return 0;
}
