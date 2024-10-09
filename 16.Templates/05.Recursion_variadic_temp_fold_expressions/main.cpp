/*
    . Template recursion: 
        .#1: Fibonacci and factorial using template recursion.
            . I did factorial and leave fibonacci as an exercise.
            . see recursion.ixx

        .#2: Variadic function templatesl
            . see variadic_function_templates.ixx
			
		.#3: Fold expressions.

        
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

    //templates_1_demo();
    //templates_2_demo();
    //templates_3_demo();
    templates_4_demo();
}