#include <fmt/format.h>


int find_character_v0(const std::string & str, char c){
    //If found , return the index, else return -1
    int not_found {-1};
    for (size_t i{} ; i < str.size()  ; ++i){
        if(str.c_str()[i] == c){
            return i;
        }
    }
    return not_found;
}


void find_character_v1(const std::string & str, char c, bool & success){
    //If found set success to true, else set to false
    for (size_t i{} ; i < str.size()  ; ++i){
        if(str.c_str()[i] == c){
            success = true;
            return;
        }
    }
    success = false;
}



int main(){

	std::string str1 {"Hello World in C++20!"};
	char c{'r'};


    /*
    int index =  find_character_v0(str1,c);

    if((find_character_v0(str1,c))!=-1){
        fmt::println( "Found character {} at index : {}", c ,index );
    }else{
       fmt::println( "Didn't find our character" );
    }
    */

   bool success{false};

   find_character_v1(str1,c,success);

   if(success){
         fmt::println( "Found character {}  in our string ", c);
   }else{
       fmt::println( "Didn't find our character" );
   }
   
    return 0;
}