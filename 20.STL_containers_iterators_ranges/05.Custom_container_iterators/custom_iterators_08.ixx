/*
    . Raw pointers as iterators.
*/
module;

#include <iostream>
#include <concepts>

export module custom_iterators_08;

namespace custom_iterators_08{


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

        /*
        // Iterator class for BoxContainer (Random Access Iterator)
        class Iterator{
            public : 
                    using iterator_category = std::random_access_iterator_tag;
                    using difference_type   = std::ptrdiff_t;
                    using value_type        = T;
                    using pointer_type           = T*;
                    using reference_type         = T&;

            Iterator() = default;
            Iterator(pointer_type ptr) : m_ptr(ptr) {}
        
            reference_type operator*() const {
                return *m_ptr;
            }

            pointer_type operator->() {
                return m_ptr;
            }

            Iterator& operator++() {
                m_ptr++; return *this;
            }  
            Iterator operator++(int) {
                Iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            //These operators are non members, but can still access private
            //members of Iterator. Cool.
            friend bool operator== (const Iterator& a, const Iterator& b) {
                return a.m_ptr == b.m_ptr;
            }
            friend bool operator!= (const Iterator& a, const Iterator& b) {
                //return a.m_ptr != b.m_ptr; 
                return !(a == b);
            } 

            Iterator& operator--() {
                m_ptr--; return *this;
            }  
            Iterator operator--(int) {
                Iterator tmp = *this;
                --(*this);
                return tmp;
            }

            //Random access
            Iterator& operator+=(const difference_type offset) {
                m_ptr += offset;
                return *this;
            }

            Iterator operator+(const difference_type offset) const  {
                Iterator tmp = *this;
                return tmp += offset;
            }
            
            Iterator& operator-=(const difference_type offset) {
                return *this += -offset;
            }

            Iterator operator-(const difference_type offset) const  {
                Iterator tmp = *this;
                return tmp -= offset;
            }

            difference_type operator-(const Iterator& right) const {
                return m_ptr - right.m_ptr;
            }
            
            reference_type operator[](const difference_type offset) const  {
                return *(*this + offset);
            }
            
            bool operator<(const Iterator& right) const  {
                return m_ptr < right.m_ptr;
            }

            bool operator>(const Iterator& right) const  {
                return right < *this;
            }

            bool operator<=(const Iterator& right) const {
                return !(right < *this);
            }

            bool operator>=(const Iterator& right) const  {
                return !(*this < right);
            }


            friend Iterator operator+(const difference_type offset, const Iterator& it){
                Iterator tmp = it;
                return tmp += offset;
            }
            //Random access - End

            private : 
                pointer_type m_ptr;
        };  

        // ConstIterator class for BoxContainer (Random Access Iterator)
        class ConstIterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer_type      = const T*;
            using reference_type    = const T&;

            ConstIterator() = default;
            ConstIterator(pointer_type ptr) : m_ptr(ptr) {}

            reference_type operator*() const { return *m_ptr; }
            pointer_type operator->() const { return m_ptr; }

            ConstIterator& operator++() {
                m_ptr++;
                return *this;
            }
            ConstIterator operator++(int) {
                ConstIterator tmp = *this;
                ++(*this);
                return tmp;
            }

            ConstIterator& operator--() {
                m_ptr--;
                return *this;
            }
            ConstIterator operator--(int) {
                ConstIterator tmp = *this;
                --(*this);
                return tmp;
            }

            ConstIterator& operator+=(difference_type offset) {
                m_ptr += offset;
                return *this;
            }

            ConstIterator operator+(difference_type offset) const {
                ConstIterator tmp = *this;
                return tmp += offset;
            }

            ConstIterator& operator-=(difference_type offset) {
                m_ptr -= offset;
                return *this;
            }

            ConstIterator operator-(difference_type offset) const {
                ConstIterator tmp = *this;
                return tmp -= offset;
            }

            difference_type operator-(const ConstIterator& right) const {
                return m_ptr - right.m_ptr;
            }

            reference_type operator[](difference_type offset) const {
                return *(m_ptr + offset);
            }

            bool operator<(const ConstIterator& right) const {
                return m_ptr < right.m_ptr;
            }

            bool operator>(const ConstIterator& right) const {
                return m_ptr > right.m_ptr;
            }

            bool operator<=(const ConstIterator& right) const {
                return !(right < *this);
            }

            bool operator>=(const ConstIterator& right) const {
                return !(*this < right);
            }

            friend ConstIterator operator+(difference_type offset, const ConstIterator& it) {
                return it + offset;
            }

            friend bool operator==(const ConstIterator& a, const ConstIterator& b) {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!=(const ConstIterator& a, const ConstIterator& b) {
                return a.m_ptr != b.m_ptr;
            }

        private:
            pointer_type m_ptr;
        };

        // ReverseIterator class for BoxContainer (Random Access Iterator)
        class ReverseIterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer_type      = T*;
            using reference_type    = T&;

            ReverseIterator() = default;
            ReverseIterator(pointer_type ptr) : m_ptr(ptr) {}

            reference_type operator*() const { return *m_ptr; }
            pointer_type operator->() { return m_ptr; }

            ReverseIterator& operator++() {
                m_ptr--;
                return *this;
            }
            ReverseIterator operator++(int) {
                ReverseIterator tmp = *this;
                --(*this);
                return tmp;
            }

            ReverseIterator& operator--() {
                m_ptr++;
                return *this;
            }
            ReverseIterator operator--(int) {
                ReverseIterator tmp = *this;
                ++(*this);
                return tmp;
            }

            ReverseIterator& operator+=(difference_type offset) {
                m_ptr -= offset;
                return *this;
            }

            ReverseIterator operator+(difference_type offset) const {
                ReverseIterator tmp = *this;
                return tmp += offset;
            }

            ReverseIterator& operator-=(difference_type offset) {
                m_ptr += offset;
                return *this;
            }

            ReverseIterator operator-(difference_type offset) const {
                ReverseIterator tmp = *this;
                return tmp -= offset;
            }

            difference_type operator-(const ReverseIterator& right) const {
                return right.m_ptr - m_ptr;
            }

            reference_type operator[](difference_type offset) const {
                return *(m_ptr - offset);
            }

            bool operator<(const ReverseIterator& right) const {
                return m_ptr > right.m_ptr;  // flipped logic for reverse
            }

            bool operator>(const ReverseIterator& right) const {
                return m_ptr < right.m_ptr;  // flipped logic for reverse
            }

            bool operator<=(const ReverseIterator& right) const {
                return !(right > *this);
            }

            bool operator>=(const ReverseIterator& right) const {
                return !(right < *this);
            }

            friend ReverseIterator operator+(difference_type offset, const ReverseIterator& it) {
                return it + offset;
            }

            friend bool operator==(const ReverseIterator& a, const ReverseIterator& b) {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!=(const ReverseIterator& a, const ReverseIterator& b) {
                return a.m_ptr != b.m_ptr;
            }

        private:
            pointer_type m_ptr;
        };

        // ConstReverseIterator class for BoxContainer (Random Access Iterator)
        class ConstReverseIterator {
        public:
            using iterator_category = std::random_access_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = T;
            using pointer_type      = const T*;
            using reference_type    = const T&;

            ConstReverseIterator() = default;
            ConstReverseIterator(pointer_type ptr) : m_ptr(ptr) {}

            reference_type operator*() const { return *m_ptr; }
            pointer_type operator->() const { return m_ptr; }

            ConstReverseIterator& operator++() {
                m_ptr--;
                return *this;
            }
            ConstReverseIterator operator++(int) {
                ConstReverseIterator tmp = *this;
                --(*this);
                return tmp;
            }

            ConstReverseIterator& operator--() {
                m_ptr++;
                return *this;
            }
            ConstReverseIterator operator--(int) {
                ConstReverseIterator tmp = *this;
                ++(*this);
                return tmp;
            }

            ConstReverseIterator& operator+=(difference_type offset) {
                m_ptr -= offset;
                return *this;
            }

            ConstReverseIterator operator+(difference_type offset) const {
                ConstReverseIterator tmp = *this;
                return tmp += offset;
            }

            ConstReverseIterator& operator-=(difference_type offset) {
                m_ptr += offset;
                return *this;
            }

            ConstReverseIterator operator-(difference_type offset) const {
                ConstReverseIterator tmp = *this;
                return tmp -= offset;
            }

            difference_type operator-(const ConstReverseIterator& right) const {
                return right.m_ptr - m_ptr;
            }

            reference_type operator[](difference_type offset) const {
                return *(m_ptr - offset);
            }

            bool operator<(const ConstReverseIterator& right) const {
                return m_ptr > right.m_ptr;  // flipped logic for reverse
            }

            bool operator>(const ConstReverseIterator& right) const {
                return m_ptr < right.m_ptr;  // flipped logic for reverse
            }

            bool operator<=(const ConstReverseIterator& right) const {
                return !(right > *this);
            }

            bool operator>=(const ConstReverseIterator& right) const {
                return !(right < *this);
            }

            friend ConstReverseIterator operator+(difference_type offset, const ConstReverseIterator& it) {
                return it + offset;
            }

            friend bool operator==(const ConstReverseIterator& a, const ConstReverseIterator& b) {
                return a.m_ptr == b.m_ptr;
            }

            friend bool operator!=(const ConstReverseIterator& a, const ConstReverseIterator& b) {
                return a.m_ptr != b.m_ptr;
            }

        private:
            pointer_type m_ptr;
        };
        */

