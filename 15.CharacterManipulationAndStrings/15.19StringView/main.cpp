#include <iostream>
#include <string_view>
#include <cstring>


int main(){

    //Showing the problem
    /*
    std::string string {"Hello"};
    std::string string1 {string}; // Copy
    std::string string2 {string}; // Copy
    
    std::cout  << "address of string : " <<  &string << std::endl;
    std::cout  << "address of string1 : " <<  &string1 << std::endl;
    std::cout  << "address of string2 : " <<  &string2 << std::endl;
    */


   //Using string_view
   /*
    std::string_view sv {"Hellooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"};
    std::string_view sv1 {sv}; // View viewing the hello literal
    std::string_view sv2 {sv1}; // Another view viewing hello 
    
    std::cout << "Size of string_view : " << sizeof(std::string_view) << std::endl;
    std::cout << "size of sv1 : " << sizeof(sv1) << std::endl;
    
    std::cout << "sv : " << sv << std::endl;
    std::cout << "sv1 : " << sv1 << std::endl;
    std::cout << "sv2 : " << sv2 << std::endl;
    */


   //Constructing string_view's
   /*
    std::string string3 {"Regular std::string"};
    const char * c_string {"Regular C-String"};
    const char char_array[]{"Char array"}; // Null terminated
    char char_array2[]{'H','u','g','e'}; // Non null terminated char array

    std::string_view sv3{"String litteral"};
    std::string_view sv4{string3};
    std::string_view sv5{c_string};
    std::string_view sv6{char_array};
    std::string_view sv7{sv3}; 
    std::string_view sv8{char_array2,std::size(char_array2)};//Non null terminated char array
                                                             //Need to pass in size info
    std::cout << "sv3 : " << sv3 << std::endl;
    std::cout << "sv4 : " << sv4 << std::endl;
    std::cout << "sv5 : " << sv5 << std::endl;
    std::cout << "sv6 : " << sv6 << std::endl;
	std::cout << "sv7 (constructed from other string_view) : " << sv7 << std::endl;
    std::cout << "Non null terminated string with std::string_view : " << sv8 << std::endl;
    */

   //Changes to the original string are reflected in the string_view
   /*
    char word [] {"Dog"};
    std::string_view sv9{word};
    
    std::cout << "word : " << sv9 << std::endl;
    
	std::cout << "Changing data... " << std::endl;
    //Change the data
    word[2] = 't';
    
    std::cout << "word : " << sv9 << std::endl;
    */

   //Changing the view window : SHRINKING
   /*
    const char * c_string1 { "The animals have left the region" };
    std::string_view sv10{c_string1};
    
    std::cout << "sv10 : " << sv10 << std::endl;
    
    sv10.remove_prefix(4); // Removes "The"
    
	//Prints : animals have left the region
    std::cout << "View with removed prefix(4) : " << sv10 << std::endl;
    
    sv10.remove_suffix(10); // Removes "the region"
    
	//Prints : animals have left
    std::cout << "View with removed suffix(10) : " << sv10 << std::endl;
    
    //Changing the view doesn't change the viewed string : 
    std::cout << "Original sv10 viewed string : " << c_string1 << std::endl;
    */


   //String_view shouldn't outlive whatever it is viewing
   /*
    std::string_view sv11;
    
    {
        std::string string4{"Hello there"};
        sv11 = string4;
        std::cout << "INSIDE --- sv11 is viewing : " << sv11 << std::endl;
        
        
        //string4 goes out of scope here.
    }
    std::cout << "OUTSIDE --- sv1 is viewing : " << sv11 << std::endl;
    */


   //data
   /*
    std::string_view sv13 {"Ticket"};
    std::cout << "sv13 : " << sv13 << std::endl;
    std::cout << "std::strlen(sv13.data()) : " << std::strlen(sv13.data()) << std::endl;
    */


   //Don't use data() on a modified view (through remove_prefix or remove_suffix)
   /*
	std::string_view sv14 {"Ticket"};
    sv14.remove_prefix(2);
    sv14.remove_suffix(2);
    
    //Length info is lost when you modify the view
    std::cout << sv14 << " has " << std::strlen(sv14.data()) << " characters(s)" << std::endl;
    std::cout << "sv14.data() is " << sv14.data() << std::endl;
    std::cout << "sv14 is " << sv14 << std::endl;
    */


   //Don't view non null terminated strings
   /*
    char char_array3[] {'H','e','l','l','o'};
    std::string_view sv15 {char_array3,std::size(char_array3)};
    
    std::cout << sv15 << " has " << std::strlen(sv15.data()) << " characters(s)" << std::endl;
    std::cout <<"sv15.data is  : " <<  sv15.data() << std::endl;
    std::cout << "sv15 is : " << sv15 << std::endl;
    */


   //std::string behaviors
	std::string_view sv16{"There is a huge forest in that area"};
    
    std::cout << "sv16 is " << sv16.length() << " characters long" << std::endl;
    std::cout << "The front character is : " << sv16.front() << std::endl;
    std::cout << "The back character is : " << sv16.back() << std::endl;
    std::cout << "Substring : " << sv16.substr(0,22) << std::endl;


    return 0;
}