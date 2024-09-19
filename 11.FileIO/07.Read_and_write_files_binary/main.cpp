/*
    . A C++ starter project using CMake and bringing in fmt right out of the box.
    . Uses vcpkg as a dependency manager
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
            . eg: gcc
        . cmake
        . ninja
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
#include "utilities.h"

#include <fmt/core.h>


int main() {
// Example data to write
 std::vector<unsigned char> output{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

 // Writing the data using std::span for type safety
 if (write_data("sample.bin", std::span(output))) {
      fmt::println("Data written successfully.");
 } else {
      fmt::print(stderr, "Failed to write data.\n");
      return 1;
 }

 // Reading the data back using modern C++ practices
 std::vector<unsigned char> input;
 size_t bytes_read = read_data("sample.bin", input);

 if (bytes_read > 0) {
      fmt::println("Data read successfully.");
 } else {
      fmt::print(stderr, "Failed to read data.\n");
      return 1;
 }

 // Verifying that the data is the same
 if (output == input) {
      fmt::println("The data read from the file is equal to the data written.");
 } else {
      fmt::println("The data read from the file is not equal to the data written.");
 }

    return 0;

}