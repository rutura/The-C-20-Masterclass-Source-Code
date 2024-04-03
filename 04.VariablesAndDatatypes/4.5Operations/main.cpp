/*
        - Basic operations
         - Precedence and associativity
         - Prefix and postfix + and -
         - Compound assignment
         - Relational operators
         - Logical operators
*/
#include <fmt/format.h>

int main()
{
  // Basic operations
  /*
  fmt::println("----Basic operations----");
  // Addition
  int number1{2};
  int number2{7};

  int result = number1 + number2;
  fmt::println("addition - result : {}", result);

  // Subtraction
  result = number2 - number1;
  fmt::println("subtraction - result : {}", result);

  result = number1 - number2;
  fmt::println("subtraction - result : {}", result);

  // Multiplication
  result = number1 * number2;
  fmt::println("subtraction - result : {}", result);

  // Division
  result = number2 / number1;
  fmt::println("division - result : {}", result);

  // Modulus
  result = number2 % number1; // 7 % 2
  fmt::println("modulus - result : {}", result); // 1

  result = 31 % 10;
  fmt::println("modulus - result : {}", result); // 1
  */
  //-------------------------------------------------------------
  /*
  fmt::print("\n");
  fmt::println("----Precedence and Associativity----");
  int a {6};
  int b {3};
  int c {8};
  int d {9};
  int e {3};
  int f {2};
  int g {5};

  int result = a + b * c -d/e -f + g; //  6 +  24  -   3 - 2 + 5

  fmt::println("result : {}", result);

  result = a/b*c +d - e + f;  //   16 + 9 - 3 + 2
  fmt::println("result : {}", result);

  result = (a + b) * c -d/e -f + g; // 72-3-2+5
  fmt::println("result () : {}", result);
  */
  //-----------------------------------------------------------------------------------------------
  /*
  fmt::println("\n");
  fmt::println("----Prefix and Postfix Increment and Decrement----");
  int value { 5 };

  //Increment by one
  value = value + 1; //6
  fmt::println("The value is : {}", value); // 6

  value = 5; // Reset value to 5

  //Decrement by one
  value = value - 1; // 4
  fmt::println("The value is : {}", value); //4

  //===================================================================


  fmt::println("======Postfix increment and decrement======");
  //Reset value to 5
  value = 5;

  fmt::println("The value is (incrementing) : {}", value++); // 5
  fmt::println("The value is : {}", value); // 6

  fmt::println("\n");

  //Decrement with postfix

  //Reset value to 5
  value = 5;

  fmt::println("The value is (decrementing) : {}", value--); //5
  fmt::println("The value is : {}", value); // 4


  //===================================================================


  fmt::println("======Prefix increment and decrement======");

  //Reset value to 5
  value = 5;

  ++value;
  fmt::println("The value is (prefix++) : {}", value); // 6

  //Reset value to 5
  value = 5;
  fmt::println("The value is (prefix++ in place) : {}", ++value); // 6

  //Prefix : Decrementing

  //Reset value to 5;
  value = 5;
  --value;
  fmt::println("The value is (prefix--) : {}", value); // 4

  //Reset value to 5;
  value = 5;
  fmt::println("The value is (prefix-- in place) : {}", --value);//4
  */

  //-----------------------------------------------------------------------------------------------------------------

  /*
 fmt::println("----Compound assignment operators----");
      int value {45};

  fmt::println("The value is : {}", value);

  value = value + 5;
  //value +=5; // equivalent to value = value + 5
  fmt::println("The value is (after +=5) : {}", value); // 50

  value -=5; // equivalent to value = value - 5
  fmt::println("The value is (after -=5) : {}", value); // 45

  value *=2;
  fmt::println("The value is (after *=2) : {}", value); // 90

  value /= 3;
  fmt::println("The value is (after /=3) : {}", value); // 30

  value %= 11;
  fmt::println("The value is (after %=11) : {}", value);// 8
  */

  //----------------------------------------------------------------------------------------
  /*
   fmt::println("----Relational operators----");
   int number1 {20};
   int number2 {20};

   fmt::println("number1 : {}", number1);
   fmt::println("number2 : {}", number2);

   fmt::println("Comparing variables");

   fmt::println("number1 < number2 : {}", (number1 < number2));
   fmt::println("number1 <= number2 : {}", (number1 <= number2));
   fmt::println("number1 > number2 : {}", (number1 > number2));
   fmt::println("number1 >= number2 : {}", (number1 >= number2));
   fmt::println("number1 == number2 : {}", (number1 == number2));
   fmt::println("number1 != number2 : {}", (number1 != number2));

   fmt::println("store comparison result and use it later");

   bool result = (number1 == number2);

   fmt::println("{} == {} : {}", number1, number2, result);
   */

  //----------------------------------------------------------------------------------------

  fmt::println("----Logical operators----");
  bool a{ true };
  bool b{ false };
  bool c{ true };

  fmt::println("a : {}", a);
  fmt::println("b : {}", b);
  fmt::println("c : {}", c);


  // AND : Evaluates to true when all operands are true.
  //       A single false operand will drag
  //      the entire expression to evaluating false.

  fmt::println("Basic AND operations");

  fmt::println(" a && b : {}", (a && b));// false
  fmt::println(" a && c : {}", (a && c));// true
  fmt::println(" a && b && c : {}", (a && b && c));// false


  // OR : Evaluates to true when at least one operand true.
  //       A single true operand will push
  //      the entire expression to evaluating true.
  fmt::println("Basic OR operations");
  fmt::println(" a || b : {}", (a || b));
  fmt::println(" a || c : {}", (a || c));
  fmt::println(" a || b || c : {}", (a || b || c));


  // NOT : Negates whateve operand you put it with
  fmt::println("Basic NOT operations");

  fmt::println("!a : {}", !a);
  fmt::println("!b : {}", !b);
  fmt::println("!c : {}", !c);


  // Combinations of all these operators
  fmt::println("Combining logical operators");
  // !(a &&b) || c
  fmt::println("!(a &&b) || c : {}", (!(a && b) || c));// true


  // Combining logical operators with relational operators
  int d{ 45 };
  int e{ 20 };
  int f{ 11 };

  fmt::println("Relational and logic operations on integers");
  fmt::println("d : {}", d);
  fmt::println("e : {}", e);
  fmt::println("f : {}", f);

  fmt::println("(d > e) && (d > f) : {}", ((d > e) && (d > f)));// true
  fmt::println("(d==e) || (e <= f ) : {}", ((d == e) || (e <= f)));
  fmt::println("(d < e) || (d > f) : {}", ((d < e) || (d > f)));
  fmt::println("(f > e) || (d < f) : {}", ((f > e) || (d < f)));
  fmt::println("(d > f) && (f <= d) : {}", ((d > f) && (f <= d)));
  fmt::println("(d > e) && (d <= f) : {}", ((d > e) && (d <= f)));
  fmt::println("(! a) && (d == e) : {}", ((!a) && (d == e)));
  fmt::println("(! a) && (d == e) : {}", ((!a) && (d == e)));
  return 0;
}