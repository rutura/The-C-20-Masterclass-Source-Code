#include <print>

int main() {

    // Declare array - "Hello" needs 6 bytes (5 characters + the null
    // terminator string literals always add), so the array must be sized
    // 6, not 5.
    char message[6]{"Hello"};

    // Print out the array through looping
    /*
    std::print("message : ");
    for (auto c : message) {
        std::print("{}", c);
    }
    std::println("");
    */

    // Change characters in our array
    /*
    message[1] = 'a';

    std::print("message : ");
    for (auto c : message) {
        std::print("{}", c);
    }
    std::println("");
    */

    // Will probably print garbage after your char array
    /*
    std::println("message : {}", message);
    */

    // If a character array is null terminated, it's called a C-string
    /*
    char message1[]{'H', 'e', 'l', 'l', 'o', '\0'};
    std::println("message1 : {}", message1);
    std::println("sizeof(message1) : {}", sizeof(message1));
    */

    /*
    char message2[6]{'H', 'e', 'l', 'l', 'o'}; // remaining slot auto-fills with '\0'
    std::println("message2 : {}", message2);
    std::println("sizeof(message2) : {}", sizeof(message2));

    char message3[]{'H', 'e', 'l', 'l', 'o'}; // NOT a C-string - no null terminator
    std::println("message3 : {}", message3);
    std::println("sizeof(message3) : {}", sizeof(message3));
    */

    // Better: string literal - the compiler adds the null terminator for you
    /*
    char message4[]{"Hello"};
    std::println("message4 : {}", message4);
    std::println("sizeof(message4) : {}", sizeof(message4));
    */

    // Can't safely print out arrays other than character arrays
    int numbers[]{1, 2, 3, 4, 5};
    std::println("numbers : {}", static_cast<const void*>(numbers));

    return 0;
}
