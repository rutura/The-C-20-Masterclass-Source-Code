module;

#include <string_view>
#include <string>
#include <fmt/format.h>

export module utilities; 

import functors;

export void print_msg(std::string_view msg) {
	fmt::println("{}",msg);
}


export void functors_demo(){

	std::string str{ "Hello" };

	fmt::println("Modifying string through function pointers : ");
	fmt::println("Initial : {}", str);
	fmt::println("Encrypted : {}", functors::modify(str, functors::encrypt));
	fmt::println("Decrypted : {}", functors::modify(str, functors::decrypt));

	fmt::println("------");

	// Using functors
	functors::Encrypt encrypt_functor;
	functors::Decrypt decrypt_functor;

	fmt::println("encrypt_functor : {}", encrypt_functor('A'));// D
	fmt::println("decrypt_functor : {}", decrypt_functor('D'));// A


	fmt::println("-----");

	fmt::println("Modifying string through functors : ");
	fmt::println("Initial : {}", str);
	fmt::println("Encrypted : {}", modify(str, encrypt_functor));
	fmt::println("Decrypted : {}", modify(str, decrypt_functor));	
}