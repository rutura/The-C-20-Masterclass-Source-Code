#include <fmt/format.h>
#include <string>

int main()
{

  // Concatenating two strings : The + operator
  /*fmt::println("");
  fmt::println( "Concatenating two strings : " );

  std::string str1{"Hello"};
  std::string str2{"World"};

  std::string message = str1 + " my " + str2;

  fmt::println( "message : {}", message );*/

  // Concatenating string literals : No, No - Compiler Error
  // String literals are expanded into const char* arrays and C++ doesn't know
  // how to add arrays with the + operator. Hence the compiler error.
  /*fmt::println("");
  fmt::println( "Concatenating string literals : No,No! Compiler Error " );

  //std::string str3 { "Hello" + "World"}; // Compiler Error
  //std::string str4 = "Hello" + "World";  // Compiler Error*/

  // A few ways around string literal concatenation
  /*fmt::println("");
  fmt::println( "A few ways around string literal concatenation" );

  std::string str5 {"Hello World"}; 	// Make the string one literal
                                                                          //in the first place
  std::string str6 {"Hello" " World"};// Put the literals side by side
                                                                          //without the + in between
  std::string str7{std::string{"Hello"} + " World"};//Turn one or both into a std::string
                                                                                                   //object  and do the
  concatenation fmt::println( "str5 : {}",  str5 ); fmt::println( "str6 : {}",  str6 ); fmt::println( "str7 : {}", str7
  );

  using namespace std::string_literals; // necessary for the s suffix
                                                                            // This polutes the namespace in main
  std::string str8 {"Hello"s + " World"};// Turn one or both into strings using the
                              //s suffix . the string_literals namespace has to be imported
                              //for this to work
  fmt::println( "str8 : {}",  str8 );

  //A better way to not polute the namespace
  std::string str9;
  {
          using namespace std::string_literals;
          str9 = "Hello"s + " World";
  }
  fmt::println( "str9 : {}", str9 );*/


  // std::string is a compound type, it has properties and behaviors
  // one of the behaviors is append. We access the behaviors using
  // the . operator after the std::string variable name
  /*fmt::println("");
  fmt::println( "Using the append method : " );
  std::string str10 {"Hello"};
  std::string str11 {" World"};
  std::string str12 = str10.append(str11);
  fmt::println( "str12 : {}", str12 );

  std::string str13{std::string{"Hello"}.append(" World")};
  fmt::println( "str13 : {}", str13 );*/


  // Append can do more than the + operator
  // The + operator is just a convenience for basic concatenation
  /*
  fmt::println("");
  fmt::println( "Append method can do more than + operator : " );
  std::string str14 {"Hello "};
  std::string str15 {str14.append(5,'?')}; // Appends 5 '?' characters
  fmt::println( "str15 : {}", str15 );


  std::string str16{"The world is our shared home."};
  std::string str17{"Hello "};
  std::string str18{str17.append(str16,4,5)};// Append a sub-section of another string
                                                                                          // starting from index 4 , 5
  characters fmt::println( "str18 : {}", str18 );

  //Direct output
  std::string str19{"Hello "};
  fmt::println( "Direct output : {}" , str19.append(str16,4,5) );
  */


  // Concatenating strings and characters
  /*fmt::println("");
  fmt::println( "Concatenating strings and characters : " );
  std::string str20 {"Hello"};
  std::string str21 {"World"};
  std::string str22 {str20 + ' ' + str21};// The space in between is a character
  fmt::println( "str22 : {}",  str22 );

  std::string str23 = "Hello";
  (str23 += ',') += ' ';
  fmt::println( "str23 : {}",  str23 );

  //Another solution
  std::string str24 = "Hello"; // Take out the , and space we added before.
  std::string str25 {"I am here to see you."};
  std::string str26 {str24 + ',' + ' ' + str25};
  fmt::println( "str26 : {}",  str26 );*/


  // Appending C-strings and char arrays
  fmt::println("");
  fmt::println("Appending C-Strings and char arrays : ");
  const char message1[]{ "World" };
  const char *message2{ "World" };

  fmt::println(" + char array : {}", std::string{ "Hello " } + message1);
  fmt::println(" + C-String : {}", std::string{ "Hello " } + message2);
  fmt::println("append char array : {}", std::string{ "Hello " }.append(message1));
  fmt::println("append C-String : {}", std::string{ "Hello " }.append(message2));

  // Concatenating std::strings and numbers

  std::string str26{ "Hello" };

  str26 += std::to_string(67.5f);// Treats 67 as a character code
                                 // When using the += operator, C++ knows to treat the
                                 // integer operand as a character code and append that to our
                                 // std::string. But what if we want the 67 appended to std::string
                                 // literally
  fmt::println("str26 : {}", str26);


  return 0;
}