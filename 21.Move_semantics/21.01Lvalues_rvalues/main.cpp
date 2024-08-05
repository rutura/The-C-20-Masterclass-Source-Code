/*
    . A C++ starter project using CMake and bringing in fmt right out of the box.
    . Uses the CMake presets file from endless sky and modifies it to work with the cl compiler
    . Uses vcpkg as a dependency manager
    . Sets up vs code to have a status bar
    . You also need ninja installed on your system.
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
  print_msg("Hello world!");
}