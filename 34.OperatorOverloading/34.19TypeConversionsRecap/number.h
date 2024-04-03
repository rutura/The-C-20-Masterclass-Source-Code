#ifndef NUMBER_H
#define NUMBER_H

#include <fmt/format.h>
class Point;
class Number
{
    friend std::ostream& operator<<(std::ostream& out , const Number& number);
    friend struct fmt::formatter<Number>;
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

template<>
struct fmt::formatter<Number>
{
  constexpr parse(format_parse_context& ctx){return  ctx.begin();}
  template<typename FormatContext>
  auto format(const Number& obj, FormatContext& ctx){
    return format_to(ctx.out(), "Number : [{}]", obj.m_wrapped_int);
  }
};


#endif // NUMBER_H
