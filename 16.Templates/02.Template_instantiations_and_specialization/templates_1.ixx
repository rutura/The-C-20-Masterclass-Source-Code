/*
    . Exploring implicit instantiations
*/
module;

#include <fmt/format.h>

export module templates_1;

namespace templates_1{

    // Define a class template
    export template <typename T>
    class MyClass {
    public:
        // A function that has no error
        void safe_function() {
            fmt::println("{}", "Safe function called");
        }

        // A function that has an error
        void error_function() {
            // Intentional error: assuming T is a class with a member function 'non_existent_function'
            T instance;
            instance.non_existent_function();  // This will cause an error if instantiated
        }
    };
    
} // namespace templates_1