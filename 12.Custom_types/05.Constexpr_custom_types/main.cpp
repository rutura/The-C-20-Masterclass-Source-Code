/*
    . Constexpr and consteval classes: 

        . The requirement for a class to be constexpr is that it provides: 
            . A constexpr constructor
        . Constexpr or consteval classes can have non constexpr member functions.
            . see the print_time() function in the Time24 class.
        . A constexpr function member function can't call a non-constexpr function.
            . fmt::println is not constexpr in the fmt library.
            . We can't call it from the print_time() function.
        . The definitions of constexpr or consteval functions must be available in 
            the module interface file. If you put it in the implementation file,
            you may face issues.
            
    . Build instructions: 
        . Bare hands with CMake: 
            . cmake -S . -B build
            . cmake --build build

        . With CMake presets (VS Code): 
            . Select configure preset
            . Select build preset
            . Use the run and debug buttons: We can debug application right from the start.

        . Note: 
            . There are other ways to build but we'll focus on these two in the course.
            . You can use the docker containers that come with the course for a fully reproducible build environment.
                . one for gcc 14 [link]
                . one for clang 18 [link]

    . Requirements:
        . A modern C++ compiler: 
            . eg: gcc 14, clang 16 or latest msvc. 
        . cmake 3.30 or up
        . ninja 1.11 or up
        . vcpkg and setting up the VCPKG_ROOT environment variable
            . how to update vcpkg: https://learn.microsoft.com/en-us/vcpkg/about/faq#how-do-i-update-vcpkg
        . A debugger: 
            . eg: gdb, lldb, or the visual studio debugger
        . Goood to have: 
            . Git

        . Editor: 
            . VS Code: 
                . The C++ extension
                . The CMake Tools extension
                . The CMake extension
                . NOTE: These are required to give you the best experience.

        . Know where a binary is: 
            . Linux: which command
                . eg: which ninja
            . Windows: Get-command
                . eg: Get-command ninja

    . Philosophy: 
        . All non module looking code should be hidden away in the utilities module.

*/

// One line comment
import utilities;

int main() {

    use_time_demo();
}