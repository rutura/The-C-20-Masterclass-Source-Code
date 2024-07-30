/*
    . Templates and friendship: 


        .#1: Friendship without templates
            . see templates_and_friendship_01.ixx
            . Exploring the basics of friendship
            . This has been covered earlier in the course.

        .#2: Class is not template, friend function and friend class are templates.
            . see templates_and_friendship_02.ixx

        .#3:  Class is not a template, but the friend function and class are specific specializations of the template.
            . see templates_and_friendship_03.ixx
            . Only a few friend functions and templates have access to the private members of the class.

        .#4: Class is a template, and the friend function is not a template.
            . see templates_and_friendship_04.ixx

        .#5: The class is a template, friend functions and classes are templates, but
              but we want a few instances of the friends to have access to the private members of the class. 
            . Only int instances of the friends have access to the private members of the class.
            . Others can't. They will trigger a compiler error.
            . see templates_and_friendship_05.ixx

        .#6: Class is template, friends are template, and we want any instance of the friend templates to have 
                access to private members of the class.
            . See templates_and_friendship_06.ixx

        .#7: Class is a template, friends are templates, and we only want friends whose template paramter matches that 
            of the class to have access to the private members of the class.
            . See templates_and_friendship_07.ixx

        .#8: Stream insertion operator for BoxContainer.
            . see templates_and_friendship_08.ixx
            . operator<< is setup as a friend whose template parameter matches that of BoxContainer.
            . We have to remember to use the <> or <T> in the friend declaration, otherwise, the compiler won't generate the needed template instances.
            . We have a few options when it comes to this: 
                . set up the declaration and the definition outside.
                . put the entire friend declaration and definition inside the class. This doesn't make the friend function a member of the class. It's just a weird syntax that C++ provides.

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
    //templates_and_friendship_01_demo();
    templates_and_friendship_08_demo() 

}