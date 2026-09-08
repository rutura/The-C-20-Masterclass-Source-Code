#include <iostream>
#include <memory>

class Item{
public : 
     Item(){
        std::cout << "Item constructor called" << std::endl; 
     }
	 
     ~Item(){
         std::cout << "Item destructor called" << std::endl;
     }
};

class MyException{
public : 
	MyException() = default;
	
	//MyException(const MyException & ex) = delete;
public :
	MyException(const MyException & ex){
    
    }	
};

int main(){

    //Showing that that automatic local variables are destroyed when 
    //we are thrown out of a try block
	/*
    int a{10};
    int b{10};

    try{
        Item item; // When exception is thrown, control immediately exits the try block
                    // an automatic local variables are released
                    // But pointers may leak memory.
        if( b == 0 )
            throw 110;
        a++; // Just using a and b in here, could use them to do anything.
        b++;
        std::cout << "Code that executes when things are fine" << std::endl;
        
    } catch(int ex){
        std::cout << "Something went wrong. Exception thrown : " << ex <<  std::endl;
    }
   

    std::cout << "Done!" << std::endl;
    */


    //.Throwing a pointer : recipe for disaster
    //Throwing pointers is a recipe for disaster, as by the time
    //the catch block executes, the memory allocated and used in try 
    //block is pointing to invalid data. The program may seem to work
    //sometimes but there are no guarantees you'll always get valid stuff
    //if you dereference pointers allocated in the try block.
    /*
    
    int c{0};
    try{
        int var{55};
        int* int_ptr = &var;
        if(c == 0)
            throw int_ptr;
        std::cout << "Keeping doing some other things..." << std::endl;
    }catch(int* ex){
        std::cout << "Something went wrong. Exception thrown : " <<*ex << std::endl;
    }
	std::cout << "END." << std::endl;
    */


    //Potential memory leaks
    //The destructor for Item is never called when we're thrown out of the 
    //try block, and memory is leaked.
	/*
	int d{0};
    try{
        //Item * item_ptr = new Item();
        std::shared_ptr<Item> item_ptr = std::make_shared<Item>();
        if(d == 0)
            throw 0;
        std::cout << "Keeping doing some other things..." << std::endl;
    }catch(int ex){
        std::cout << "Something went wrong. Exception thrown : "<< ex << std::endl;
    }
	std::cout << "END." << std::endl;

    */

	//If you throw an exception and it's not handled anywhere in your code,
	//you'll get a hard crash
    /*
	throw 0;
	std::cout << "Doing something after we throw" << std::endl;
	
	std::cout << "END." << std::endl;
    */


	// If copy constructor is either deleted, protected or private, the 
	// object can't be thrown as exception. You'll get a compiler error.
	
	try{
		MyException e;
		throw e; // 
		
	}catch(MyException ex){
		
	}
	std::cout << "END." << std::endl;

    return 0;
}