/*
    . Exploring references
    . Topics: 
        . Declaring and using references
        . Compare pointers to references
        . References and const
        . references with range based for loop

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
    declaring_and_using_references();
    compare_pointers_and_references();
    references_and_const();
    ref_with_range_based_for_loop();

}