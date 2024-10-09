/*

    . Variadic Function templates: 
        . Functions that can accept an arbitrary number of arguments.
    . How It Works:

        . Base Case:
            . The base case function takes two parameters of type T and returns their sum. 
            . This base case handles the situation where there are exactly two arguments left to process.

        . Variadic Template:
            . The variadic template function uses a template parameter pack (Args...) to accept 
                an arbitrary number of arguments. . It adds the first argument (first) to the 
                result of calling add recursively on the remaining arguments (args...). . The 
                recursion eventually reduces the problem to the base case of adding two parameters.

        . This function template can handle any number of arguments and sum them up correctly.

    . Visualization: 
                    add(1, 2, 3, 4)
                    |
                    +-- 1 + add(2, 3, 4)
                            |
                            +-- 2 + add(3, 4)
                                |
                                +-- Base case: add(3, 4)
                                        |
                                        +-- 3 + 4 = 7
        Final result:   1   +   2    +    7    =   10 


    . The series of calls when we call impl_2::add2: 
        . When you call add2(1, 2, 3, 4): 

            1. First Call: add2(1, 2, 3, 4)
                first = 1, args = (2, 3, 4)
                sizeof...(args) == 3, so we go to the else branch.
                The function returns 1 + add2(2, 3, 4).

            2. Second Call: add2(2, 3, 4)
                first = 2, args = (3, 4)
                sizeof...(args) == 2, so we again go to the else branch.
                The function returns 2 + add2(3, 4).

            3. Third Call: add2(3, 4)
                first = 3, args = (4)
                sizeof...(args) == 1, so we continue in the else branch.
                The function returns 3 + add2(4).

            4. Fourth Call: add2(4)
                first = 4, args = () (no more arguments)
                sizeof...(args) == 0, so we hit the base case.
                The function returns 4.

            Returning Values:
                Now, we start returning back up the call stack:
                    The fourth call returns 4.
                    The third call returns 3 + 4 = 7.
                    The second call returns 2 + 7 = 9.
                    The first call returns 1 + 9 = 10.

        . Call stack
            ---------------
            | add2(1, 2, 3, 4)   |
            |     (first = 1)    |
            | args = (2, 3, 4)   |
            |---------------------|
            | add2(2, 3, 4)      |
            |     (first = 2)    |
            | args = (3, 4)      |
            |---------------------|
            | add2(3, 4)         |
            |     (first = 3)    |
            | args = (4)         |
            |---------------------|
            | add2(4)            |
            |     (first = 4)    |
            | args = ()          |
            |---------------------|

        . Stack unwinding: 
            ---------------
            | add2(4)          |
            | returns 4       |
            |-------------------|
            | add2(3, 4)       |
            | returns 3 + 4 = 7|
            |-------------------|
            | add2(2, 3, 4)    |
            | returns 2 + 7 = 9|
            |-------------------|
            | add2(1, 2, 3, 4) |
            | returns 1 + 9 = 10|
            |-------------------|


*/
module;

export module templates_2;

namespace templates_2{

    namespace impl_1
    {
        // Base case to add two numbers
        export template <typename T>
        T add(T a, T b) {
        return a + b;
        }

        export template <typename T, typename... Args>  // Args is a template parameter pack
        T add(T first, Args... args) {                  // Args... is a function parameter pack
            return (first + add(args...));              // args is a parameter pack expansion.
            // return add(first, add(args...));
        }
        
    } // namespace impl_1

    namespace impl_2
    {
        //Another implementation using the size of operator together with if constexpr
        //The compiler still generates different overloads for each number of arguments.
        export template <typename T, typename... Args>
        T add2(T first, Args... args) {
            /*
                .1 First Call, 2nd Call, 3rd Call, 4th Call are evaluated here.
                At the last step, first will be 4 and args will be empty, so we return 4.
                 
            */

            if constexpr (sizeof...(args) == 0) {
                return first;
            } else {
                return first + add2(args...);
            }
        }
        
    } // namespace impl_2
    
} // namespace templates_2