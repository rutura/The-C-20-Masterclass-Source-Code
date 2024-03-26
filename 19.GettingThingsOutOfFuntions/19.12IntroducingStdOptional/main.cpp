#include <fmt/format.h>
#include <optional>



int main(){

	//Declare and initialize
    std::optional<int> items{3}; 
    std::optional<std::string> name{"Daniel Gakwaya"};
    std::optional<double> weight {77.2};
    std::optional<char> character{'s'};
	
	
	//Declare and empty initialize
    std::optional<std::string> dog_name {}; // Initializes to std::nullopt
    std::optional<int> age {std::nullopt}; // std::nullopt is the null or zero equivalent
											// for std::optional
	std::optional<char> letter = std::nullopt; 	// Triggers unused warning
	std::optional<double> height = {};		  	//Initializes to std::nullopt
												// Triggers unused warning.


    //Read from an std::optional variable
	fmt::println( "items : {}" , items.value() );
	fmt::println( "items : {}" , *items ); // Personaly find this confusing as
													// it's not a pointer, so this the 
													// first and last time I use it in the
													// course
    //fmt::println( "items : {}" , items );
	fmt::println( "name : {}" , name.value() );
	fmt::println( "weight : {}" , weight.value() );
	fmt::println( "character : {}" , character.value() );


    //Write stuff
	dog_name = "Fluffy";
	age = 26;
	
    fmt::println( "Writting data in ..." );
	fmt::println( "dog_name : {}" , dog_name.value() );
	fmt::println( "age : {}" , age.value() );


    //Reading bad data
	//fmt::println( letter.value() ); // Throws exception and crashes program
	//fmt::println( height.value() ); // Trhows exception and crashes program


    //has_value()
    fmt::println( "letter.has_value() : {}" , letter.has_value() );
    fmt::println( "height.has_value() : {}" , height.has_value() );
    fmt::println( "dog_name.has_value() : {}" , dog_name.has_value() );


    //Do your checks before you read data

    fmt::println( "Conditional reading" );
	if(letter.has_value()){
		fmt::println( "letter contains a useful value" );
	}else{
		fmt::println( "letter contains std::nullopt" );
	}
	
	//Checking against std::nullopt
	if(letter != std::nullopt){
		fmt::println( "letter contains a useful value" );
	}else{
		fmt::println( "letter contains std::nullopt" );
	}


    //Checking against std::nullopt
	if(dog_name != std::nullopt){
		fmt::println( "dog_name contains a useful value : {}" , dog_name.value() );
	}else{
		fmt::println( "dog_name contains std::nullopt" );
	}

    
    
    return 0;
}