/*
    . Exploring smart pointers
        . unique_ptr
        . shared_ptr
        . weak_ptr will be introduced later, when we have learnt about classes.
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
    unique_pointers();
    shared_pointers();

}