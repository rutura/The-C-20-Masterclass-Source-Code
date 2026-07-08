#ifndef BOX_CONTAINER_H
#define BOX_CONTAINER_H
#include <iostream>

class BoxContainer
{
		friend std::ostream& operator<< (std::ostream& out, const BoxContainer& box);

		using value_type = int;

        static const size_t DEFAULT_CAPACITY = 30;
public:
	BoxContainer(size_t capacity = DEFAULT_CAPACITY);
	BoxContainer(const BoxContainer& source);
	~BoxContainer();

	size_t size( ) const { return m_size; }
	size_t capacity() const{return m_capacity;};

	void add(const value_type& item);
	bool remove_item(const value_type& item);

private :
	void expand(size_t new_capacity);

private :
	value_type * m_items;
	size_t m_capacity;
	size_t m_size;
};

#endif // BOX_CONTAINER_H
