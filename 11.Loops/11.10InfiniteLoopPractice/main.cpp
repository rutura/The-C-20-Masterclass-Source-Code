#include <fmt/format.h>
#include <iostream>

int main(){

	char operation; // +,-,*,/
    double operand1;
    double operand2;
    bool end {false};
    
    fmt::println( "Welcome to Awesome Calculator");
    
    while((end == false)){
		//Do some processing
        fmt::println( "--------------------------------------------" );
        fmt::println( "What operation do you want help with? " );
        fmt::println( "+,-,* and / are supported. Please choose one and type below");
        fmt::print( "Your operation : ");
        std::cin >> operation;
        
        fmt::println( "Please type in your two operands separated by a space and hit enter: ");
        std::cin >> operand1 >> operand2;

		switch(operation){
        case '+' : 
            fmt::println( "{} + {} = {}", operand1, operand2, (operand1 + operand2) );
            break;
        case '-' :
            fmt::println( "{} - {} = {}", operand1, operand2, (operand1 +- operand2) );
            break;
        case '*' :
            fmt::println( "{} * {} = {}", operand1, operand2, (operand1 * operand2) );
            break;
        case '/' :
            fmt::println( "{} / {} = {}", operand1, operand2, (operand1 / operand2) );
            break;
        default :
            fmt::println( "{} operation not supported", operation );
            break;
		}
	
		
        fmt::println( "Continue ? ( Y | N) : ");
        
        char go_on;
        std::cin >> go_on;
        
        //end = ((go_on == 'Y') || (go_on == 'y')) ? false : true;
        
        //You could also write the previous statement using if else
        if((go_on == 'Y') || (go_on == 'y')){
            end = false;
        }else{
            end = true;
        }
    }
    
    fmt::println( "Done helping out. BYE!" );

    return 0;
}