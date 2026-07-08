#ifndef BOX_CONTAINER_H
#define BOX_CONTAINER_H
#include "stream_insertable.h"

class BoxContainer : public StreamInsertable
{
		//typedef int value_type; // Allows us to change what's stored in the vector on the fly
								// Can make it store int, double,...
		using value_type = int;

        static const size_t DEFAULT_CAPACITY = 30;  
public:
	BoxContainer(size_t capacity = DEFAULT_CAPACITY);
	BoxContainer(const BoxContainer& source);
	~BoxContainer();
	
	//StreamInsertable Interface
	virtual void stream_insert(std::ostream& out)const override;
	
	// Helper getter methods
	size_t size( ) const { return m_size; }
	size_t capacity() const{return m_capacity;};
	
	//Method to just play around with the class for now. Will
	//show a proper way to store in data starting from the next lecture
	void dummy_initialize(){
		
		//Put in 10 items
		for(size_t i{}; i < 10; ++i){
			m_items[i] = i + 12;
		}
		//Set the size
		m_size = 10;
		
		//Using the default capacity
	}
	
private : 
	value_type * m_items;
	size_t m_capacity;
	size_t m_size;
};

#endif // BOX_CONTAINER_H
