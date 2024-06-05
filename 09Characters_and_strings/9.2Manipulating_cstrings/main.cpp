/*
    . Manipulating characters: 
    . Topics: 
        . strlen
        . strcmp
        . strncmp
        . strchr
        . strrchr
        . strcat
        . strncat
        . strcpy
        . strncpy

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
    //cstring_strlen();
    //cstring_strcmp();
    //cstring_strncmp();
    //cstring_find_first_occurence_version_1();
    //cstring_find_first_occurence_version_2();
    //cstring_find_last_occurence();
    //cstring_concatenation_version_1();
    //cstring_concatenation_version_2();
    //cstring_strncat();
    //cstring_strcpy();
    cstring_strncpy();
}