module;

#include <concepts>
#include <fmt/format.h>
#include <iostream>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

export module custom_iterators_04;

namespace custom_iterators_04{
  // BoxContainer class template definition
    export template <typename T>
    requires std::default_initializable<T> // Ensuring type T is default-initializable
    class BoxContainer {
        static constexpr size_t DEFAULT_CAPACITY = 5; // Default initial capacity of the container
        static constexpr size_t EXPAND_STEPS = 5;     // Steps to expand the container's capacity

    public:
        // Constructor with optional initial capacity
        BoxContainer(size_t capacity = DEFAULT_CAPACITY);

        // Copy constructor enabled only for copyable types (requires C++20)
        BoxContainer(const BoxContainer& source) requires std::copyable<T>;

        // Move constructor
        BoxContainer(BoxContainer&& source) noexcept;

        // Copy assignment operator, uses copy-and-swap idiom
        BoxContainer& operator=(const BoxContainer& source);

        // Move assignment operator
        BoxContainer& operator=(BoxContainer&& source) noexcept;

        // Destructor is defaulted, no manual cleanup needed
        ~BoxContainer() = default;

        // Output operator overload for BoxContainer, for pretty printing
        friend std::ostream& operator<<(std::ostream& out, const BoxContainer<T>& operand) {
            out << "BoxContainer : [ size : " << operand.m_size
                << ", capacity : " << operand.m_capacity << ", items : ";

            for (size_t i{ 0 }; i < operand.m_size; ++i) {
                out << operand.m_items[i] << " "; // Print each item
            }
            out << "]";
            return out;
        }

        // Returns the current number of elements in the container
        size_t size() const noexcept { return m_size; }

        // Returns the current capacity of the container
        size_t capacity() const noexcept { return m_capacity; }

        // Get item at index with bounds-checked access (throws if out of bounds)
        const T& get_item(size_t index) const {
            if(index >= m_size)
                throw std::out_of_range("Index out of bounds");
            return m_items[index];
        }

        // Adds a new item to the container, expands if needed
        void add(const T& item);

        // Removes the first occurrence of an item, returns true if found and removed
        bool remove_item(const T& item);

        // Removes all occurrences of an item, returns the count of removed items
        size_t remove_all(const T& item);

        // Combines another container into this one (operator overload)
        void operator+=(const BoxContainer<T>& operand);

        // Iterator class for BoxContainer (Bi-directional Iterator)
        class Iterator {
        public:
            using iterator_category = std::bidirectional_iterator_tag;  // Bidirectional iterator tag
            using difference_type = std::ptrdiff_t;                     // Difference type
            using value_type = T;                                       // Value type
            using pointer_type = T*;                                    // Pointer type
            using reference_type = T&;                                  // Reference type

            Iterator() = default;                                       // Default constructor

            // Constructor taking a pointer to the underlying data
            explicit Iterator(pointer_type ptr) : m_ptr(ptr) {}

            // Copy constructor and assignment operator can be defaulted
            Iterator(const Iterator&) = default;
            Iterator& operator=(const Iterator&) = default;

            // Dereference operator to access the value
            reference_type operator*() const { return *m_ptr; }

            // Arrow operator to access members directly
            pointer_type operator->() { return m_ptr; }

            // Pre-increment operator (advances the pointer)
            Iterator& operator++() { ++m_ptr; return *this; }

            // Post-increment operator (advances but returns old value)
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            // Pre-decrement operator (moves the pointer backward)
            Iterator& operator--() { --m_ptr; return *this; }

            // Post-decrement operator
            Iterator operator--(int) { Iterator tmp = *this; --(*this); return tmp; }

            // Equality comparison operator for iterators
            friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }

            // Inequality comparison operator for iterators
            friend bool operator!=(const Iterator& a, const Iterator& b) { return !(a == b); }

        private:
            pointer_type m_ptr{ nullptr }; // Pointer to the current element
        };

        // Begin iterator (points to the first element)
        Iterator begin() { return Iterator(m_items.get()); }

        // End iterator (points one past the last element)
        Iterator end() { return Iterator(m_items.get() + m_size); }

    private:
        // Expands the container's capacity to the new size
        void expand(size_t new_capacity);

