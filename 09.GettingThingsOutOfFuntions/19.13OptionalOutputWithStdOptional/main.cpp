#include <iostream>
#include <optional>

std::optional<size_t> find_character_v2(const std::string & str, char c){
    //If found set the return index, else return an empty std::optional
    for (size_t i{} ; i < str.size()  ; ++i){
        if(str.c_str()[i] == c){
            return i;
        }
    }
   return {}; //Or std::nullopt
   //std::nullopt;
}


//Specify default character to  search for

std::optional<size_t> find_character_v3(const std::string & str,
										std::optional<char> c = std::nullopt){
    //If found set return index, else return empty
    //If c is specified, find it else just find 'z'
    /*
    char char_to_find;
    if(c.has_value()){
        char_to_find = c.value();
    }else{
        char_to_find = 'z'; // Will find z by default
    }
    */
   char char_to_find = c.value_or('z');
    
    for (size_t i{} ; i < str.size()  ; ++i){
        //std::cout << "str[i] : " << str.at(i) << " , c : " << c << std::endl;
        if(str.c_str()[i] == char_to_find){
            return i;
        }
    }
   return {};// Or std::nullopt
}



int main(){

	std::string str1 {"Hello World in C++20!"};
	char c{'C'};

    /*
    std::optional<size_t> result = find_character_v2(str1,c);

    if(result.has_value()){
        std::cout << "Found our character at index : " << result.value() << std::endl;
    }else{
        std::cout << "Didn't find our character" << std::endl;
    }
    */

	str1 = "Hello Worldz in C++20!";
	
	auto result1 = find_character_v3(str1,'o'); //Will search for 'z' if you don't specify 
											// the character so search for
	if(result1.has_value()){
		std::cout << "Found character 'o' at index " << result1.value() << std::endl;
	}else{
		std::cout << "Could not find character 'o' in the string : " << str1 << std::endl;
	}
   
    return 0;
}