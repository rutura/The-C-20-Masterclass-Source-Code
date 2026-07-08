#ifndef INT_CONTAINER_H
#define INT_CONTAINER_H

#include "stream_insertable.h"

class IntContainer : public StreamInsertable
{
		using value_type = int; // Allows us to change what's stored in the vector on the fly
								// Can make it store int, double,...
        static const size_t DEFAULT_CAPACITY = 5;  
		static const size_t EXPAND_STEPS = 5;
public:
	IntContainer(size_t capacity = DEFAULT_CAPACITY);
	IntContainer(const IntContainer& source);
	~IntContainer();

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
	void operator +=(const IntContainer& operand);
	void operator =(const IntContainer& source);
	
private : 
	void expand(size_t new_capacity);
	
private : 
	value_type * m_items;
	size_t m_capacity;
	size_t m_size;
};

//Free operators
IntContainer operator +(const IntContainer& left, const IntContainer& right);


#endif // INT_CONTAINER_H
