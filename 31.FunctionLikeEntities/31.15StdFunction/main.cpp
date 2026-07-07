#include <iostream>
#include <functional>
#include "boxcontainer.h"


//Function pointer
char encrypt(const char& param){
    return static_cast<char> (param + 3);
}

//Functor
class Decrypt
{
public:
    char operator()( const char& param){
         return static_cast<char> (param - 3);
    }
};


//Modifying a BoxContainer of strings
BoxContainer<std::string>& modify(BoxContainer<std::string>& sentence,
                                        //char(*modifier) (const char&)){
                                  std::function<char(const char&)> modifier){
    for(size_t i{}; i < sentence.size() ; ++i){
            
        //Code below relies on get_item() to return a reference
        //Loop through the word modifying each character 
        for(size_t j{} ; j < sentence.get_item(i).size(); ++j){
            sentence.get_item(i)[j] = modifier(sentence.get_item(i)[j]);
        }
    }
    return sentence;
}

std::string get_best (const BoxContainer<std::string>& sentence,
        // bool(*comparator)(const std::string& str1, const std::string& str2)){
        std::function<bool(const std::string& str1,const std::string& str2)> comparator){

    std::string best = sentence.get_item(0);
    for(size_t i{}; i < sentence.size() ; ++i){
            
        if(comparator(sentence.get_item(i),best)){
            best = sentence.get_item(i);
        }
            
    }
        
    return best;
}

//Function pointer
bool larger_in_size (const std::string& str1, const std::string& str2){
    if(str1.size() > str2.size())
        return true;
    else 
        return false;
}


int main(){

    //Basic usage of std::function : storing function like entities
    //in a unified way.
    std::function<char(const char&)> my_modifier;

    //Function pointer
    my_modifier = encrypt;
    std::cout << "A encrypted becomes : " << my_modifier('A') << std::endl; // D

    //Functor
    Decrypt decrypt;
    my_modifier = decrypt;
    std::cout << "D decrypted becomes : " << my_modifier('D') << std::endl;


    //Lambda function
    my_modifier = [](const char& param){
        return static_cast<char> (param + 3);
    };
    std::cout << "A encrypted becomes : " << my_modifier('A') << std::endl; // D



    std::cout << "--------" << std::endl;

    //Storing function like entities in a collection
    std::cout << std::endl;
    std::cout << "Collection of function like entities : " << std::endl;
    
    BoxContainer<std::function<char(const char&)>> func_entities;
    func_entities.add(encrypt); // Function pointer
    func_entities.add(decrypt); // Functor
    func_entities.add([](const char& param){ // Lambda function
        return static_cast<char> (param + 3);
    });
    
    for(size_t i{}; i < func_entities.size() ; ++i){
        std::cout << "result " << i << ". D transformed becomes : " << 
                func_entities.get_item(i)('D') << std::endl;
    }


    std::cout <<"--------" << std::endl;

    //std::function as callback 
    std::cout << std::endl;
    std::cout << "Modifying the quote : " << std::endl;
    BoxContainer<std::string> quote;
    quote.add("The");
    quote.add("sky");
    quote.add("is");
    quote.add("blue");
    quote.add("my");
    quote.add("friend");
    std::cout << "Initial : " <<  quote << std::endl;
    std::cout << "Encrypted : " << modify(quote,encrypt) << std::endl;
    std::cout << "Decrypted : " << modify(quote,decrypt) << std::endl;


    std::cout << "----------" << std::endl;

    std::cout << std::endl;
    std::cout << "Gettting the best : " << std::endl;
    
    auto  greater_lexicographically = [](const std::string& str1, const std::string& str2){
    return (str1>str2);
    };
    
    std::cout << "larger in size : " << get_best(quote,larger_in_size) << std::endl;
    std::cout << "greater lexicographicaly : " 
            << get_best(quote,greater_lexicographically) << std::endl;



  
    
    return 0;
}