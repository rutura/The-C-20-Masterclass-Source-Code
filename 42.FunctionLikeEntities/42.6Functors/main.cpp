#include "decrypt.h"
#include "encrypt.h"
#include <fmt/format.h>


char encrypt(const char &param)
{// Callback function
  return static_cast<char>(param + 3);
}

char decrypt(const char &param)
{// Callback function
  return static_cast<char>(param - 3);
}


template<typename Modifier> std::string &modify(std::string &str_param, Modifier modifier)
{
  for (size_t i{}; i < str_param.size(); ++i) {
    str_param[i] = modifier(str_param[i]);// Calling the callback
  }
  return str_param;
}


int main()
{

  std::string str{ "Hello" };

  fmt::println("Modifying string through function pointers : ");
  fmt::println("Initial : {}", str);
  fmt::println("Encrypted : {}", modify(str, encrypt));
  fmt::println("Decrypted : {}", modify(str, decrypt));

  fmt::println("------");

  // Using functors
  Encrypt encrypt_functor;
  Decrypt decrypt_functor;

  fmt::println("encrypt_functor : {}", encrypt_functor('A'));// D
  fmt::println("decrypt_functor : {}", decrypt_functor('D'));// A


  fmt::println("-----");

  fmt::println("Modifying string through functors : ");
  fmt::println("Initial : {}", str);
  fmt::println("Encrypted : {}", modify(str, encrypt_functor));
  fmt::println("Decrypted : {}", modify(str, decrypt_functor));

  return 0;
}