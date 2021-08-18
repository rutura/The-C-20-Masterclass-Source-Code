#include <iostream>
#include "dog.h"


void do_something_with_animal_ptr(Animal* animal){
	std::cout<< "In function taking base pointer..." << std::endl;
	Feline* feline_ptr = dynamic_cast<Feline*>(animal);
	
	if(feline_ptr){
		feline_ptr->do_some_feline_thingy();
	}else{
		std::cout << "Couldn't cast to Feline pointer,Sorry." << std::endl;
	}
	
}

void do_something_with_animal_ref(Animal & animal){
	std::cout << "In function taking base reference..." << std::endl;
	Feline* feline_ptr_1 {dynamic_cast<Feline*>(&animal)};
	if(feline_ptr_1){
		feline_ptr_1->do_some_feline_thingy();
	}else{
		std::cout << "Couldn't cast to Feline reference,Sorry." << std::endl;
	}
}

int main(){

	//Base class pointer
	 Animal* animal1 = new Feline("stripes","feline1");
	 //animal1->do_some_feline_thingy();


    std::cout << "-----------" << std::endl;

	//If the cast succeeds, we get a valid pointer back, 
	//if it fails, we get nullptr. So we can check before
	//calling stuff on the returned pointer
	Feline* feline_ptr = dynamic_cast<Feline*>(animal1);

    if(feline_ptr){
        feline_ptr->do_some_feline_thingy();
    }else{
        std::cout << "Couldn't do the transformation from Animal* to Dog*" << std::endl;
    }

    std::cout << "-----------" << std::endl;

    //Can do the transformation downstream for references

	//Base class reference
	Feline feline2 ("stripes", "feline2");
	Animal & animal_ref = feline2;
	
	//Calling non virtual methods on animal_ref won't work
	//animal_ref.do_some_feline_thingy();
	
	//Dog & feline_ref {dynamic_cast<Dog&>(animal_ref)};
	//feline_ref.do_some_dog_thingy();


    //Doing proper checks with references
	Dog* feline_ptr_1 {dynamic_cast<Dog*>(&animal_ref)};
	if(feline_ptr_1){
		feline_ptr_1->do_some_dog_thingy();
	}else{
		std::cout << "Couldn't cast to Dog reference,Sorry." << std::endl;
	}
 


    std::cout << "---------------" << std::endl;
    do_something_with_animal_ptr(animal1);
    do_something_with_animal_ref(animal_ref);


    std::cout << "----------------" << std::endl;
    /*
    int data{45};
    int data_ptr = &data;

    std::string data_str = dynamic_cast<std::string *>(data_ptr);
    */

    std::cout << "Done!" << std::endl;

    delete animal1;
     
    return 0;
}