module;

#include <iostream>
#include <string>

export module ranges_library_04;

namespace ranges_library_04{

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


}   // namespace ranges_library_04