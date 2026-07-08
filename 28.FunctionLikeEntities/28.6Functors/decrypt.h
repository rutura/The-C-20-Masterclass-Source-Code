#ifndef DECRYPT_H
#define DECRYPT_H

//Functor or function object

class Decrypt
{
public:
    char operator()( const char& param){
         return static_cast<char> (param - 3);
    }
};

#endif // DECRYPT_H
