#include <cstddef>
#include <print>
#include <string>
#include <vector>

// A destructor is a function that runs automatically when an object dies.
// You will write your own in chapter 10. Here it only exists so that you can
// SEE when a Probe is destroyed.
struct Probe {
    std::string name;

    ~Probe() {
        std::println("  probe {} shut down", name);
    }
};

int main() {

    // Local variables live on the stack and are cleaned up when their scope
    // ends. Memory from "new" lives on the heap and stays until you say so.
    //
    //   stack:  int a{72};             freed automatically at the closing brace
    //   heap:   new int{72}            freed ONLY by delete, wherever you are
    //
    // new returns the address of the new object, so it goes in a pointer.
    int* one{new int{72}};
    std::println("*one = {}", *one);

    delete one;         // give the memory back. Exactly one delete per new.
    one = nullptr;      // so a leftover use is an obvious crash, not silent garbage

    // The reason to use the heap at all: a size that is only known when the
    // program runs. new[] makes an array, and the matching form is delete[].
    std::size_t count{6};
    int* readings{new int[count]{}};     // the {} sets every element to 0

    for (std::size_t i{0}; i < count; ++i) {
        readings[i] = 60 + static_cast<int>(i) * 3;
    }

    std::print("heap readings: ");
    for (std::size_t i{0}; i < count; ++i) {
        std::print("{} ", readings[i]);
    }
    std::println("");

    delete[] readings;       // new[] pairs with delete[], never plain delete
    readings = nullptr;

    // delete runs the destructor and then frees the memory.
    std::println("\nbefore delete:");
    Probe* probe{new Probe{"north"}};
    std::println("  using probe {}", probe->name);
    delete probe;
    std::println("after delete");

    // The three classic mistakes. All compile, none produces an error message
    // on its own, and the project will make each one fail loudly:
    //
    //   leak            new without any delete: the memory is never returned
    //   double free     delete the same pointer twice
    //   use after free  read or write through a pointer after delete
    //
    // Every one of them comes from the same root: a raw pointer says WHERE
    // something is, and nothing about WHO must clean it up.

    // If an exception is thrown between new and delete, or a return leaves
    // early, the delete is skipped too. So how does a std::vector avoid all of
    // this? It does the new[] and delete[] itself, in its destructor.
    std::vector<int> safer(count);
    for (std::size_t i{0}; i < count; ++i) {
        safer[i] = 60 + static_cast<int>(i) * 3;
    }
    std::println("\nvector, same job, no new and no delete: size {}", safer.size());

    return 0;
}
