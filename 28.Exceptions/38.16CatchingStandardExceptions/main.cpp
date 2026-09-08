#include <iostream>


class Animal{
public : 
    Animal(const std::string n ) : m_name(n){}
	Animal() = default;
    virtual ~Animal(){}
    virtual void breathe()const{
		
	}
protected : 
    std::string m_name;
};

class Feline : public Animal{
    public : 
    Feline(const std::string n) : Animal(n){}
	
private : 
	int speed;
};



int main(){

    Animal animal;
    try{
        Feline& feline_ref = dynamic_cast<Feline&>(animal);
    }
    catch(std::exception& ex){
        std::cout << "Something is wrong : " << ex.what() << std::endl;       
    }

    std::cout << "END." << std::endl;

   
    return 0;
}