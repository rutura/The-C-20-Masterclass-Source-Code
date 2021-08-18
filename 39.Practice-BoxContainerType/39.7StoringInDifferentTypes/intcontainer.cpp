#include "intcontainer.h"


IntContainer::IntContainer(size_t capacity)
{
	m_items = new value_type[capacity];
	m_capacity = capacity;
	m_size =0;
}

IntContainer::IntContainer(const IntContainer& source)
{
	//Set up the new box
	m_items = new value_type[source.m_capacity];
	m_capacity = source.m_capacity;
	m_size = source.m_size;
	
	//Copy the items over from source 
	for(size_t i{} ; i < source.size(); ++i){
		m_items[i] = source.m_items[i];
	}
}

IntContainer::~IntContainer()
{
	delete[] m_items;
}

void IntContainer::stream_insert(std::ostream& out)const{
	
	out << "IntContainer : [ size :  " << m_size
		<< ", capacity : " << m_capacity << ", items : " ;
			
	for(size_t i{0}; i < m_size; ++i){
		out << m_items[i] << " " ;
	}
	std::cout << "]";
}


void IntContainer::expand(size_t new_capacity){
	std::cout << "Expanding to " << new_capacity << std::endl;
	value_type *new_items_container;

	if (new_capacity <= m_capacity)
		return; // The needed capacity is already there
	
	//Allocate new(larger) memory
	new_items_container = new value_type[new_capacity];

	//Copy the items over from old array to new 
	for(size_t i{} ; i < m_size; ++i){
		new_items_container[i] = m_items[i];
	}
	
	//Release the old array
	delete [ ] m_items;
	
	//Make the current box wrap around the new array
	m_items = new_items_container;
	
	//Use the new capacity
	m_capacity = new_capacity;
}

void IntContainer::add(const value_type& item){
	if (m_size == m_capacity)
		//expand(m_size+5); // Let's expand in increments of 5 to optimize on the calls to expand
		expand(m_size + EXPAND_STEPS);
	m_items[m_size] = item;
	++m_size;
}


//Show that we could go through the trouble to copy the remaining
//right items to occupy the space left empty by the removed element, but
//we don't care about the order of elements in our box, the elements just
//have to be there and that's all. So we could just take the last element,
//put it in the slot left empty by the removed element and reduce the size
//of the box. The bool return type may seem useless, but sometimes, it's important
//to know if the call to remove_item actually removed the item or not. Well use
//this piece of information in the remove_all() method 
bool IntContainer::remove_item(const value_type& item){
	
	//Find the target item
	size_t index {m_capacity + 999}; // A large value outside the range of the current 
										// array
	for(size_t i{0}; i < m_size ; ++i){
		if (m_items[i] == item){
			index = i;
			break; // No need for the loop to go on
		}
	}
	
	if(index > m_size)
		return false; // Item not found in our box here
		
	//If we fall here, the item is located at m_items[index]
	
	//Overshadow item at index with last element and decrement m_size
	m_items[index] = m_items[m_size-1];
	m_size--;
	return true;
}


//Removing all is just removing one item, several times, until
//note is left, keeping track of the removed items.
size_t IntContainer::remove_all(const value_type& item){
	
	size_t remove_count{};
	
	bool removed = remove_item(item);
	if(removed)
		++remove_count;
	
	while(removed == true){
		removed = remove_item(item);
		if(removed)
			++ remove_count;
	}
	
	return remove_count;
}

void IntContainer::operator +=(const IntContainer& operand){
	
	//Make sure the current box can acommodate for the added new elements
	if( (m_size + operand.size()) > m_capacity)
		expand(m_size + operand.size());
		
	//Copy over the elements
	for(size_t i{} ; i < operand.m_size; ++i){
		m_items [m_size + i] = operand.m_items[i];
	}
	
	m_size += operand.m_size;
}


IntContainer operator +(const IntContainer& left, const IntContainer& right){
	IntContainer result(left.size( ) + right.size( ));
	result += left; 
	result += right;
	return result;	
}


void IntContainer::operator =(const IntContainer& source){
	value_type *new_items;

	// Check for self-assignment:
	if (this == &source)
            return;
/*
	// If the capacities are different, set up a new internal array
	//that matches source, because we want object we are assigning to 
	//to match source as much as possible.
	*/
	if (m_capacity != source.m_capacity)
	{ 
	    new_items = new value_type[source.m_capacity];
	    delete [ ] m_items;
	    m_items = new_items;
	    m_capacity = source.m_capacity;
	}
	
	//Copy the items over from source 
	for(size_t i{} ; i < source.size(); ++i){
		m_items[i] = source.m_items[i];
	}
	
	m_size = source.m_size;
}

