#include <print>

int main() {

    // How we've used pointers so far: pointing at stack variables.
    /*
    int number{22}; // stack

    int* p_number = &number;

    std::println("");
    std::println("Declaring pointer and assigning address : ");
    std::println("number : {}", number);
    std::println("p_number : {}", static_cast<const void*>(p_number));
    std::println("&number : {}", static_cast<const void*>(&number));
    std::println("*p_number : {}", *p_number);

    int* p_number1;    // uninitialized pointer, contains a junk address
    int number1{12};
    p_number1 = &number1; // now points somewhere valid

    std::println("");
    std::println("Uninitialized pointer : ");
    std::println("*p_number1 : {}", *p_number1);
    */

    // BAD: writing into an uninitialized pointer's junk address
    /*
    int* p_number2; // contains a junk address - could be anything
    std::println("Writing in the 55");
    *p_number2 = 55; // writing into junk memory: undefined behavior
    std::println("");
    std::println("Writing into uninitialized pointer through dereference");
    std::println("p_number2 : {}", static_cast<const void*>(p_number2));
    std::println("Dereferencing bad memory");
    std::println("*p_number2 : {}", *p_number2);
    */

    // Initializing a pointer to nullptr instead - a pointer pointing nowhere
    /*
    int* p_number3{}; // equivalent to nullptr
    std::println("Writing into nullptr memory");
    // *p_number3 = 33; // writing through nullptr: undefined behavior, likely a crash
    std::println("Done writing");

    std::println("");
    std::println("Reading and writing through nullptr : ");
    // std::println("p_number3 : {}", static_cast<const void*>(p_number3));
    // std::println("*p_number3 : {}", *p_number3); // reading through nullptr: also undefined behavior
    */

    // Dynamic heap memory
    /*
    int* p_number4{nullptr};
    p_number4 = new int; // allocates space for one int on the heap - this
                          // memory now belongs to the program until it's
                          // explicitly returned with delete

    *p_number4 = 77;
    std::println("");
    std::println("Dynamically allocating memory : ");
    std::println("*p_number4 : {}", *p_number4);

    delete p_number4; // return the memory to the OS
    p_number4 = nullptr;
    */

    // A pointer can also be initialized with a valid heap address directly,
    // instead of nullptr.
    int* p_number5{new int};     // contains a junk value - not zero-initialized
    int* p_number6{new int(22)}; // direct-initialization
    int* p_number7{new int{23}}; // uniform initialization

    std::println("");
    std::println("Initialize with valid memory address at declaration : ");
    std::println("*p_number5 : {}", *p_number5); // junk value
    std::println("*p_number6 : {}", *p_number6);
    std::println("*p_number7 : {}", *p_number7);

    // Every new needs exactly one matching delete.
    delete p_number5;
    p_number5 = nullptr;

    delete p_number6;
    p_number6 = nullptr;

    delete p_number7;
    p_number7 = nullptr;

    // A pointer can be reused for a fresh allocation once its old one is freed.
    p_number5 = new int(81);
    std::println("*p_number5 : {}", *p_number5);

    delete p_number5;
    p_number5 = nullptr;

    // Calling delete twice on the same pointer is undefined behavior - in
    // practice, glibc's allocator detects it and aborts the program
    // outright ("double free detected"). Resetting the pointer to nullptr
    // immediately after delete (as done above, and again here) is exactly
    // what prevents this - deleting a nullptr is always safe and a no-op.
    p_number5 = new int(99);
    std::println("*p_number5 : {}", *p_number5);

    delete p_number5;
    p_number5 = nullptr;
    // delete p_number5; // would be a double-delete if p_number5 still
    // pointed at the freed block - safe here only because it was reset to
    // nullptr first.

    // What new(std::nothrow) does when an allocation is too large to
    // satisfy: rather than throwing std::bad_alloc, it returns nullptr, so
    // the failure can be handled with an ordinary nullptr check instead of
    // a try/catch.
    for (size_t i{0}; i < 5; ++i) {
        int* data = new (std::nothrow) int[1'000'000'000];

        if (data != nullptr) {
            std::println("Data allocated");
            delete[] data; // free it immediately - this loop only exists
                            // to demonstrate the allocation attempt itself
        } else {
            std::println("Data allocation failed");
        }
    }

    std::println("Program is ending well");
    return 0;
}
