/*
    . Logical operators: 
        .#1: Logical operators
            . We will use the Point class to demonstrate the logical operators.
            . These will be shown as: 
                . member functions
                . non-member functions

        .#2: Logical operators with implicit conversions
            . Laying ground for <=>
            . Showing the worst case scenario where you 
                have to implement A LOT of operators.
            . The number class prevents this by using implicit conversions, 
                because of the explicit constructor.
            . If we want to support logical comparisons between Number and ints, 
                things like : 
                    . 15 < n2
                    . n1 < 25
                    . n1 < n2,
                we have to implement three versions of the operator<.
            . If we extend this to all 6 operators, we end up with 18 operators.
            . This is a lot of boilerplate code.

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
    //logical_operators();
    logical_ops_implicit_conversions();
}