    private:
        std::unique_ptr<T[]> m_items;  // m_items is a smart pointer that will manage 
                                       // a dynamically allocated array of type T.
        size_t m_capacity{ 0 };        // Current capacity of the container
        size_t m_size{ 0 };            // Current number of elements in the container
    };

    // --- Method Definitions ---
    // Operator to concatenate two BoxContainers and return a new one
    template <typename T> requires std::default_initializable<T>
    BoxContainer<T> operator+(const BoxContainer<T>& left, const BoxContainer<T>& right) {
        BoxContainer<T> result(left.size() + right.size()); // Create a new container large enough
        result += left;                                     // Add elements from left
        result += right;                                    // Add elements from right
        return result;                                      // Return the combined container
    }

    // Constructor
    template <typename T> requires std::default_initializable<T>
    BoxContainer<T>::BoxContainer(size_t capacity)
        : m_items(std::make_unique<T[]>(capacity)), m_capacity(capacity), m_size(0) {}

    // Copy constructor, uses std::copy for copying elements
    template <typename T> requires std::default_initializable<T>
    BoxContainer<T>::BoxContainer(const BoxContainer<T>& source) requires std::copyable<T>
        : m_items(std::make_unique<T[]>(source.m_capacity)), m_capacity(source.m_capacity), m_size(source.m_size) {
        std::copy(source.m_items.get(), source.m_items.get() + source.m_size, m_items.get());
    }

    // Move constructor
    template <typename T> requires std::default_initializable<T>
    BoxContainer<T>::BoxContainer(BoxContainer&& source) noexcept
        : m_items(std::move(source.m_items)), 
        m_capacity(source.m_capacity), 
        m_size(source.m_size) {
        source.m_capacity = 0; // Invalidate the moved-from object's capacity
        source.m_size = 0;     // Invalidate the moved-from object's size
    }

    // Copy assignment operator using copy-and-swap idiom (exception safe)
    template <typename T> requires std::default_initializable<T>
    BoxContainer<T>& BoxContainer<T>::operator=(const BoxContainer<T>& source) {
        if (this != &source) {
            BoxContainer temp(source);          // Copy source into a temporary object
            std::swap(m_items, temp.m_items);   // Swap data members
            std::swap(m_capacity, temp.m_capacity);
            std::swap(m_size, temp.m_size);
        }
        return *this;                           // Return the modified object
    }

    // Move assignment operator
    template <typename T> requires std::default_initializable<T>
    BoxContainer<T>& BoxContainer<T>::operator=(BoxContainer&& source) noexcept {
        if (this != &source) {
            m_items = std::move(source.m_items); // Move the resource
            m_capacity = source.m_capacity;       // Transfer capacity
            m_size = source.m_size;               // Transfer size

            // Invalidate the moved-from object's state
            source.m_capacity = 0; 
            source.m_size = 0; 
        }
        return *this; // Return the modified object
    }

    // Expands the container's capacity to hold more elements
    template <typename T> requires std::default_initializable<T>
    void BoxContainer<T>::expand(size_t new_capacity) {
        if (new_capacity <= m_capacity)
            return;  // No need to expand if the current capacity is sufficient

        std::unique_ptr<T[]> new_items = std::make_unique<T[]>(new_capacity);  // Allocate new larger array
        std::copy(m_items.get(), m_items.get() + m_size, new_items.get());     // Copy existing elements
        m_items.swap(new_items);                                               // Replace old array
        m_capacity = new_capacity;                                             // Update capacity
    }

    // Adds a new item to the container, expanding if necessary
    template <typename T> requires std::default_initializable<T>
    void BoxContainer<T>::add(const T& item) {
        if (m_size == m_capacity)
            expand(m_size + EXPAND_STEPS);  // Expand if capacity is full
        m_items[m_size] = item;             // Add the new item
        ++m_size;                           // Increment size
    }

    // Removes the first occurrence of the item from the container
    template <typename T> requires std::default_initializable<T>
    bool BoxContainer<T>::remove_item(const T& item) {
        auto it = std::find(m_items.get(), m_items.get() + m_size, item); // Use std::find to locate the item
        if (it == m_items.get() + m_size)
            return false;  // Item not found

        // Replace the removed item with the last item and reduce size
        *it = std::move(m_items[m_size - 1]); // Move last item to the removed item's position
        --m_size;  // Decrease size
        return true;  // Return success
    }

    // Removes all occurrences of the item from the container
    template <typename T> requires std::default_initializable<T>
    size_t BoxContainer<T>::remove_all(const T& item) {
        size_t count = 0;
        for (size_t i = 0; i < m_size;) {
            if (m_items[i] == item) {
                remove_item(item);  // Use remove_item to remove the item
                ++count;            // Increment count
            } else {
                ++i;  // Only increment if no item is removed
            }
        }
        return count; // Return the number of removed items
    }

    // Combines another container into this one (operator overload)
    template <typename T> requires std::default_initializable<T>
    void BoxContainer<T>::operator+=(const BoxContainer<T>& operand) {
        for (size_t i = 0; i < operand.m_size; ++i) {
            add(operand.m_items[i]);  // Add each item from the operand container
        }
    }

}   // namespace custom_iterators_04