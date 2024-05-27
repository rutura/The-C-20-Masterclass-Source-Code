/*
    . Bitwise operator examples: 
        . Masks
        . Packing color information.
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

  //Example1: masks
  /*
  //use_options_v0(0, 0, 1, 1, 1, 0, 1, 0);
  //use_options_v1(mask_bit_2 | mask_bit_3 | mask_bit_4 | mask_bit_6);
  */


  //Example2: Packing color information
  pack_colors();



  return 0;
}