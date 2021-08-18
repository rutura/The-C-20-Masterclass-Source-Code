#include <iostream>
#include <string>

int main(){

	//Replacing (1)
    //basic_string& replace( size_type pos, size_type count,const basic_string& str );
    //Replace the range [pos, pos + count] with str
	/*
	std::string str1 {"Finding Nemo"}; // Replace Finding with 'Searching For'
	std::string str1_2 {"Searcing For"};
	std::cout << "str1 : " << str1 << std::endl;
	
	std::cout << "Replacing..." << std::endl;
    str1.replace(0,7,str1_2);
	
    std::cout << "str1 : " << str1 << std::endl;
    */

   	//Replacing - (2)
    //basic_string& replace( size_type pos, size_type count,
                       //const basic_string& str,
                       //size_type pos2, size_type count2 = npos );
    /*                   
    //Replace in part of str, not its entirety
	std::string str2 {"Finding Nemo"};
    std::string str3 {"The Horse was Found in the Fields Searching For Food"};
	
	std::cout << "str2 : " << str2 << std::endl;
	
	std::cout << "Replacing..." << std::endl;
    str2.replace(0,7,str3,34,13);
	
    std::cout << "str2 : " << str2 << std::endl;
    */

    //Copying
    //size_type copy( CharT* dest,size_type count,size_type pos = 0)
	//Copy a subsection of *this string to dest. Dest is pre-allocated
	// The resulting character string is not null-terminated. Be careful
    /*
    std::string str4{"Climbing Kirimanjaro"};
    char txt4[15] {}; //Initialized with zero equivalent for characters which is '\0'
    std::cout << "std::size(txt4) : " << std::size(txt4) << std::endl;
    std::cout << "txt4 : " << txt4 << std::endl;
	
	std::cout << "Copying..." << std::endl;
    str4.copy(txt4,11,9);
	
	//Safe to print because the char array was initialized with '\0' s.
    std::cout << "txt4 : " << txt4 << std::endl;
    */


	//Resizing
    //std::resize(
    /*
    std::string str5{"Hello"};
	
    std::cout << "null char : " << '\0' << std::endl;
	std::cout << "str5 : " << str5 << std::endl;
    std::cout << "str5.size() : " << str5.size() << std::endl;
    std::cout << "str5.capacity() : " << str5.capacity() << std::endl;
	
	std::cout << "Resizing..." << std::endl;
    str5.resize(8); // This fills new char place holders with
						//null character by default, you can't print and see them
    
	std::cout << "str5 : " << str5 << std::endl;
    std::cout << "str5.size() : " << str5.size() << std::endl;
    std::cout << "str5.capacity() : " << str5.capacity() << std::endl;
	
	//Prove that they are indeed null characters
    std::cout << "Printing through loop : " << std::endl;
	for(size_t i{} ; i < str5.size() ; ++i){
		std::cout << i << ":" << str5[i] << std::endl;
	}


    //Resize and specify autofill character
    std::cout << "Resize and specify autofill character : " << std::endl;
    str5.resize(10,'*');
	std::cout << "str5 : " << str5 << std::endl;
    std::cout << "str5.size() : " << str5.size() << std::endl;
    std::cout << "str5.capacity() : " << str5.capacity() << std::endl;


    //Resize down
    std::cout << "Resize down : " << std::endl;
    str5.resize(5);
	std::cout << "str5 : " << str5 << std::endl;
    std::cout << "str5.size() : " << str5.size() << std::endl;
    std::cout << "str5.capacity() : " << str5.capacity() << std::endl;
    */


    //Swapping
	std::string str_a{"This is a string stored in A"};
    std::string str_b{"This is a string stored in B and it's really great to be able to do that."};
    
    //Before swap
    std::cout << "str_a : " << str_a << std::endl;
    std::cout << "str_b : " << str_b << std::endl;
	std::cout << "str_a.size() :" << str_a.size() << std::endl;
	std::cout << "str_a.capaity() : " << str_a.capacity() << std::endl;
	std::cout << "str_b.size() :" << str_b.size() << std::endl;
	std::cout << "str_b.capaity() : " << str_b.capacity() << std::endl;
    
	std::cout << "Swapping..." << std::endl;
    str_a.swap(str_b);
    
    //After swap
    std::cout << "str_a : " << str_a << std::endl;
    std::cout << "str_b : " << str_b << std::endl;
	std::cout << "str_a.size() :" << str_a.size() << std::endl;
	std::cout << "str_a.capaity() : " << str_a.capacity() << std::endl;
	std::cout << "str_b.size() :" << str_b.size() << std::endl;
	std::cout << "str_b.capaity() : " << str_b.capacity() << std::endl;

    














  
    return 0;
}