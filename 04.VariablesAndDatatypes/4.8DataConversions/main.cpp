/*
    . Exploring data conversions
        . Implicit data conversions
        . Explicit data conversions
        . Overflow and underflow
*/

#include <fmt/format.h>

int main() {
    //Implicit data conversions
    //		. The compiler applies implicit conversions
    // 			when types are different in 
    //			an expression
    //		. Conversions are always done from the smallest
    //			to the largest type in this case int is 
    //			transformed to double before the expression
    //			is evaluated.Unless we are doing an assignment
    /* 
    double price { 45.6 };
    int units {10};
    
    auto total_price = price * units; // units will be implicitly converted to double
    
    fmt::println("Total price : {}", total_price);
    fmt::println("sizeof total_price : {}", sizeof(total_price));


    //Implicit conversions in assignments
    // The assignment operation is going to cause an implicit
    // narrowing conversion , y is converted to int before assignment
    int x;
    double y {45.44};
    x = y; // double to int
    fmt::println("The value of x is : {}", x);
    fmt::println("sizeof x : {}", sizeof(x));
    */

   //Explicid data conversions
   	//Implicit cast will add up the doubles,
	//then turn result into int for assignment
    /*
    double x { 12.5 };
    double y { 34.6};

    int sum = x + y; 
    fmt::println("The sum is: {}", sum);

    //Explicity cast : cast then sum up
    sum = static_cast<int>(x) + static_cast<int>(y);
    fmt::println("The sum is: {}", sum);

    //Explicit cast : sum up then cast, same thing as implicit cast
    sum =  static_cast<int> (x + y);
    fmt::println("Sum up then cast, result: {}", sum);

    //Old style C-cast
    double PI {3.14};

    //int int_pi = (int)(PI);
    int int_pi = static_cast<int>(PI);
    fmt::println("PI: {}", PI);
    fmt::println("int_pi: {}", int_pi);
    */


    //Overflow and underflow

        //Overflow 

    unsigned char data {250};

    ++data;
    fmt::println("data : {}", static_cast<int>(data));

    ++data;
    fmt::println("data : {}", static_cast<int>(data));

    ++data;
    fmt::println("data : {}", static_cast<int>(data));

    ++data;
    fmt::println("data : {}", static_cast<int>(data));

    ++data; 
    fmt::println("data : {}", static_cast<int>(data)); // 255

    ++data;  // Overflow
    fmt::println("data : {}", static_cast<int>(data)); // 256

    data = 1;

    --data;
    fmt::println("data : {}", static_cast<int>(data));

    --data;
    fmt::println("data : {}", static_cast<int>(data));
    return 0;
}