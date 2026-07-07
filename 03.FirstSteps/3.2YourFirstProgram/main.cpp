// This is a one line comment. The compiler ignores everything after "//" on this line.
// We are building a small "profile" program throughout this chapter, one piece at a time.

/*
   This is a block comment. It can span multiple lines and is useful
   for longer explanations, like this one describing what the program does.

   For now, our program just says hello. We'll grow it lecture by lecture
   into something that talks to the user, makes decisions, loops, and even
   remembers things between runs.
*/

#include <print>

int main() {

    std::println("Hello there!");
    std::println("Welcome to your very first C++ program.");

    return 0;
}
