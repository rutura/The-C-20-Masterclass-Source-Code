#ifndef NUMBER_H
#define NUMBER_H

#include <iostream>
class Number
{
    friend std::ostream& operator<<(std::ostream& out , const Number& number);

    //Comparison operators
    friend bool operator<(const Number& left_operand, const Number& right_operand);
    friend bool operator<(int left_operand, const Number& right_operand);
    friend bool operator<(const Number& left_operand, int right_operand);

    friend bool operator==(const Number& left_operand, const Number& right_operand);
    friend bool operator==(int left_operand, const Number& right_operand);
    friend bool operator==(const Number& left_operand, int right_operand);

    friend bool operator>(const Number& left_operand, const Number& right_operand);
    friend bool operator>(int left_operand, const Number& right_operand);
    friend bool operator>(const Number& left_operand, int right_operand);

    friend bool operator>=(const Number& left_operand, const Number& right_operand);
    friend bool operator>=(int left_operand, const Number& right_operand);
    friend bool operator>=(const Number& left_operand, int right_operand);

    friend bool operator<=(const Number& left_operand, const Number& right_operand);
    friend bool operator<=(int left_operand, const Number& right_operand);
    friend bool operator<=(const Number& left_operand, int right_operand);

    friend bool operator!=(const Number& left_operand, const Number& right_operand);
    friend bool operator!=(int left_operand, const Number& right_operand);
    friend bool operator!=(const Number& left_operand, int right_operand);
public:
	Number() = default;
	explicit Number(int value );
          
	//getter
	int get_wrapped_int() const{
            return m_wrapped_int;
	}

    ~Number();
private : 
    int m_wrapped_int{0};
};


#endif // NUMBER_H
