/*
    . Wraping around existing iterators.
*/
module;

#include <iostream>
#include <vector>

export module custom_iterators_09;

namespace custom_iterators_09{

    export template <typename T>
    class VectorWrapper{
    public: 
        //Iterator methods
        std::vector<T>::iterator begin() { return m_items.begin(); }
        std::vector<T>::iterator end()   { return m_items.end(); }

        //Const overloads
        std::vector<T>::const_iterator begin() const{ return m_items.cbegin(); }
        std::vector<T>::const_iterator end() const  { return m_items.cend(); }


        std::vector<T>::const_iterator cbegin() { return m_items.cbegin(); }
        std::vector<T>::const_iterator cend()   { return m_items.cend(); }
    
        friend std::ostream& operator<< (std::ostream& out, const VectorWrapper<T>& vec){
            out << "Items : " ;
            for (auto i : vec.m_items){
                out << i << " ";
            }
            return out;
        }  
        
        void add( T item){
            m_items.push_back(item);
        }
    private : 
        std::vector<T> m_items;
    };

}   //namespace custom_iterators_09