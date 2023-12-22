1. Welcome [ADJUSTED]
      1. Wecome to the course
      2. Get the most out of this course
         - Provide a folder structure where students can just drag and drop starter files
   

2. Environment Setup [ADJUSTED]
   1. Tools: 
        1. Visual Studio Code and the extensions
        2. CMake
        3. Vcpkg
        4. A compiler
     2. Windows
     3. Linux
     4. Mac

3. Diving In [ADJUSTED]
      1. Project Template
      2. Your First C++ Program
         - Comments
         - Errors
         - Statements and Functions
      3. C++ Program Execution Model
      4. Challenge

4. Variables, data types and operations [ADJUSTED]
      1. Introduction
      2. Number Systems
          - Integers
          - Floating points: IEEE 754
          - Numeric limits to show the ranges
      3. Decimals and Integers
         - Note: Integrate std::cin and std::cout into your code examples. No need to specifically set up lectures for them
         - Note: Use std::format for output formatting.
         - Note: use std::vector and std::array where you need to store collections.
         - Integers and modifiers
         - Floating points and modifiers
         - Booleans
      4. Characters And Text
         1. char and std::string
      5. Auto
      6. Operations
         - Basic operations
         - Precedence and associativity
         - Prefix and postfix + and -
         - Compound assignment
         - Relational operators
         - Logical operators
      7. Math Functions
      8. Weird Integral types
      9. Data conversions
         - Implicit conversions
         - Explicit conversions
         - Overflow and underflow
      10. Bitwise operators [Optional]
      11. Challenge: SFML Window.
          * Use the code here: https://github.com/SFML/cmake-sfml-project/blob/master/src/main.cpp 

5. Modern C++ Formatting: std::format
      1. Overview
      2. Challenge



6. Literals, constants and compile time programming. Reference : https://github.com/federico-busato/Modern-CPP-Programming/blob/master/05.Basic_Concepts_IV.pdf. See the title relevant to this.
    1. Literals
    2. Constants
    3. constexpr
    4. constexpr vs const
    5. constinit
    6. constexpr functions
       - Note: We have briefly talked about functions so it's ok to talk about constexpr functions here
    7. consteval functions
    8. constexpr variables
    9. Challenge - FIGURE OUT

7.  Flow control
    1.  if, switch and ternary operator
        - If statements
           - If blocks and scope
             - Move the concepts for the variable scope revisited lecture here
        - Switch statements
        - Ternary operator

    2.  Loops 
        - For
        - Range based for
        - While
        - Do while
        - Huge loops with output
        - Infinite loops
    3. Challenge: SFML Window. Add something to use loops

8.  Arrays: Reserved for low level usage
      1. Arrays
         - declaration and initialization
         - size of arrays
         - array bounds
      2.  Arrays of characters
      3.  Random numbers
      4. Fortune teller v1
      5. Multidimensional arrays
         - Also cover multi dimensional arrays of characters
      6. Challenge: may be yamlcpp?  

9. Pointers: Reserved for low level usage
      1. Pointer basics
         - declaring and using pointers
         - pointer to char
         - arrays of pointer to char
         - const pointer and pointer to const
         - array of const pointer to char
         - pointers and arrays

      2. Pointer arithmetic
      3. Memory map revisited
      4. Dynamic memory allocation
      5.  Pointer quirks
         - dangling pointers
         - when new fails
         - null pointer safety
         - memory leaks
      6. Challenge: Banking application 

10. References
      1.  Declaring and using references
      2. Comparing pointers and references
      3. References and const
      4. References with range based for loops
      5. Challenge : Banking application?

11. Character manipulation and strings
      1. C style strings
      2. std::string
          - All the nuances you covered in previous version of the course
      3. Escape sequences
      4. Raw string literals
      5. String copies 
      6. string_view
      7. Challenge: Banking application??

12. Functions
      1. Function declaration and definition
      2. Function calling (value, pointer and reference parameters)
      3. Function parameters and arguments
      4. Return values
      5. Optional output
      6. Void functions
      7. Variable Lifetime and scope
      8. Function overloading
      9. Default arguments
      10. Inline functions
      11. Recursive functions
      12. Function pointers
      13. Lambda functions
      14. Arguments to the main function
      15. Challenge: SQLite database?? 
      16. Challenge: CMake Functions and Macros?? 

