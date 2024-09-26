module;

#include <fmt/format.h>

export module utilities; 

import canvas;

export void use_canvas(){

	//raw::Canvas canvas{ 10, 10 };
	modern::Canvas canvas{ 10, 10 };
	canvas.print();

}