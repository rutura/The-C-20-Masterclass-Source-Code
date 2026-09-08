#include <iostream>

//Function that takes a single parameter, and doesn't 
//give back the result explicitly
void enter_bar(size_t age){ // Functions parameters
    if( age > 18){
        std::cout << "You're " << age << " years old. Please proceed." << std::endl;
    }else{
        std::cout << "Sorry, you're too young for this. No offense! " << std::endl;
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
    std::cout << "Hello there" << std::endl;
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
	
	std::cout << "Inside function , before increment : " << std::endl;
	std::cout << "a : " << a << std::endl;
	std::cout << "b : " << b << std::endl;
    
    double result = ((++a)  * (++b));
    
	std::cout << "Inside function , after increment : " << std::endl;
	std::cout << "a : " << a << std::endl;
	std::cout << "b : " << b << std::endl;
    
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
   std::cout << "max : " << result << std::endl;
   */
  

  //Calling say_hello
  /*
  say_hello();
  */

    //Calling lucy_number
    /*
    int result{};
    result = lucky_number();
    std::cout << "result : " << result << std::endl;
    */

    double h{3.00};
    double i{4.00};
							
	std::cout << "Outside function , before increment : " << std::endl;
	std::cout << "h : " << h << std::endl;
	std::cout << "i : " << i << std::endl;
    
    double incr_mult_result = increment_multiply(h,i);
    
	std::cout << "Outside function , before increment : " << std::endl;
	std::cout << "h : " << h << std::endl;
	std::cout << "i : " << i << std::endl;




  
    return 0;
}