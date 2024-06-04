/*
    . Pointer arithmetic
        . navigation
        . distance
        . compare pointers
        . swap addresses example

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

    //p_a_navigation();
    //p_a_distance();
    p_a_compare_pointers();
    p_a_swap_addresses();

}