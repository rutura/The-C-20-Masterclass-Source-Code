#include <print>

int main() {

    // Case 1: Uninitialized pointer
    /*
    int* p_number; // dangling, uninitialized pointer

    std::println("");
    std::println("Case 1 : Uninitialized pointer : .");
    std::println("p_number : {}", static_cast<const void*>(p_number));
    std::println("*p_number : {}", *p_number); // CRASH!
    */

    // Case 2: Deleted pointer
    /*
    std::println("");
    std::println("Case 2 : Deleted pointer");
    int* p_number1{new int{67}};

    std::println("*p_number1 (before delete) : {}", *p_number1);

    delete p_number1;

    std::println("*p_number1 (after delete) : {}", *p_number1); // reading freed memory
    */

    // Case 3: Multiple pointers to the same address
    /*
    std::println("");
    std::println("Case 3 : Multiple pointers pointing to same address : ");

    int* p_number3{new int{83}};
    int* p_number4{p_number3};

    std::println("p_number3 - {} - {}", static_cast<const void*>(p_number3), *p_number3);
    std::println("p_number4 - {} - {}", static_cast<const void*>(p_number4), *p_number4);

    delete p_number3;

    // p_number4 now points to freed memory - dereferencing it is undefined
    // behavior: crash, garbage, or anything in between.
    std::println("p_number4 (after deleting p_number3) - {} - {}", static_cast<const void*>(p_number4), *p_number4);
    */

    // Solution 1: initialize pointers immediately upon declaration
    /*
    std::println("");
    std::println("Solution 1 : ");
    int* p_number5{nullptr};
    int* p_number6{new int(87)};

    if (p_number6 != nullptr) {
        std::println("*p_number6 : {}", *p_number6);
    } else {
        std::println("Invalid address");
    }
    */

    // Solution 2: reset a pointer to nullptr right after delete
    /*
    std::println("");
    std::println("Solution 2 : ");
    int* p_number7{new int{82}};

    std::println("p_number7 - {} - {}", static_cast<const void*>(p_number7), *p_number7);

    delete p_number7;
    p_number7 = nullptr; // makes it unmistakable that it points nowhere

    if (p_number7 != nullptr) {
        std::println("*p_number7 : {}", *p_number7);
    } else {
        std::println("Invalid memory access!");
    }
    */

    // Solution 3: for multiple pointers sharing an address, designate one
    // clear "master" pointer responsible for releasing the memory - other
    // pointers should only be dereferenced while the master is still valid.
    std::println("");
    std::println("Solution 3 : ");
    int* p_number8{new int{382}}; // p_number8 is the master pointer
    int* p_number9{p_number8};

    std::println("p_number8 - {} - {}", static_cast<const void*>(p_number8), *p_number8);

    if (!(p_number8 == nullptr)) { // only use the "slave" pointer while the master is valid
        std::println("p_number9 - {} - {}", static_cast<const void*>(p_number9), *p_number9);
    }

    delete p_number8; // master releases the memory
    p_number8 = nullptr;

    if (!(p_number8 == nullptr)) {
        std::println("p_number9 - {} - {}", static_cast<const void*>(p_number9), *p_number9);
    } else {
        std::println("WARNING : Trying to use an invalid pointer");
    }

    std::println("Program is ending well");

    return 0;
}
