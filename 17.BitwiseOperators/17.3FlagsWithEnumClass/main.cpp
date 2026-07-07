#include <print>

// The realistic use for bitwise operators in day-to-day C++ is combining a
// handful of yes/no options into one small value instead of passing half a
// dozen separate bool parameters around. An enum class (chapter 14) gives
// each option a readable name, and giving each one its own bit means several
// can be combined into a single value with |.
enum class FilePermission {
    None    = 0b000,
    Read    = 0b001,
    Write   = 0b010,
    Execute = 0b100,
};

// enum class deliberately blocks |/& directly - it doesn't implicitly
// convert to int the way a plain enum would. Casting to the underlying int
// at the point of combining is the trade-off for that safety, and it's a
// pattern you'll see a lot in real permission/flag code.
int combine(FilePermission a, FilePermission b) {
    return static_cast<int>(a) | static_cast<int>(b);
}

bool has(int flags, FilePermission check) {
    return (flags & static_cast<int>(check)) != 0;
}

int main() {

    // A file that can be read and written, but not executed.
    int documentPermissions = combine(FilePermission::Read, FilePermission::Write);

    std::println("Can read?    {}", has(documentPermissions, FilePermission::Read));
    std::println("Can write?   {}", has(documentPermissions, FilePermission::Write));
    std::println("Can execute? {}", has(documentPermissions, FilePermission::Execute));

    // Combine three flags in one go by OR-ing all of them together.
    int scriptPermissions = static_cast<int>(FilePermission::Read)
                           | static_cast<int>(FilePermission::Write)
                           | static_cast<int>(FilePermission::Execute);

    std::println("");
    std::println("Script can execute? {}", has(scriptPermissions, FilePermission::Execute));

    // Revoking a permission: AND with the NOT of the flag clears just that
    // bit, leaving every other bit untouched.
    scriptPermissions &= ~static_cast<int>(FilePermission::Write);
    std::println("Script can write (after revoking)? {}", has(scriptPermissions, FilePermission::Write));
    std::println("Script can execute (still)?        {}", has(scriptPermissions, FilePermission::Execute));

    return 0;
}
