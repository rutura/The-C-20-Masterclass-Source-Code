module;

#include <iostream>
#include <algorithm>
#include <vector>
#include <ranges>

export module custom_iterators_06;

namespace custom_iterators_06{

    export void print(auto  view){
        for(auto i : view){ // Computation happens here.
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }

    export struct Student{
        friend std::ostream& operator<<(std::ostream& out, const Student& s){
            out << "Student [ name : " << s.m_name << ", age : " << s.m_age << "]";
            return out;
        }
        auto operator <=>(const Student& s) const= default;
        std::string m_name;
        unsigned int m_age;
    };

}   //custom_iterators_06