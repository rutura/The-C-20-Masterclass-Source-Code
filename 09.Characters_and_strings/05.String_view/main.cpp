/*
    . Exploring std::string_view
    . Topics: 
        . The problem
        . The solution
        . Construction
        . Visualizing the original string
        . Changing the view window
        . Lifetime
        . Data
        . Non-null terminated strings
        . Behaviors

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
    //string_view_the_problem();
    //string_view_the_solution();
    //string_view_construction();
    //std_string_view_visualizes_original_string();
    //std_string_view_change_view_window();
    //std_string_view_lifetime();
    //std_string_view_data();
    //std_string_view_non_null_terminated_strings();
    std_string_view_behaviors();
}