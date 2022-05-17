#include <iostream>
#include <exception>
#include <cstring>

class DivideByZeroException : public std::exception {
public :   
    DivideByZeroException(int a, int b) noexcept : std::exception(),m_a(a),m_b(b){}
	
     virtual const char* what() const noexcept override {
         /*
         //Some compilers will give a warning that we're returning the address of a local string
         //link : https://www.udemy.com/instructor/communication/qa/17488954/detail/?course=2987082
         return (std::string("Divide by zero detected , dividing ") +
            std::to_string(m_a) + std::string(" by ") +
                std::to_string(m_b)).c_str();
                */
               return"divide by zero detected, dividing ";
     }
     
     int get_a() const{
         return m_a;
     }
     
     int get_b() const{
         return m_b;
     }
     
private : 
     int m_a{};
     int m_b{};
    
};

int divide( int a, int b){
    
    if(b==0)
        throw DivideByZeroException(a,b);
        
    return a/b;
}


int main(){

    try{
        divide(10,0);
    }
    catch(std::exception& ex){
        
		
        //We know that the thrown exception contains a DivideByZeroException
        //part do ws can downcast safely and call non virtual functions
        /*
        DivideByZeroException * d_z = dynamic_cast<DivideByZeroException*> (&ex);
        if(d_z){
            std::cout<< ex.what() << ": dividing " << d_z->get_a() << 
                " by "<<  d_z->get_b() << std::endl;
        }
        */
       
       std::cout << ex.what() << std::endl;
		
    }
   
    return 0;
}