/*
    . The spaceship operator
        .#1: The basics
            . Basic comparisons
            . Spaceship comparisons
            . weak ordering
            . strong ordering
            . partial ordering

        .#2: Defaulted equality operator

        .#3: Custom equality operator

        .#4: Default ordering with spaceship

        .#5: Members without spacehip operator

        .#6: Custom spaceship operator for ordering
            . ATTENTION: 
                . For some reason, gcc doesn't like it when we do the custom spaceship operator.
                . Will see how it fares with other compilers.
                . You can even compile the same code without modules.
                . This problem may be fixed in future versions of the compiler.

        .#7: Logical operators simplified
            . GCC doesn't like this either.

        .#8: Spaceship operator as a non member. 
            . See number.ixx.
            . GCC doesn't like this either.



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
    //spaceship_op_the_basics();
    //defaulted_equality_operator();
    //custom_equality_operator();
    //default_ordering_with_spaceship();
    //members_without_spaceship();
    //custom_spaceship_op_for_ordering();
}