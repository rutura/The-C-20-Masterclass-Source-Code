/*
    . More on modules: 
        .#1: Block export 
            . see more_on_modules_01.ixx


        .#2: Export import
            . see point.ixx and line.ixx

        .#3: Submodules
            . see math.ixx mult.div.ixx and add.sub.ixx 

        .#4 Module interface partitions
            . see add_partition.ixx, mult_partition.ixx and math_v1.ixx 

        .#5: Visibility and reachability
            . see more_on_modules_05.ixx

        .#6: Private module fragment
            . see more_on_modules_06.ixx 

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
    //more_on_modules_01_demo();
    //more_on_modules_02_demo();
    //more_on_modules_03_demo();
    //more_on_modules_04_demo();
    //more_on_modules_05_demo();
    more_on_modules_06_demo();
}