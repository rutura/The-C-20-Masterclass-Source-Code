#include <fmt/format.h>

int main()
{

  int number1{ 75 };
  int number2{ 60 };
  bool result = (number1 < number2);// Expression yielding the condition

  /*

      fmt::println("result : {}" ,  result );

      fmt::println( "free standing if statement" );

  //if(result){
      if(result == true){
      fmt::println("{} is less than {}" , number1, number2 );
  }

  //if(!result){
      if(!(result == true)){
      fmt::println( " {}is NOT less than{} " , number1,number2 );
  }

  */


  // Using else
  /*
      fmt::println( "using the else clause : " );

      if(result == true){
      fmt::println(" {} is less than {}" , number1, number2 );
  }else{
      fmt::println( "{} is NOT less than {}" , number1, number2 );
  }
  */


  // Use expression as condition directly
  /*
      fmt::println( std::endl;
      fmt::println( "Using expression as condition : " );

      if(number1 < number2){
      fmt::println("{} is less than {}" ,number1, number2 );
  }else{
      fmt::println("{} is NOT less than {}" ,number1, number2 );
  }
  */


  // Nesting if statements
  fmt::println("Nesting if statements");

  bool red = false;
  bool green{ true };
  bool yellow{ false };
  bool police_stop{ true };

  /*
   *      If green : go
   *      If red, yellow : stop
   *      If green and police_stop : stop
   * */
  /*
  if(red){
      fmt::println( "Stop" );
  }
  if(yellow){
      fmt::println( "Slow down" );
  }
      if(green){
              fmt::println( "Go" );
      }
  */

  /*
       fmt::println( "Police officer stops(verbose)" );
       if(green){
       if(police_stop){
           fmt::println( "Stop" );
       }
       else{
           fmt::println( "Go" );
       }

   }
   */


  fmt::println("Police officer stops(less verbose)");
  if (green && !police_stop) {
    fmt::println("Go");
  } else {
    fmt::println("Stop");
  }


  return 0;
}