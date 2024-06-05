/*
    .  Fortune teller example 
        . version 1:
            . Stores predictions in independent raw arrays.
        . version 2:
            . Stores predictions in a single 2d array.
        . version 3:
            . Uses a marsene twister to generate random numbers.
            . also shows that the generator can be stored in the global scope.
        . version 4:
            . We ask chatGPT to improve the code and it offers a few suggestions: 
                . Input Handling:
                    . Used std::getline for reading the name to handle spaces in the input.
                    . Added std::cin.ignore to clear the input buffer after reading the character for the continuation prompt. This prevents any leftover characters from interfering with subsequent inputs.
                . Logic Improvement:
                    . Simplified the loop condition to improve readability and maintainability.

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
    //fortune_teller_version_1();
    //fortune_teller_version_2();
    //fortune_teller_version_3();
    //fortune_teller_version_4();
    fortune_teller_version_5();
    return 0; 
}