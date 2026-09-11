#include <print>
#include <string>

// --- const function parameters -------------------------------------------

// BY VALUE: x is already a fresh COPY the moment this function is called -
// pass-by-value means the caller's variable was never reachable from here,
// const or not. Adding const here protects that copy from ACCIDENTAL
// reassignment inside the function's own body - a self-imposed discipline,
// not a promise to the caller. Without const, x *could* be reassigned
// inside the function and nothing outside would ever know or care, because
// it is thrown away when the function returns either way.
int square_by_value(const int x) {
    // x = x + 1;   // would not compile: x is const - catches a typo like
    //              // this before it becomes a silent, pointless mutation
    return x * x;
}

// BY REFERENCE: label is an ALIAS for the caller's own std::string - no
// copy is made. Here const is not just tidiness - it is the promise the
// caller actually relies on: "this function reads label, and will not
// touch your string." Combined with &, it gets the no-copy speed of a
// reference while keeping the safety of pass-by-value.
void print_label(const std::string& label) {
    // label += "!";   // would not compile: label is const - this would
    //                 // otherwise reach through the alias and mutate the
    //                 // CALLER's own string, which is exactly what the
    //                 // const promise rules out
    std::println("label: {}", label);
}

// --- constexpr functions ---------------------------------------------------

// A constexpr function CAN run at compile time, when every argument is
// itself known at compile time - but it is not required to. Called with a
// runtime value, it just runs normally, like any other function.
constexpr int cube(int x) {
    return x * x * x;
}

int main() {

    // --- const standalone variables -----------------------------------------
    const int max_players{4};
    int current_players{1};   // NOT const - this one is meant to change

    std::println("max_players: {}", max_players);
    std::println("current_players: {}", current_players);

    // max_players = 5;   // would not compile: assignment to a const variable
    current_players = 2;   // fine - current_players was never const
    std::println("current_players after a join: {}", current_players);

    // --- const by value vs const by reference, side by side -----------------
    std::println("\nsquare_by_value(6): {}", square_by_value(6));

    std::string player_name{"Ada"};
    print_label(player_name);

    // --- constexpr variables: compile-time, not just unchanging -------------
    // const int is "will not change after it is set" - the value itself can
    // still come from somewhere only known at RUN time.
    const int seed{current_players * 7};   // fine: computed from a runtime value
    std::println("\nseed (const, runtime-computed): {}", seed);

    // constexpr additionally demands the compiler can compute the value
    // ITSELF, while compiling - before the program ever runs.
    constexpr int board_size{8 * 8};       // fine: 8 * 8 is knowable right now
    std::println("board_size (constexpr, compile-time): {}", board_size);

    // constexpr int bad_seed{current_players * 7};
    //     // would not compile: current_players is not known until the
    //     // program is actually running - constexpr cannot accept that,
    //     // even though the identical expression was fine for `const seed`
    //     // above

    // --- constexpr functions: compile time when possible, runtime otherwise --
    constexpr int compile_time_cube{cube(3)};   // 3 is a literal - the compiler
    std::println("\ncube(3), evaluated at compile time: {}", compile_time_cube);
    // can (and typically will) compute this itself; nothing runs at runtime

    int side{current_players + 2};
    int runtime_cube{cube(side)};                // side is only known while
    std::println("cube(side), evaluated at run time: {}", runtime_cube);
    // the program runs - cube falls back to an ordinary function call here,
    // same function, same result, different point in time it runs

    return 0;
}