13. Function templates
      1.  [Reorganize the content of this chapter - Marius]
      2. Trying out function templates
      3. Template type deduction and explicit arguments
      4. Template parameters by reference
      5. Template specialization
      6. Function templates with overloading
      7. Function templates with multiple parameters
      8. Template return type deduction with auto
      9. Decltype and trailing return types
      10. Decltype auto
      11. Default arguments
      12. Non type template parameters
      13. Auto function templates
      14. Named template parameters for lambdas
      15. Type traits.

14. C++ 20 Concepts
      1. Using concepts
      2. Building your own concepts
      3. Zooming in on the requires clause
      4. Combining concepts (|| and &&)
      5. Concepts and auto

15. Namespaces
      1. Introduction
      2. Creating Namespaces
      3. Use Points like a gentleman
      4. Namespaces Across Multiple Files
      5. Split your points across
      6. Default Global Namespace
      7. Make it global
      8. Built In Namespaces
      9. Using Declarations
      10. Anounymous Namespaces
      11. Nested Namespaces
      12. Namespace Aliases
      13. Summary

16. Functions, multiple files and linkage [CHAPTER RELOCATED]
      1. Introduction
      2. Compiling and linking : Compilation Model
      3. Declarations and definitions
      4. One Definition Rule
      5. Linkage
      6. Global external variables
      7. Flipping linkage
      8. Inline variables and functions
      9. Inline Vs static (anonymous namespaces)
      10. Forward declarations
      11. Summary

17. OOP with classes: Custom types
      1. Intro to classes
         - Content previously in the classes section 
      2. Classes, objects and const
      3. Diving deep into constructors and initialization
      4. Friends
      5. Static members
      6. Enums and type aliases

18. Smart Pointers
      1. Introduction
      2. Unique pointers
      3. Unique pointers as function parameters and return values
      4. Unique pointers and arrays
      5. Shared pointers
      6. Creating shared pointers from unique pointers
      7. Shared pointers with arrays
      8. Shared pointers as function parameters and return values
      9. Weak pointers
      10. Smart pointer members : Recommended reading
      11. Smart Pointers conventional wisdom
      12. Summary

19. Operator overloading
      1. Introduction
      2. Addition Operator as Member
      3. Addition Operator as Non-Member
      4. Subscript Operator for Reading
      5. Subscript Operator for Reading and Writing
      6. Subscript Operator for Collection Types
      7. Stream Insertion Operation Operator
      8. Stream Extraction Operator
      9. Other Arithmetic Operators
      10. Compound Operators && Reusing Other Operators
      11. Custom Type Conversions
      12. Implicit Conversions with Overriden Binary Operators
      13. Unary Prefix Increment Operator As Member
      14. Unary Prefix Increment Operator as Non-Member
      15. Unary Postfix Increment Operator
      16. Prefix-Postfix Decrement Operator (Exercise)
      17. Copy Assignment Operator
      18. CU::string copy assignment operator
      19. Copy Assignment Operator for Other Types
      20. Type Conversions Recap
      21. Functors
      22. Summary

20. Logical operators and the C++ 20 spaceship operator
      1. Introduction
      2. All Logical Operators
      3. Rel Ops Namespace
      4. Logical Operators with Implicit Conversions
      5. Three way comparison operator
      6. Defaulted Equality Operator
      7. Custom equality operator
      8. Default ordering with spaceship operator
      9. Members without the spaceship operator
      10. Custom spaceship operator for ordering
      11. Logical Operators Simplified
      12. Spaceship operator as a non member
      13. Zooming in on weak ordering - Example 1
      14. Zooming on weak ordering - Example 2
      15. Zooming on partial ordering
      16. Summing up on comparisons in C++ 20
      17. Summary

21. Inheritance
      1. Introduction
      2. First try on Inheritance
      3. Protected members
      4. Get it to work
      5. Base class access specifiers : Zooming in
      6. Base class access specifiers : A demo
      7. Closing in on Private Inheritance
      8. Resurecting Members Back in Context
      9. Default Constructors with Inheritance
      10. Custom Constructors With Inheritance
      11. Copy Constructors with Inheritance
      12. Inheriting Base Constructors
      13. Inheritance and Destructors
      14. Reused Symbols in Inheritance
      15. Summary

22. Polymorphism

23. Exception handling

24. BoxContainer: A case study

25. Class templates

26. Move semantics

27. Function like entities

28. STL, Containers and Iterators

29. STL Algorithms

30. C++ 20 Ranges and Range Algorithms

31. Building custom iterators for your containers

32. C++ 20 Coroutines

33. C++ 20 Modules