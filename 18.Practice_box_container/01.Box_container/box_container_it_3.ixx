/*
    .#3: Removing items 
*/
module;

#include <iostream>

export module box_container_it_3;

import stream_insertable;

namespace iteration_3{

   export class BoxContainer : public StreamInsertable
    {
        using value_type = int;
        static constexpr size_t DEFAULT_CAPACITY = 30;  
        static constexpr size_t DUMMY_ITEM_COUNT = 10;

    public:
        BoxContainer(size_t capacity = DEFAULT_CAPACITY);
        BoxContainer(const BoxContainer& source); // Copy constructor
        BoxContainer& operator=(BoxContainer source);  // Copy assignment using copy-and-swap idiom
        BoxContainer(BoxContainer&& source) noexcept;  // Move constructor
        BoxContainer& operator=(BoxContainer&& source) noexcept;    // Move assignment
        ~BoxContainer();
        
        virtual void stream_insert(std::ostream& out) const override;

        size_t size() const { return m_size; }
        size_t capacity() const { return m_capacity; }

        void dummy_initialize();
        void add(value_type item);     // Add method
        void expand(size_t new_capacity); // Expand method

        // Remove items
        bool remove_item(const value_type& item);    // Remove first occurrence
        size_t remove_all(const value_type& item);   // Remove all occurrences

        // Swap function
        void swap(BoxContainer& other) noexcept;

    private:
        value_type* m_items;
        size_t m_capacity;
        size_t m_size;
    };

    // Constructor
    BoxContainer::BoxContainer(size_t capacity)
        : m_items(new value_type[capacity]), m_capacity(capacity), m_size(0) {}

    // Copy constructor
    BoxContainer::BoxContainer(const BoxContainer& source)
        : m_items(new value_type[source.m_capacity]), m_capacity(source.m_capacity), m_size(source.m_size) {
        std::copy(source.m_items, source.m_items + source.m_size, m_items);
    }

    // Move constructor
    BoxContainer::BoxContainer(BoxContainer&& source) noexcept 
        : m_items(source.m_items), m_capacity(source.m_capacity), m_size(source.m_size) {
        source.m_items = nullptr;
        source.m_size = 0;
        source.m_capacity = 0;
    }

    // Destructor
    BoxContainer::~BoxContainer() {
        delete[] m_items;
    }

    // Swap function for copy-and-swap idiom
    void BoxContainer::swap(BoxContainer& other) noexcept {
        std::swap(m_items, other.m_items);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_size, other.m_size);
    }

    // Copy assignment using copy-and-swap
    BoxContainer& BoxContainer::operator=(BoxContainer source) {
        swap(source);
        return *this;
    }

    // Move assignment
    BoxContainer& BoxContainer::operator=(BoxContainer&& source) noexcept {
        if (this != &source) {
            delete[] m_items;
            m_items = source.m_items;
            m_capacity = source.m_capacity;
            m_size = source.m_size;

            source.m_items = nullptr;
            source.m_size = 0;
            source.m_capacity = 0;
        }
        return *this;
    }

    // Add method: adds a new item to the container
    void BoxContainer::add(value_type item) {
        if (m_size >= m_capacity) {
            expand(m_capacity * 2);
        }
        m_items[m_size++] = item;
    }

    // Expand method: increases the capacity of the container
    void BoxContainer::expand(size_t new_capacity) {
        value_type* new_items = new value_type[new_capacity];
        std::copy(m_items, m_items + m_size, new_items);
        delete[] m_items;
        m_items = new_items;
        m_capacity = new_capacity;
    }

    // Remove the first occurrence of the item
    bool BoxContainer::remove_item(const value_type& item) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_items[i] == item) {
                // Shift all elements after the found item
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_items[j] = m_items[j + 1];
                }
                --m_size;
                return true;
            }
        }
        return false;
    }

    // Remove all occurrences of the item
    size_t BoxContainer::remove_all(const value_type& item) {
        size_t count = 0;
        for (size_t i = 0; i < m_size; ) {
            if (m_items[i] == item) {
                remove_item(item);
                ++count;
            } else {
                ++i;
            }
        }
        return count;
    }

    void BoxContainer::dummy_initialize() {
        for (size_t i{}; i < DUMMY_ITEM_COUNT && i < m_capacity; ++i) {
            m_items[i] = i + 12;
        }
        m_size = std::min(DUMMY_ITEM_COUNT, m_capacity);
    }

    void BoxContainer::stream_insert(std::ostream& out) const {
        out << "BoxContainer : [ size :  " << m_size
            << ", capacity : " << m_capacity << ", items : ";
        for (size_t i{0}; i < m_size; ++i) {
            out << m_items[i] << " ";
        }
        out << "]";
    }

}   //namespace iteration_3