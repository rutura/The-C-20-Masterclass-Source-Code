#include "boxcontainer.h"


BoxContainer::BoxContainer(size_t capacity)
{
	m_items = new value_type[capacity];
	m_capacity = capacity;
	m_size =0;
}

BoxContainer::BoxContainer(const BoxContainer& source)
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

BoxContainer::~BoxContainer()
{
	delete[] m_items;
}

std::ostream& operator<< (std::ostream& out, const BoxContainer& box){

	out << "BoxContainer : [ size :  " << box.m_size
		<< ", capacity : " << box.m_capacity << ", items : " ;

	for(size_t i{0}; i < box.m_size; ++i){
		out << box.m_items[i] << " " ;
	}
	out << "]";
	return out;
}

