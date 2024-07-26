module;
#include <string_view>
#include <fmt/format.h>

export module utilities; 

import implicit_instantiations;
import explicit_instantiations;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}

export void implicit_instantiations_demo(){

	// Create an instance of MyClass with int (no errors will be caused because we don't call errorFunction)
    implicit_instantiations::MyClass<int> myIntInstance;
    myIntInstance.safeFunction();  // This works

    // Create an instance of MyClass with double (again, no errors because errorFunction is not called)
    implicit_instantiations::MyClass<double> myDoubleInstance;
    myDoubleInstance.safeFunction();  // This works

    // Uncommenting the following lines will cause a compilation error because errorFunction will be instantiated
    // myIntInstance.errorFunction();
    // myDoubleInstance.errorFunction();
}

export void explicit_instantiations_demo(){
	//Explicit instantiation
	
}
