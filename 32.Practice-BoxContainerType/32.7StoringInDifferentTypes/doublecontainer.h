#ifndef DOUBLE_CONTAINER_H
#define DOUBLE_CONTAINER_H

#include "stream_insertable.h"

class DoubleContainer : public StreamInsertable
{
		using value_type = double; // Allows us to change what's stored in the vector on the fly
								// Can make it store int, double,...
        static const size_t DEFAULT_CAPACITY = 5;  
		static const size_t EXPAND_STEPS = 5;
public:
	DoubleContainer(size_t capacity = DEFAULT_CAPACITY);
	DoubleContainer(const DoubleContainer& source);
	~DoubleContainer();
	
	//StreamInsertable Interface
	virtual void stream_insert(std::ostream& out)const;
	
	// Helper getter methods
	size_t size( ) const { return m_size; }
	size_t capacity() const{return m_capacity;};
	
	
	//Method to add items to the box
	void add(const value_type& item);
	bool remove_item(const value_type& item);
	size_t remove_all(const value_type& item);
	
	//In class operators
	void operator +=(const DoubleContainer& operand);
	void operator =(const DoubleContainer& source);
	
private : 
	void expand(size_t new_capacity);
	
private : 
	value_type * m_items;
	size_t m_capacity;
	size_t m_size;
};

//Free operators
DoubleContainer operator +(const DoubleContainer& left, const DoubleContainer& right);


#endif // DOUBLE_CONTAINER_H
