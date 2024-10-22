/*
    .  The iterator traits template:
        . Problem: 
            . Once we have an iterator, we want to know what type of data it points to.
            . But we don't know the type of the container.
        . Solution: 
            . Use the iterator_traits template to get the type of the data the iterator points to.
*/
module;

#include <fmt/format.h>
#include <iterator>

export module containers_iterators_04;

namespace containers_iterators_04{

    export template <typename T>
    void print_referenced_value(T it){

        //This syntax allows us to retrieve the value contained in the container, which is dynamic.
        //If the container contains int, val will be int, if the container contains std::string, val will be std::string, and so on.
        typename std::iterator_traits<T>::value_type val = *it;
        fmt::println("{}", val);
    }

    //We can use the technique to create a find function that works with any container: Pretty slick if you ask me.
    export template <typename T>
    auto custom_find(T begin, T end, typename std::iterator_traits<T>::value_type val){

        while(begin != end){
            if(*begin == val){
                return begin;
            }
            ++begin;
        }
        return end;
    }

}   // namespace containers_iterators_04