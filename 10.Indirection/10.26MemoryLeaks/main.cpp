#include <print>

int main() {

    // Reassigning a pointer before freeing what it used to point to leaks
    // the original allocation - the program loses its only handle to that
    // memory, but the memory itself stays reserved until the program exits.
    /*
    int* p_number{new int{67}}; // points to some address, call it address1

    // should delete and reset here

    int number{55}; // stack variable
    p_number = &number; // now points to address2 - address1 is still
                         // reserved, but nothing can reach it anymore
    */

    // Double allocation: the same leak, just via a second `new` instead of
    // pointing at a stack variable.
    /*
    int* p_number1{new int{55}};

    // use the pointer

    // should delete and reset here

    p_number1 = new int{44}; // the memory holding 55 is now leaked

    delete p_number1;
    p_number1 = nullptr;
    */

    // Nested scopes with dynamically allocated memory
    {
        int* p_number2{new int{57}};

        // use the dynamic memory
    }
    // The memory holding 57 is leaked here - p_number2 went out of scope
    // at the closing brace, but nothing ever called delete on it.

    std::println("Program is ending well");
    return 0;
}
