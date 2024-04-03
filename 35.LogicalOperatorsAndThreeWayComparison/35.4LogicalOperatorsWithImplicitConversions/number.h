#ifndef NUMBER_H
#define NUMBER_H
#include <fmt/format.h>

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

/*
 - fmt output stream overloading for Point of int
 - Reference: https://fmt.dev/latest/api.html
 */
template <>
struct fmt::formatter<Number> : nested_formatter<int> {
	auto format(Number n, format_context& ctx) const {
		return write_padded(ctx, [=](auto out) {
		  return format_to(out, "Number : [{}]", nested(n.get_wrapped_int()));
		});
	}
};


#endif // NUMBER_H
