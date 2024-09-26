/*
    . A Canvas class that holds a 2D array of Pixels.
        . Topic: 
            . Dynamic memory management
            . Copy constructor and assignment operator: The copy and swap idiom at work.
            . Challenge the students to rewrite this using std::vector as a 2D array.
                . A solution is provided in the modern namespace.
                . Do we still need the copy and swap idiom if we're using std::vector? Food for thought.
            . Good lesson: 
                . Whenever you are dynamically allocating memory, you should always have a destructor
                    to release that memory. You should also set up your own copy constructor and copy assignment operator. to do proper deep copying.

                . The copy-and-swap idiom is not just useful for assignment operators. It can be used for any multi-step operation, where a lot can go wrong, to ensure an all-or-nothing outcome: first, create a copy, modify it, and if successful, swap the result with the original in a non-throwing manner.

                . Sometimes you don't objects of your classes to be copied at all . This is how the Qt QObject class works. It's not copyable. You can only move it. If you need that behavior, you can delete the copy constructor and copy assignment operator.
                    .eg: 
                        . class MyClass {
                        . public:
                        .     MyClass(const MyClass&) = delete;
                        .     MyClass& operator=(const MyClass&) = delete;
                        . };

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

    canvas_demo();
}