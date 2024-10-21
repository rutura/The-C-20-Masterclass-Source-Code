/*
     .#1: Constructing and destructing
        . The class is not a template
*/
module;

#include <iostream>

export module box_container_it_1;

import stream_insertable;

namespace iteration_1{

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
        //Loop through the source items and copy them to the new object
        /*
        for(size_t i{}; i < source.m_size; ++i) {
            m_items[i] = source.m_items[i];
        }
        */
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
        // Swap contents with the temporary (source) object
        swap(source);
        // Return *this after the swap
        return *this;
    }

    // Move assignment operator
    BoxContainer& BoxContainer::operator=(BoxContainer&& source) noexcept {
        if (this != &source) {

            //Release the current resources
            delete[] m_items;

            //Steal data from the source
            m_items = source.m_items;
            m_capacity = source.m_capacity;
            m_size = source.m_size;

            //Reset the source
            source.m_items = nullptr;
            source.m_size = 0;
            source.m_capacity = 0;
        }
        return *this;
    }

    void BoxContainer::dummy_initialize() {

        //The test below protects against cases where for example the capacity is 2 and DUMMY_ITEM_COUNT is 10
        //It will only initialize the first 2 items
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

} // namespace iteration_1