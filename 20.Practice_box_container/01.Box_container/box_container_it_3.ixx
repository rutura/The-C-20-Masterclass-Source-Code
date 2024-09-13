module;

#include <iostream>

export module box_container_it_3;

import stream_insertable;

namespace iteration_3{

    export class BoxContainer : public iteration_1::StreamInsertable
    {
            //typedef int value_type; // Allows us to change what's stored in the vector on the fly
                                    // Can make it store int, double,...
            using value_type = int;

            static const size_t DEFAULT_CAPACITY = 30;  
            static const size_t EXPAND_STEPS = 5;// The box expands the capacity by this amount
    public:
        BoxContainer(size_t capacity = DEFAULT_CAPACITY);
        BoxContainer(const BoxContainer& source);
        ~BoxContainer();
        
        //StreamInsertable Interface
        virtual void stream_insert(std::ostream& out)const override;
        
        // Helper getter methods
        size_t size( ) const { return m_size; }
        size_t capacity() const{return m_capacity;};

        //Method to add items to the collection
        void add(const value_type& item);

        //Remove items
        bool remove_item(const value_type& item);
        size_t remove_all(const value_type& item);

    private : 
        void expand(size_t new_capacity);

    private : 
        value_type * m_items;
        size_t m_capacity;
        size_t m_size;
    };
    //Implementation
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

    void BoxContainer::expand(size_t new_capacity){
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

    void BoxContainer::add(const value_type& item){
        if (m_size == m_capacity)
            expand(m_size + EXPAND_STEPS);// Let's expand in increments of 5 to optimize on the calls to expand
        m_items[m_size] = item;
        ++m_size;	
    }


    bool BoxContainer::remove_item(const value_type& item){

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
    size_t BoxContainer::remove_all(const value_type& item){
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

}   //namespace iteration_3