#include <fmt/format.h>

// Tools
const int Pen{ 10 }; 
const int Marker{ 20 };
const int Eraser{ 30 };
const int Rectangle{ 40 };
const int Circle{ 50 };
const int Ellipse{ 60 };


int main(){

    int tool {Eraser};

    if (tool == Pen) {
        fmt::println( "Active tool is pen" );
        //Do the actual painting
    }
    else if (tool == Marker) {
        fmt::println( "Active tool is Marker" );
    }
    else if (tool == Eraser) {
        fmt::println( "Active tool is Eraser" );
    }
    else if (tool == Rectangle) {
        fmt::println( "Active tool is Rectangle" );
    }
    else if (tool == Circle) {
        fmt::println( "Active tool is Circle" );
    }
    else if (tool == Ellipse) {
        fmt::println( "Active tool is Ellipse" );
    }

    fmt::println( "Moving on" );
    
    return 0;
}