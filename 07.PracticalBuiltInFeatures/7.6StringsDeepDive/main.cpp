#include <print>
#include <sstream>
#include <string>

int main() {

    // --- assignment, concatenation, swap ----------------------------------
    // Chapter 5 covered +, ==, length()/size(), starts_with/ends_with.
    // Here are the member-function equivalents and a few more useful ones.
    std::string title{"cat"};
    std::string subtitle;             // empty string
    subtitle.assign(title);           // same effect as: subtitle = title;

    std::println("title: {}\nsubtitle: {}", title, subtitle);

    title.append("acomb");            // "cat" -> "catacomb"
    std::string spinoff{title + " sequel"};   // "+" still works too
    std::println("title (after append): {}\nspinoff: {}", title, spinoff);

    std::string first{"one"};
    std::string second{"two"};
    first.swap(second);               // exchange contents, no copy of data
    std::println("after swap -> first: {}, second: {}", first, second);

    // --- substr: pull out a piece without touching the original -----------
    const std::string filename{"report_final.pdf"};
    std::println("\nsubstr(0, 6): {}", filename.substr(0, 6));   // "report"

    // --- find family: locate things inside a string ------------------------
    const std::string log{"noon is 12pm; midnight is not"};
    std::println("\nlog: {}", log);
    std::println("find(\"is\") from the front: {}", log.find("is"));
    std::println("rfind(\"is\") from the back:  {}", log.rfind("is"));

    // find_first_not_of: skip a set of characters, report where something
    // else starts. Handy for "where does the interesting part begin".
    std::size_t digitsStart{log.find_first_not_of("noon is ")};
    std::println("first character not in \"noon is \": '{}' at {}",
                  log.at(digitsStart), digitsStart);

    // npos marks "not found" - always check for it before using the result.
    std::size_t missing{log.find("xyz")};
    std::println("find(\"xyz\") == npos: {}", missing == std::string::npos);

    // --- erase / replace: edit a string in place ----------------------------
    std::string sentence{"The quick brown fox jumps over the lazy dog"};
    std::println("\nsentence: {}", sentence);

    sentence.erase(19);   // drop everything from index 19 onward
    std::println("after erase(19): {}", sentence);

    std::size_t spacePos{sentence.find(' ')};
    while (spacePos != std::string::npos) {
        sentence.replace(spacePos, 1, "_");
        spacePos = sentence.find(' ', spacePos + 1);
    }
    std::println("after replacing spaces: {}", sentence);

    // --- insert: splice text into the middle --------------------------------
    std::string greeting{"Hello, !"};
    greeting.insert(7, "World");
    std::println("\nafter insert: {}", greeting);

    // --- string streams: build and parse text without hand-rolled loops -----
    // ostringstream accumulates pieces of different types into one string,
    // the same << you already know from std::cout, aimed at a string
    // instead of the console.
    std::ostringstream receipt;
    receipt << "Order #" << 42 << ": " << "coffee" << " - $" << 4.5;
    std::println("\nreceipt.str(): {}", receipt.str());

    // istringstream runs the same idea backwards: pull typed values out of
    // one string, the same way std::cin pulls them from the keyboard.
    std::istringstream record{"Ada 3 19.99"};
    std::string item;
    int quantity{};
    double price{};
    record >> item >> quantity >> price;
    std::println("parsed -> item: {}, quantity: {}, price: {}",
                  item, quantity, price);

    return 0;
}
