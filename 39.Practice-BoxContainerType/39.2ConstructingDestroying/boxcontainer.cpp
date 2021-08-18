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

void BoxContainer::stream_insert(std::ostream& out)const{
	
	out << "BoxContainer : [ size :  " << m_size
		<< ", capacity : " << m_capacity << ", items : " ;
			
	for(size_t i{0}; i < m_size; ++i){
		out << m_items[i] << " " ;
	}
	std::cout << "]";
}

