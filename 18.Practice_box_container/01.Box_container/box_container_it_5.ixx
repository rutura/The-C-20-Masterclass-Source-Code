/*
    . Making BoxContainer a template class
    . Modernizing the code
        . Using std::unique_ptr for automatic memory management
        . Because smart pointers are managing memory, we don't need to write a destructor
            . we can just default it.
        . We also use templates and show a rather practical example of using concepts
        . We also use standard algorithms like std::copy and std::move to reduce boilerplate code
        
    
*/
module;

#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>
#include <span>
#include <stdexcept>
#include <concepts>

export module box_container_it_5;

import stream_insertable;

namespace iteration_5{

    // Concept to constrain the types that can be used in BoxContainer
    export template <typename T>
    concept cout_printable = requires(T a, std::ostream& out) {
        { out << a } -> std::same_as<std::ostream&>;
    };

    export template <typename T>
    concept BoxItem = std::copyable<T> && std::equality_comparable<T> && std::movable<T> && cout_printable<T>;

    // Template class to make BoxContainer flexible for any type T
    export template<BoxItem T>
    class BoxContainer: public StreamInsertable {
        using value_type = T;
        static constexpr size_t DEFAULT_CAPACITY = 30;  
        static constexpr size_t DUMMY_ITEM_COUNT = 10;

    public:
        // Constructors and assignment operators
        BoxContainer(size_t capacity = DEFAULT_CAPACITY);
        BoxContainer(const BoxContainer& source); // Copy constructor
        BoxContainer(BoxContainer&& source) noexcept;  // Move constructor
        BoxContainer& operator=(BoxContainer source);  // Copy assignment using copy-and-swap idiom
        BoxContainer& operator=(BoxContainer&& source) noexcept;    // Move assignment
        ~BoxContainer() = default;

        // Member functions
        void add(const value_type& item);     // Add item
        void expand(size_t new_capacity);     // Expand capacity
        bool remove_item(const value_type& item);    // Remove first occurrence
        size_t remove_all(const value_type& item);   // Remove all occurrences

        // Operator overloads
        BoxContainer operator+(const BoxContainer& other) const;  // operator+
        BoxContainer& operator+=(const BoxContainer& other);  // operator+=

        // Stream insert for pretty printing
        void stream_insert(std::ostream& out) const;

        // Getters
        size_t size() const noexcept { return m_size; }
        size_t capacity() const noexcept { return m_capacity; }

    private:
        std::unique_ptr<value_type[]> m_items;  // Use unique_ptr for automatic memory management
        size_t m_capacity;
        size_t m_size;
    };

    // Constructor with default capacity
    template<BoxItem T>
    BoxContainer<T>::BoxContainer(size_t capacity)
        : m_items(std::make_unique<value_type[]>(capacity)), m_capacity(capacity), m_size(0) {}

    // Copy constructor
    template<BoxItem T>
    BoxContainer<T>::BoxContainer(const BoxContainer& source)
        : m_items(std::make_unique<value_type[]>(source.m_capacity)), m_capacity(source.m_capacity), m_size(source.m_size) {
        std::copy(source.m_items.get(), source.m_items.get() + source.m_size, m_items.get());
    }

    // Move constructor
    template<BoxItem T>
    BoxContainer<T>::BoxContainer(BoxContainer&& source) noexcept
        : m_items(std::move(source.m_items)), m_capacity(source.m_capacity), m_size(source.m_size) {
        source.m_capacity = 0;
        source.m_size = 0;
    }

    // Move assignment operator
    template<BoxItem T>
    BoxContainer<T>& BoxContainer<T>::operator=(BoxContainer&& source) noexcept {
        if (this != &source) {
            m_items = std::move(source.m_items);
            m_capacity = source.m_capacity;
            m_size = source.m_size;
            source.m_capacity = 0;
            source.m_size = 0;
        }
        return *this;
    }

    // Copy assignment using copy-and-swap idiom
    template<BoxItem T>
    BoxContainer<T>& BoxContainer<T>::operator=(BoxContainer source) {
        swap(source);
        return *this;
    }

    // Add method: Adds a new item to the container
    template<BoxItem T>
    void BoxContainer<T>::add(const value_type& item) {
        if (m_size >= m_capacity) {
            expand(m_capacity * 2);
        }
        m_items[m_size++] = item;
    }

    // Expand method: Expands the container when capacity is insufficient
    template<BoxItem T>
    void BoxContainer<T>::expand(size_t new_capacity) {
        auto new_items = std::make_unique<value_type[]>(new_capacity);
        std::copy(m_items.get(), m_items.get() + m_size, new_items.get());
        m_items = std::move(new_items);
        m_capacity = new_capacity;
    }

    // Remove the first occurrence of an item
    template<BoxItem T>
    bool BoxContainer<T>::remove_item(const value_type& item) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_items[i] == item) {
                std::move(m_items.get() + i + 1, m_items.get() + m_size, m_items.get() + i);
                --m_size;
                return true;
            }
        }
        return false;
    }

    // Remove all occurrences of an item
    template<BoxItem T>
    size_t BoxContainer<T>::remove_all(const value_type& item) {
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

    // Operator+ : Combines two BoxContainers into a new one
    template<BoxItem T>
    BoxContainer<T> BoxContainer<T>::operator+(const BoxContainer& other) const {
        BoxContainer<T> result(m_size + other.m_size);
        std::copy(m_items.get(), m_items.get() + m_size, result.m_items.get());
        std::copy(other.m_items.get(), other.m_items.get() + other.m_size, result.m_items.get() + m_size);
        result.m_size = m_size + other.m_size;
        return result;
    }

    // Operator+= : Appends items from another BoxContainer to the current one
    template<BoxItem T>
    BoxContainer<T>& BoxContainer<T>::operator+=(const BoxContainer& other) {
        if (m_size + other.m_size > m_capacity) {
            expand(m_size + other.m_size);
        }
        std::copy(other.m_items.get(), other.m_items.get() + other.m_size, m_items.get() + m_size);
        m_size += other.m_size;
        return *this;
    }

    // Pretty printing stream insert
    template<BoxItem T>
    void BoxContainer<T>::stream_insert(std::ostream& out) const {
        out << "BoxContainer : [ size : " << m_size
            << ", capacity : " << m_capacity << ", items : ";
        for (size_t i = 0; i < m_size; ++i) {
            out << m_items[i] << " ";
        }
        out << "]";
    }

    // Custom Point type with an output stream operator
    export struct Point {
        int x, y;

        // Stream insertion operator
        friend std::ostream& operator<<(std::ostream& out, const Point& p) {
            out << "(" << p.x << ", " << p.y << ")";
            return out;
        }

        // Equality operator
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

}   // namespace iteration_5