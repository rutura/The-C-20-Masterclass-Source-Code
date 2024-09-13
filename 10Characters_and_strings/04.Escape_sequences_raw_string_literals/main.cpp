/*
    . Escape sequences and raw string literals 
    . Topics: 
        . Escape sequences: 
            . \n: New line character
            . \t: Tab character
            . \": Double quote character
            . \\: Backslash character
        . Raw string literals: 
            . R"(string)"
            . No need to escape characters
            . Useful for regular expressions, file paths, etc.

    . Build instructions: 

        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Can also use presets on the command line.
    . Dependencies: 
        . gcc 14 or up (can be official container)
        . cmake 3.29 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

// One line comment
import utilities;

int main() {
    //escape_sequences();
    raw_string_litterals();

}