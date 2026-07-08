#include <print>

int main() {

    std::println("");
    std::println("Verbose nullptr check: ");

    int* p_number{}; // initialized to nullptr

    /*
    if (!(p_number == nullptr)) {
        std::println("p_number points to a VALID address : {}", static_cast<const void*>(p_number));
        std::println("*p_number : {}", *p_number);
    } else {
        std::println("p_number points to an INVALID address.");
    }
    */

    // A pointer converts to bool directly (true if non-null) - the
    // idiomatic, shorter equivalent of the explicit != nullptr check above.
    if (p_number) {
        std::println("p_number points to a VALID address : {}", static_cast<const void*>(p_number));
        std::println("*p_number : {}", *p_number);
    } else {
        std::println("p_number points to an INVALID address.");
    }

    delete p_number; // deleting a nullptr is always safe - a guaranteed no-op

    // It's OK to call delete on a nullptr
    int* p_number1{};
    delete p_number1; // won't cause any problem, since p_number1 is nullptr

    // if (p_number1 != nullptr) {
    //     delete p_number1;
    // }

    return 0;
}
