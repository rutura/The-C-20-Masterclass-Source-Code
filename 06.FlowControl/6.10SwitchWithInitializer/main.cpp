#include <iostream>
#include <string>


// Tools
const int Pen{ 10 };
const int Marker{ 20 };
const int Eraser{ 30 };
const int Rectangle{ 40 };
const int Circle{ 50 };
const int Ellipse{ 60 };


int main(){

    int tool {Eraser};

    switch (double strength{3.56};tool)
    {
        case Pen : {
             std::cout << "Active tool is Pen. strength : " <<  strength << std::endl;
        }
        break;

        case Marker : {
             std::cout << "Active tool is Marker. strength : " <<  strength << std::endl;
        }
        break;


        case Eraser :
        case Rectangle : 
        case Circle : {
             std::cout << "Drawing Shapes. strength : " <<  strength << std::endl;
        }
        break;

        case Ellipse : {
             std::cout << "Active tool is Ellipse. strength : " <<  strength << std::endl;
        }
        break;
    
        default: {
            std::cout << "No match found. strength : " <<  strength << std::endl;
        }
        break;
    }

    std::cout << "Moving on" << std::endl;
    //strength++;



   
    return 0;
}