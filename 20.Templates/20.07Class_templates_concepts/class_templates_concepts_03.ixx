module;

#include <iostream>
#include <vector>

export module class_templates_concepts_03;

import boxcontainer;

namespace class_templates_concepts_03{

    //An concept that checks if a type can be written to an ostream
    export template <typename T>
    concept OutputStreamable = requires(std::ostream& o , T d){
        o << d;
    };


    ///Write an operator<< that prints a box::BoxContainer<T> to an ostream
    export template <OutputStreamable T>
    std::ostream & operator << (std::ostream& out, const box::BoxContainer<T> & box){
        out << "BoxContainer : [ size :  " << box.size()
            << ", capacity : " << box.capacity() << ", items : " ;
                
        for(size_t i{0}; i < box.size(); ++i){
            out << box.get_item(i) << " " ;
        }
        out << "]";
        
        return out;
    }


    export struct Point{
        double mx;
        double my;

        friend std::ostream& operator<<( std::ostream& o, const Point p){
            o << "Point [ x : " << p.mx << ", y : " << p.my << "]";
            return o;
        }
    
    };

}   // namespace class_templates_concepts_03