#include <print>

// A plain function call (see 3.3/6.2). Arguments travel in registers,
// the answer comes back in one register - call / ret, exactly like
// 6.2's stack-frame diagram.
int add_numbers(int first, int second) {
    int result{first + second};
    return result;
}

int main() {
    int sum{add_numbers(25, 7)};
    std::println("add_numbers(25, 7) = {}", sum);
    return 0;
}

// Try it: paste both functions into Compiler Explorer together and
// make sense of what is going on. Add a third parameter and watch
// which register it lands in; add a seventh and watch it move onto
// the stack instead.
