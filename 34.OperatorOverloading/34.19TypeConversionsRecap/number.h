#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
class Point;
class Number
{
    friend std::ostream& operator<<(std::ostream& out , const Number& number);
    //Arithmetic operators
    friend Number operator+(const Number& left_operand, const Number& right_operand);
    friend Number operator-(const Number& left_operand, const Number& right_operand);
    friend Number operator*(const Number& left_operand, const Number& right_operand);
    friend Number operator/(const Number& left_operand, const Number& right_operand);
    friend Number operator%(const Number& left_operand, const Number& right_operand);
		
public:
	Number() = default;
	Number(int value );
	
  
     //Type conversion operator from Number to Point
	  operator Point() const;
   
       
        //getter
        int get_wrapped_int() const{
            return m_wrapped_int;
        }
     
    ~Number();
    
private : 
    int m_wrapped_int{0};
};


#endif // NUMBER_H
