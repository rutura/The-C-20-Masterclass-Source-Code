#include <fmt/format.h>
#include <string>


int main(){

	//Find(1)
    //std::string::find()
    //size_type find( const basic_string& str, size_type pos = 0 ) const
    //Finds the starting index where the str substring is found in
	//the string where we call the method.
    /*
    std::string string1{"Water was poured in the heater"};
    std::string search_for{"ter"};
    
    size_t found_pos = string1.find(search_for);
    fmt::println( "find('ter') : index [{}]",  found_pos);// index : 2
	
    //find red
    search_for = "red";
    found_pos = string1.find(search_for);
    fmt::println( "find('red') : index [{}]", found_pos);// 13

    //Find something that isn't there
    search_for = "chicken";
    found_pos = string1.find(search_for);
    fmt::println( "find('chicken') : index [{}]", found_pos  );//huge number

    //std::string::npos
    fmt::println( "npos : {}" , std::string::npos );

    size_t large = -1;
    fmt::println( "large : {}" , large );
    */



     //Using std::string::npos to check if search was successfull or failed
    /*
    std::string string1{"Water was poured in the heater"};
    std::string search_for{"red"};
    
    size_t found_pos = string1. find(search_for);
    if(found_pos == std::string::npos){
        fmt::println( "Could not find the string 'red' : " );
    }else{
        fmt::println( "'red' found starting at position : {}",  found_pos );
    }
	
	
	//Search for chicken and check result against std::string::npos
    search_for = "chicken";
    found_pos = string1.find(search_for);
    
    if(found_pos == std::string::npos){
        fmt::println( "Could not find the string 'chicken'. " );
    }else{
        fmt::println( "'chicken' found starting at position : {}",  found_pos );
    }
    */




	//Find(2)	
	//Can specify the position where we want the search to start
    //using the second parameter of the method
    /*std::string string1{"Water was poured in the heater"};
    std::string search_for{"ter"};

    size_t found_pos = string1.find(search_for); 
    fmt::println( "ter found at position : {}",  found_pos );
    
    found_pos = string1.find(search_for,0);
    fmt::println( "ter found at position : {}",  found_pos );
    
    found_pos = string1.find(search_for,10);
    fmt::println( "ter found at position : {}",  found_pos );*/


	//Find(3)
	//size_type find( const CharT* s, size_type pos = 0 ) const;
	//Finds the first substring equal to the character string pointed to by s
	//pos : the position where we start searching in the std::string
	
	std::string string2 = "beer is packaged by her in beer cans around here.";
	const char * c_string2{"her"};
	
	size_t found_pos = string2.find(c_string2,2);
	if( found_pos!= std::string::npos){
		fmt::println(  "{} found at position : {}", c_string2, found_pos );
	}else{
        fmt::println( "Could not find the string :  {}", (c_string2) );
	}

    return 0;
}