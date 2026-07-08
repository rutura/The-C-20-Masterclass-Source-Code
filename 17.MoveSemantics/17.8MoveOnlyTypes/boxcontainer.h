#ifndef BOX_CONTAINER_H
#define BOX_CONTAINER_H

#include <iostream>

class BoxContainer
{
	friend std::ostream& operator<< (std::ostream& out, const BoxContainer& box);

	using value_type = int;
	static const size_t DEFAULT_CAPACITY = 5;
	static const size_t EXPAND_STEPS = 5;
public:
	BoxContainer(size_t capacity = DEFAULT_CAPACITY);
	BoxContainer(const BoxContainer& source) = delete;//Copy constructor
	BoxContainer( BoxContainer&& source);//Move constructor
	~BoxContainer();

	// Helper getter methods
	size_t size( ) const { return m_size; }
	size_t capacity() const{return m_capacity;};

	value_type get_item(size_t index) const{
		return m_items[index];
	}

	//Method to add items to the box
	void add(const value_type& item);
	bool remove_item(const value_type& item);
	size_t remove_all(const value_type& item);

	//In class operators
	void operator +=(const BoxContainer& operand);
	void operator =(const BoxContainer& source) = delete; // Copy assignment operator
	BoxContainer& operator =( BoxContainer&& source); // Move assignment operator
	void invalidate(){
		m_items = nullptr;
		m_size = 0;
		m_capacity = 0;
	}
private :
	void expand(size_t new_capacity);
private :
	value_type * m_items;
	size_t m_capacity;
	size_t m_size;
};

//Free operators
BoxContainer operator +(const BoxContainer& left, const BoxContainer& right);

#endif // BOX_CONTAINER_H