        //Iterator methods
        /*
        Iterator begin() { return Iterator(m_items.get()); } // Begin iterator: points to the first element
        Iterator end() { return Iterator(m_items.get() + m_size); } // End iterator: points one past the last element

        ConstIterator begin() const { return ConstIterator(m_items.get()); }
        ConstIterator end() const { return ConstIterator(m_items.get() + m_size); }

        ReverseIterator rbegin() { return ReverseIterator(m_items.get() + m_size - 1); }
        ReverseIterator rend() { return ReverseIterator(m_items.get() - 1); }

        ConstReverseIterator rbegin() const { return ConstReverseIterator(m_items.get() + m_size - 1); }
        ConstReverseIterator rend() const { return ConstReverseIterator(m_items.get() - 1); }
        */

        //Add begin and end methods that just return the raw pointers
        T* begin() { return m_items.get(); }
        T* end() { return m_items.get() + m_size; }

        const T* begin() const { return m_items.get(); }
        const T* end() const { return m_items.get() + m_size; }

        //Add rbegin and rend methods that just return the raw pointers
        T* rbegin() { return m_items.get() + m_size - 1; }
        T* rend() { return m_items.get() - 1; }

        const T* rbegin() const { return m_items.get() + m_size - 1; }
        const T* rend() const { return m_items.get() - 1; }

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

    export template <typename T>
    void print(const BoxContainer<T>&  c){
        for(auto i : c){ // Computation happens here.
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

}   //custom_iterators_08