#include <iostream>
#include "encrypt.h"
#include "decrypt.h"


char encrypt(const char& param){ // Callback function
    return static_cast<char> (param + 3);
}

char decrypt(const char& param){ // Callback function
    return static_cast<char> (param - 3);
}


template <typename Modifier>
std::string & modify(std::string& str_param,
                                        Modifier modifier)
{
     for(size_t i{} ; i < str_param.size() ; ++i){
        str_param[i] = modifier(str_param[i]); // Calling the callback
     }
     return str_param;
}


int main(){

    std::string str {"Hello"};
    
    std::cout << std::endl;
    std::cout << "Modifying string through function pointers : " << std::endl;
    std::cout << "Initial : " << str << std::endl;
    std::cout << "Encrypted : " <<  modify(str,encrypt) << std::endl;
    std::cout << "Decrypted : " << modify(str,decrypt) << std::endl;

    std::cout << "------" << std::endl;

    //Using functors
    Encrypt encrypt_functor;
    Decrypt decrypt_functor;
    
    std::cout << "encrypt_functor : " << encrypt_functor('A') << std::endl; // D
    std::cout << "decrypt_functor : " << decrypt_functor('D') << std::endl;// A


    std::cout << "-----" << std::endl;

    std::cout << std::endl;
    std::cout << "Modifying string through functors : " << std::endl;
    std::cout << "Initial : " << str << std::endl;
    std::cout << "Encrypted : " <<  modify(str,encrypt_functor) << std::endl;
    std::cout << "Decrypted : " << modify(str,decrypt_functor) << std::endl;
   
    return 0;
}