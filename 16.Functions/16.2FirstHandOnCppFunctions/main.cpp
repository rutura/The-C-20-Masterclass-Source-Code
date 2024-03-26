#include <fmt/format.h>

//Function that takes a single parameter, and doesn't 
//give back the result explicitly
void enter_bar(size_t age){ // Functions parameters
    if( age > 18){
        fmt::println( "You're {} years old. Please proceed.", age );
    }else{
        fmt::println( "Sorry, you're too young for this. No offense! " );
    }
    return ;
}


//Function that takes multiple parameters and returns the result of the computation
int max( int a, int b){
    if(a>b)
        return a;
    else
        return b;
}

//Function that doesnt' take parameters and returns nothing
void say_hello(){
    fmt::println( "Hello there" );
    return; // You could omit this return statement for functions returning void
}


//Function that takes no parameters and return something
int lucky_number(){
    return 99;
}


//Parameters passed this way are scoped localy in the function.
//Changes to them are not visible outside the function. What we
//have inside the function are actually COPIES of the arguments
//passed to the function.
double increment_multiply( double a ,double b){
	
	fmt::println( "Inside function , before increment : " );
	fmt::println( "a : {}" , a );
	fmt::println( "b : {}" , b );
    
    double result = ((++a)  * (++b));
    
	fmt::println( "Inside function , after increment : " );
	fmt::println( "a : {}" , a );
	fmt::println( "b : {}" , b );
    
    //Returning the result
    return result;
}



int main(){
    //Calling enter_bar
    /*
    //enter_bar(22); // Function arguments
    //enter_bar(15);

    for(size_t i{1} ; i < 20 ; ++i){
        enter_bar(i);
    }
    */

   //Calling max
   /*
   int x{22};
   int y{44};
   int result = max(100,20); // Arguments
   result = max(x,y);
   fmt::println( "max : {}" , result );
   */
  

  //Calling say_hello
  /*
  say_hello();
  */

    //Calling lucy_number
    /*
    int result{};
    result = lucky_number();
    fmt::println( "result : {}" , result );
    */

    double h{3.00};
    double i{4.00};
							
	fmt::println( "Outside function , before increment : " );
	fmt::println( "h : {}" , h );
	fmt::println( "i : {}" , i );
    
    double incr_mult_result = increment_multiply(h,i);
    
	fmt::println( "Outside function , before increment : " );
	fmt::println( "h : {}" , h );
	fmt::println( "i : {}" , i );




  
    return 0;
}