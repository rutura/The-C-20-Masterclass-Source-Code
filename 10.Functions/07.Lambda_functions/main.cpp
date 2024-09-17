/*
    . Lambda functions: 
        . Declaring a lambda function and calling it through a name
        . Declare a lambda function and call it directly
        . Lambda function that takes parameters
        . Lambda function that returns something
        . Explicitly specify the return type
        . Capture lists





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
    //Declaring and using lambdas
    //declare_and_use_lambda_func();

    //Capture lists
    capture_lists();

    //Capture all lists
    //capture_all_lists();
}