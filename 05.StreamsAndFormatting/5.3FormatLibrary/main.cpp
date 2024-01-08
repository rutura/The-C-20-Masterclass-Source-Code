/*

    . Show three ways to output data in fmt
        . fmt::format combined with std::cout
        . fmt::print
        . fmt::println

    . The {} block called a format specifier. It a placeholder for the data that will be printed.

    . format_spec ::=  [[fill]align][sign]["#"]["0"][width]["." precision]["L"][type]
        straight from the reference doc: https://fmt.dev/latest/syntax.html#format-specification-mini-language
        fill        ::=  <a character other than '{' or '}'>
        align       ::=  "<" | ">" | "^"
        sign        ::=  "+" | "-" | " "
        width       ::=  integer | "{" [arg_id] "}"
        precision   ::=  integer | "{" [arg_id] "}"
        type        ::=  "a" | "A" | "b" | "B" | "c" | "d" | "e" | "E" | "f" | "F" | "g" | "G" |
                        "o" | "p" | "s" | "x" | "X" | "?"

*/

#include <iostream>
#include <fmt/format.h>

int main(){
   
    /*
    std::cout << fmt::format("Hello, {}!", "world") << std::endl;
    fmt::print("Hello, {}!", "world\n");
    fmt::println("Hello, {}!", "world"); 
    */

    fmt::println("Unformatted table : ");
    fmt::println("{} {} {}", "Daniel","Gray", "25");
    fmt::println("{} {} {}", "Stanley","Woods", "33");
    fmt::println("{} {} {}", "Jordan", "Parker", "45");
    fmt::println("{} {} {}", "Joe", "Ball", "21");
    fmt::println("{} {} {}", "Josh", "Carr", "27");
    fmt::println("{} {} {}", "Izaiah", "Robinson", "29");

    fmt::println("-----");
    
    fmt::println("Formatted table : "); 
    fmt::println("{:<10} {:<10} {:<5}", "Lastname", "Firstname", "Age");
    fmt::println("{:<10} {:<10} {:<5}", "Daniel", "Gray", "25");
    fmt::println("{:<10} {:<10} {:<5}", "Stanley", "Woods", "33");
    fmt::println("{:<10} {:<10} {:<5}", "Jordan", "Parker", "45");
    fmt::println("{:<10} {:<10} {:<5}", "Joe", "Ball", "21");
    fmt::println("{:<10} {:<10} {:<5}", "Josh", "Carr", "27");
    fmt::println("{:<10} {:<10} {:<5}", "Izaiah", "Robinson", "29");

    fmt::println("-----");

    //dynamic width
    int col_width{10};
    fmt::println("Formatted table with dynamic width: "); 
    fmt::println("{:<{}} {:<{}} {:<{}}", "Lastname", col_width, "Firstname", col_width, "Age", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Daniel", col_width, "Gray", col_width, "25", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Stanley", col_width, "Woods", col_width, "33", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Jordan", col_width, "Parker", col_width, "45", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Joe", col_width, "Ball", col_width, "21", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Josh", col_width, "Carr", col_width, "27", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Izaiah", col_width, "Robinson", col_width, "29", col_width/2);

    fmt::println("-----");

    //right justified
    fmt::println("Right justified table:  ");
    col_width = 20;
    fmt::println("{:>{}} {:>{}} {:>{}}", "Lastname", col_width, "Firstname", col_width, "Age", col_width/2);
    fmt::println("{:>{}} {:>{}} {:>{}}", "Daniel", col_width, "Gray", col_width, "25", col_width/2);
    fmt::println("{:>{}} {:>{}} {:>{}}", "Stanley", col_width, "Woods", col_width, "33", col_width/2);
    fmt::println("{:>{}} {:>{}} {:>{}}", "Jordan", col_width, "Parker", col_width, "45", col_width/2);
    fmt::println("{:>{}} {:>{}} {:>{}}", "Joe", col_width, "Ball", col_width, "21", col_width/2);
    fmt::println("{:>{}} {:>{}} {:>{}}", "Josh", col_width, "Carr", col_width, "27", col_width/2);
    fmt::println("{:>{}} {:>{}} {:>{}}", "Izaiah", col_width, "Robinson", col_width, "29", col_width/2);

    fmt::println("-----");

    //left justified
    fmt::println("Left justified table :  ");
    col_width = 20;
    fmt::println("{:<{}} {:<{}} {:<{}}", "Lastname", col_width, "Firstname", col_width, "Age", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Daniel", col_width, "Gray", col_width, "25", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Stanley", col_width, "Woods", col_width, "33", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Jordan", col_width, "Parker", col_width, "45", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Joe", col_width, "Ball", col_width, "21", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Josh", col_width, "Carr", col_width, "27", col_width/2);
    fmt::println("{:<{}} {:<{}} {:<{}}", "Izaiah", col_width, "Robinson", col_width, "29", col_width/2);

    fmt::println("-----");

    //Internal justified 
    fmt::println("Internal justified: ");
    fmt::print("{:>10}\n", -123.45);
    fmt::print("{:^10}\n", -123.45);
    fmt::print("{:<10}\n", -123.45);

    fmt::println("-----");

    //setfill
    fmt::println("Table with fill characters :  ");
    col_width = 20;
    fmt::println("{:*<{}} {:*<{}} {:*<{}}", "Lastname", col_width, "Firstname", col_width, "Age", col_width/2);
    fmt::println("{:*<{}} {:*<{}} {:*<{}}", "Daniel", col_width, "Gray", col_width, "25", col_width/2);
    fmt::println("{:*<{}} {:*<{}} {:*<{}}", "Stanley", col_width, "Woods", col_width, "33", col_width/2);
    fmt::println("{:*<{}} {:*<{}} {:*<{}}", "Jordan", col_width, "Parker", col_width, "45", col_width/2);
    fmt::println("{:*<{}} {:*<{}} {:*<{}}", "Joe", col_width, "Ball", col_width, "21", col_width/2);
    fmt::println("{:*<{}} {:*<{}} {:*<{}}", "Josh", col_width, "Carr", col_width, "27", col_width/2);
    fmt::println("{:*<{}} {:*<{}} {:*<{}}", "Izaiah", col_width, "Robinson", col_width, "29", col_width/2);

    fmt::println("-----");

    //control bool output format : 1/0 or true/false
    bool condition {true};
    bool other_condition {false};
    
    fmt::println("condition: {}",condition); //true
    fmt::println("other_condition: {}",other_condition); //false
    
    //This is a hack - ref: https://github.com/fmtlib/fmt/issues/170
    fmt::println("condition: {:d}",condition);
    fmt::println("other_condition: {:d}",other_condition);

    fmt::println("-----");

    //showpos and noshowpos : show or hide the +  sign for positive numbers
    fmt::println("show or hide the +  sign for positive numbers: "); 
    int pos_num {34};
    int neg_num {-45};

    fmt::println("pos_num: {}", pos_num);
    fmt::println("neg_num: {}", neg_num);

    fmt::println("pos_num: {:+}", pos_num);
    fmt::println("neg_num: {:-}", neg_num);

    fmt::println("-----");

    //different number systems : std::dec, std::hex, std::oct
    fmt::println("different number systems: dec, hex, oct"); 
    int pos_int {717171};
    int neg_int {-5};
    double double_var {498.32};
    
    fmt::println("default base format : ");
    fmt::println("pos_int : {}", pos_int);
    fmt::println("neg_int : {}", neg_int);
    fmt::println("double_var : {}", double_var);
    
    fmt::println("pos_int in different bases : ");
    fmt::println("pos_int (dec) : {}", pos_int);
    fmt::println("pos_int (hex) : {:x}", pos_int);
    fmt::println("pos_int (oct) : {:o}", pos_int);
    fmt::println("pos_int (binary) : {:b}", pos_int);
    fmt::println("pos_int (decimal) : {:d}", pos_int);
    
    fmt::println("neg_int in different bases : ");
    fmt::println("neg_int (dec) : {}", neg_int);
    fmt::println("neg_int (hex) : {:x}", neg_int);
    fmt::println("neg_int (oct) : {:o}", neg_int);
    fmt::println("neg_int (binary) : {:032b}", neg_int);// Prints the pos number representation prepended with a negative sign.
                                                        // Make sure this is what you want.
    fmt::println("neg_int (decimal) : {:d}", neg_int);

    //We'll see more about floating point format specifiers shortly.  
    fmt::println("double_var in different formats: ");
    fmt::println("double_var (default): {}", double_var);
    fmt::println("double_var (fixed): {:f}", double_var);
    fmt::println("double_var (scientific): {:e}", double_var);
    fmt::println("double_var (general): {:g}", double_var);  

    fmt::println("-----");

    //uppercase and nouppercase
    fmt::println("uppercase and nouppercase: ");
    pos_int = 717171;
    fmt::println("pos_int (nouppercase - default): ");
    fmt::println("pos_int (dec): {}", pos_int);
    fmt::println("pos_int (hex): {:x}", pos_int);
    fmt::println("pos_int (oct): {:o}", pos_int);
    
    //For integers, the # toogles the alternative format flag. This shows the base prefix like 0b, and 0x.
    fmt::println("pos_int (uppercase): ");
    fmt::println("{:#X}", pos_int);
    fmt::println("{:#B}", pos_int);
    
    fmt::println("-----");

    //fixed and scientific : for floating point values
    //control the precision.
    
    fmt::println("fixed and scientific: for floating point values: ");
    double a{ 3.1415926535897932384626433832795 };
    double b{ 2006.0 };
    double c{ 1.34e-10 };
    
    fmt::println("double values (default : use scientific where necessary) : ");
    fmt::println("a : {}", a);
    fmt::println("b : {}", b);
    fmt::println("c : {}", c);

        
    fmt::println("double values (precision) : ");
    fmt::println("a: {:.6}", a);
    fmt::println("b: {:.6}", b);
    fmt::println("c: {:.6}", c);
    
    fmt::println("double values (fixed) : ");
    fmt::println("a: {:.6f}", a);
    fmt::println("b: {:.6f}", b);
    fmt::println("c: {:.6f}", c);
    
    fmt::println("double values (scientific) : ");
    fmt::println("a: {:.6e}", a);
    fmt::println("b: {:.6e}", b);
    fmt::println("c: {:.6e}", c);

    fmt::println("-----");

    //argument indexes: Allow us to order arguments. This is good for example for applications that use localization.
    fmt::println("argument indexes: ");
    fmt::println("It's {:.2f} degrees outside and it's {}",34.5, "sunny");
    fmt::println("It's {1} today. And the temperature is {0:.2f} degrees outside", 34.5, "sunny"); 


    return 0;
}