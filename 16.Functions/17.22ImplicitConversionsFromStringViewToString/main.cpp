#include <iostream>
void say_my_name(const std::string& name);
void process_name(std::string_view name_sv);

int main(){

    process_name("Daniel");
   
    return 0;
}

//Definitions
void say_my_name(const std::string& name){
    std::cout << "Your name is " << name << std::endl;
}

void process_name(std::string_view name_sv){
    
	say_my_name(name_sv); // Compiler error . Implicit conversion
						  // from std::string_view
                          // to std::string is not  allowed.
                          
    //Fix : Be explicit about the conversion
    //say_my_name(std::string(name_sv));
    
    
}