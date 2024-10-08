/*
    . Template template parameters: 
        . These allow templates to accept another template as a parameter.
        . Let's see this through an example: 
            . We have a template class called Container that works with any type T.
                . This is a regular template class (or class template as I like to call them).
            . We also have a template class called Processor that works with a template
                 class Container and a type T.
                 . We want Processor to work on any container type that has an add method and 
                    a print method.
                 . The first parameter of the Processor class template is a template itself;
                    hence the term template template parameter.
                . The syntax `template <typename> class ContainerType` specifies that ContainerType 
                    is a template class that takes one type parameter.
*/
module;

#include <fmt/format.h>
#include <vector>

export module templates_4;

namespace templates_4{

        //The container template.
    export template <typename T>
    class Container {
    public:
        void add(const T& element) {
            data.push_back(element);
        }
        
        void print() const {
            for (const auto& element : data) {
                fmt::print("{} ", element);
            }
            fmt::print("\n");
        }

    private:
        std::vector<T> data;
    };

    //Template template parameter.
    export template <template <typename> class ContainerType, typename T>
    class Processor {
    public:
        void process(ContainerType<T>& container, const T& element) {
            container.add(element);
            container.print();
        }
    };
    
} // namespace templates_4