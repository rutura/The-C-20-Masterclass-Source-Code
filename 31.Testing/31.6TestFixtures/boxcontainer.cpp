#include "boxcontainer.h"

BoxContainer::BoxContainer(size_t capacity)
{
	m_items = new value_type[capacity];
	m_capacity = capacity;
	m_size = 0;
}

BoxContainer::BoxContainer(const BoxContainer& source)
{
	m_items = new value_type[source.m_capacity];
	m_capacity = source.m_capacity;
	m_size = source.m_size;

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

void BoxContainer::expand(size_t new_capacity){
	if (new_capacity <= m_capacity)
		return;

	value_type *new_items_container = new value_type[new_capacity];

	for(size_t i{} ; i < m_size; ++i){
		new_items_container[i] = m_items[i];
	}

	delete [ ] m_items;
	m_items = new_items_container;
	m_capacity = new_capacity;
}

void BoxContainer::add(const value_type& item){
	if (m_size == m_capacity)
		expand(m_size + 5);
	m_items[m_size] = item;
	++m_size;
}

bool BoxContainer::remove_item(const value_type& item){
	size_t index {m_capacity + 999};
	for(size_t i{0}; i < m_size ; ++i){
		if (m_items[i] == item){
			index = i;
			break;
		}
	}

	if(index > m_size)
		return false;

	m_items[index] = m_items[m_size-1];
	m_size--;
	return true;
}
