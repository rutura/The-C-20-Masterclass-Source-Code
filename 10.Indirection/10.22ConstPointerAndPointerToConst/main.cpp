#include <print>

int main() {

    // A raw variable that can be modified
    /*
    std::println("");
    std::println("Raw variable that can be modified : ");

    int number{5};
    std::println("number : {}", number);
    std::println("&number : {}", static_cast<const void*>(&number));

    number = 12;
    number += 7;

    std::println("number : {}", number);
    std::println("&number : {}", static_cast<const void*>(&number));
    */

    // Pointer: both the pointer and the pointed-to data can be modified
    /*
    int* p_number1{nullptr};
    int number1{23};

    p_number1 = &number1;
    std::println("Pointer and value pointed to : both modifiable : ");
    std::println("p_number1 : {}", static_cast<const void*>(p_number1));
    std::println("*p_number1 : {}", *p_number1); // 23
    std::println("number1 : {}", number1);       // 23

    std::println("");
    std::println("Modifying the value pointed to by p_number1 through the pointer : ");
    *p_number1 = 432;
    std::println("*p_number1 : {}", *p_number1);
    std::println("number1 : {}", number1);

    std::println("");
    std::println("Changing the pointer itself to make it point somewhere else");
    int number2{56};
    p_number1 = &number2;
    std::println("*p_number1 : {}", *p_number1);
    std::println("number1 : {}", number1);
    std::println("number2 : {}", number2);
    */

    // Pointer to const: pointer is modifiable, pointed-to value is not
    /*
    std::println("Pointer is modifiable, pointed to value is constant : ");
    int number3{632}; // the const below applies to what p_number3 points
                       // to, not to number3 itself - number3 stays a
                       // perfectly ordinary, modifiable int
    const int* p_number3{&number3};

    std::println("*p_number3 : {}", *p_number3);

    std::println("");
    std::println("Modifying the value pointed to by p_number3 through the pointer (Compile Error) : ");
    // *p_number3 = 444; // compiler error

    // Can't change what it points to, but can still repoint it elsewhere
    std::println("");
    std::println("Changing the address pointed to by p_number3 : ");
    int number4{872};
    p_number3 = &number4;
    std::println("*p_number3 : {}", *p_number3);
    */

    // const applies to whatever comes right before it - here, the pointed-to type
    /*
    std::println("const keyword applies to a variable name : ");
    int protected_var{10};

    // p_protected_var can't modify the data through this pointer,
    // regardless of whether protected_var itself is declared const.
    const int* p_protected_var{&protected_var};

    // *p_protected_var = 55; // compiler error
    protected_var = 66; // fine - protected_var itself isn't const
    std::println("protected_var : {}", protected_var);
    std::println("*p_protected_var : {}", *p_protected_var);

    // The reverse doesn't work: you can't point a modifiable pointer at
    // const data - "invalid conversion from 'const int*' to 'int*'".
    const int some_data{55};
    // int* p_some_data{&some_data}; // compiler error
    */

    // Both the pointer and the pointed-to value are constant
    /*
    const int number5{459};
    const int* const p_number5{&number5};
    std::println("Pointer is constant, value pointed to is constant : ");
    std::println("*p_number5 : {}", *p_number5);

    // *p_number5 = 222;      // error: read-only location
    // int number6{333};
    // p_number5 = &number6;  // error: read-only location
    */

    // Pointer is constant (can't repoint it), but the pointed-to value can change
    std::println("Pointer is constant, pointed to value can change : ");
    int number7{982};
    int* const p_number7{&number7};

    std::println("*p_number7 : {}", *p_number7);
    std::println("Changing value pointed to through p_number7 pointer : ");

    *p_number7 = 456;
    std::println("The value pointed to by p_number7 now is : {}", *p_number7);

    int number8{2928};
    std::println("Changing the address where p_number7 is pointing (Compile Error).");
    // p_number7 = &number8; // compiler error: p_number7 itself is const
    (void)number8;

    return 0;
}
