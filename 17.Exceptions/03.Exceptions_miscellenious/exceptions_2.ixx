/*
    . Exploring custom termination: 
        . C++ provides a way to set a custom termination function.
        . This function is called when an exception is thrown and not caught.
        . This is your chance to save what you can before the program terminates.
        . In our case we just print a message and wait 10s before calling std::abort().
        . std::abort is a function that terminates the program without unwinding the stack.
        . The code example for this lives in the main function.
*/
module;

export module exceptions_2;

namespace exceptions_2{
    
} // namespace exceptions_2
