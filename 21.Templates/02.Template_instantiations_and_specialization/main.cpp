/*
    . Template instantiation
        .#1: Implicit instantiation through use

        .#2: Explicit template instantiation definition

        .#3: Explicit template instantiation declaration
            . Tried to split into interface and implementation file but throws linker 
                errors with Visual C++.
            . The question is, do we really even need this? Putting the explicit template instantation definition, 
                like we did in #2, seems to do the job just fine with C++20 modules.
            . Leaving this to this. But should show explicit template instantiation definition, in 
                a non-module setting. Just in case where the student is using an older version of C++.

        .#4: Template full specialization 
            . see full_specialization.ixx

        .#5: Template partial specialization
            . see partial_specialization.ixx

        .#6: Type traits
            . see type_trait_example.ixx

        #7: Specialize a single method in a class
            . see single_method_in_class.ixx 
            . specializing only the get_max function. This keeps all the other functions we had in the BoxContainer class.

    
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
        . gcc
        . cmake
        . ninja
        . vcpkg and setting up the VCPKG_ROOT environment variable
        . gdb any version

*/

// One line comment
#include "utilities.h"

int main() {
      //explicit_instantiation_declaration_demo();
      //full_specialization_demo();
      //type_trait_example_demo();
      //single_method_in_class_demo();
}