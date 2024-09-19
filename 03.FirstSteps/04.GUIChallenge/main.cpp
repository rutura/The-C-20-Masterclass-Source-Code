/*
    . GUI Challenge: SFML
        . Create a window
        . Show a circle in the window
        . Change the color of the circle
        . Change the color of the background

    . Student should do: 
        . Read the docs about SFML

    . NOTE: 
        . This example won't work in containers because they don't have a xserver
            set up. It's possible to set up one but we'll pass for this course.
                . Update: 
                    . It turns out WSL 2 has a xserver set up. And docker on Windows somehow uses it.
                    . If you are on Windows, you may be able to run this example in a container.

        . You can run it: 
            . On a local box with the requirements met: 
                . a compiler with support for modules with cmake:   
                    . gcc 14 and up
                    . clang 16 and up
                    . latest visual c++
        . ATTENTION: Be careful about the opengl dependencies that vcpkg will complain about in the output .
            . It may give you instructions on how to get them installed.
				. Install them: apt-get install libx11-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev 
        . Note that even if we don't have access to xserver we can still build the 
            binary successfuly. We simply and run it and see a GUI.
        . In this course, we will run it on windows 

*/

#include "utilities.h"

int main()
{
  print_msg("starting out...");
  app();

  return 0;
}