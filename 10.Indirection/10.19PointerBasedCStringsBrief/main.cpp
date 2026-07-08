#include <print>
#include <random>

int main() {

    // Before std::string existed, a "string" was just a pointer to the
    // first char of a null-terminated char array - this is what that
    // looked like, and why std::string/std::string_view (chapter 12)
    // replaced it as the default for new code.
    const char* message{"Hello World!"};
    std::println("message : {}", message);

    // *message = "B"; // compiler error: message points to const data
    std::println("*message : {}", *message);

    // A char array (not a pointer-to-const) can still be modified in place.
    char message1[]{"Hello World!"};
    message1[0] = 'B';
    std::println("message1 : {}", message1);

    // An array of const char* pointers - one classic way to store a list
    // of C-strings before std::vector<std::string> existed. Each pointer
    // points at a separate string literal.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist;

    const char* predictions[]{
        "a lot of kids running in the backyard!",
        "a lot of empty beer bootles on your work table.",
        "you Partying too much with kids wearing weird clothes.",
        "you running away from something really scary",
        "clouds gathering in the sky and an army standing ready for war",
        "dogs running around in a deserted empty city",
        "a lot of cars stuck in a terrible traffic jam",
        "you sitting in the dark typing lots of lines of code on your dirty computer",
        "you yelling at your boss. And oh no! You get fired!",
        "you laughing your lungs out. I've never seen this before."};

    dist = std::uniform_int_distribution<size_t>(0, std::size(predictions) - 1);
    std::println("");
    std::println("A random prediction : {}", predictions[dist(gen)]);

    // Marking both the pointer and the pointed-to data const is the safest
    // version of this pattern - neither the string contents nor which
    // string each slot points to can change afterward.
    const char* const students[]{
        "Daniel Gray",
        "Tuna Philbe",
        "The Rock",
        "Kumar Singh",
        "Sam Ali",
        "Dave Mahoro"};

    std::println("");
    std::println("Printing out the students : ");
    for (const char* student : students) {
        std::println("{}", student);
    }

    // *students[0] = 'K';           // compiler error: pointed-to data is const
    // students[0] = "Bob the Great"; // compiler error: the pointers themselves are const

    return 0;
}
