#include <fmt/format.h>



class SomethingIsWrong{
public : 
    SomethingIsWrong(const std::string& s) 
        : m_message(s)
        {
        }
        
    //Copy Constructor
    SomethingIsWrong(const SomethingIsWrong& source){
        fmt::println( "Copy constructor for SomethingIsWrong called" );
        m_message = source.m_message;
    }
    
    //Destructor
    ~SomethingIsWrong(){
        fmt::println( "SomethingIsWrong destructor called" );
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
      fmt::println( "Doing something at iteration : {}" , i );
}



int main(){

    for(size_t i{0}; i < 5 ; ++i){
        
      try{
          do_something(i);
      }
      catch(SomethingIsWrong& ex){
          fmt::println( "Exception cought : {}" , ex.what() );
      }
    }
   
    return 0;
}