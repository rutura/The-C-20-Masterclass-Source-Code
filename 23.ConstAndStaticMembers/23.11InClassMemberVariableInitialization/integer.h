#ifndef INTEGER_H
#define INTEGER_H

class Integer
{
public:
	explicit Integer(int value);
	Integer(){
		std::cout << "Default constructor for Integer called" << std::endl;
	}
	~Integer();
	
	int get_value () const{
		return inner_int;
	}
	
	void set_value(int new_val){
		inner_int = new_val;
	}
	
private : 
	int inner_int{};

};

#endif // INTEGER_H
