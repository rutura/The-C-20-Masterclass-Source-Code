#include <iostream>



class SomethingIsWrong{
public : 
    SomethingIsWrong(const std::string& s) 
        : m_message(s)
        {
        }
        
    //Copy Constructor
    SomethingIsWrong(const SomethingIsWrong& source){
        std::cout << "Copy constructor for SomethingIsWrong called" << std::endl;
        m_message = source.m_message;
    }
    
    //Destructor
    ~SomethingIsWrong(){
        std::cout << "SomethingIsWrong destructor called" << std::endl;
    }
    const std::string& what()const{
        return m_message;
    }
private : 
    std::string m_message;
};


void do_something(size_t i){
      if(i == 2){
          throw SomethingIsWrong("i is 2");
      }
      std::cout << "Doing something at iteration : " << i << std::endl;
}



int main(){

    for(size_t i{0}; i < 5 ; ++i){
        
      try{
          do_something(i);
      }
      catch(SomethingIsWrong& ex){
          std::cout << "Exception cought : " << ex.what() << std::endl;
      }
    }
   
    return 0;
}