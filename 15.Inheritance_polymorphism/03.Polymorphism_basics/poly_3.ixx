/*
    . The need for virtual destructors.
        . In C++, when using polymorphism, objects can be accessed through pointers or 
            references to the base class.
        . The static type refers to the type of the pointer (in this case, the base class), 
            while the dynamic type refers to the actual object being pointed to 
            (which could be a derived class object).
        . If the base class destructor is not virtual, when you delete an object 
            through a pointer to the base class, the compiler will only call the 
            destructor of the static type (the base class). This is because non-virtual 
            functions are resolved at compile-time based on the static type of the pointer.
        . When a member function (such as show() in the example) is marked as virtual, the 
            function call is resolved at runtime (dynamic binding) based on the dynamic 
            type of the object. However, if the destructor is not marked virtual, its call 
            is still resolved at compile-time. This results in only the base class destructor 
            being called, even though the object might be of the derived class.
        . Derived class destructor is not called: If the derived class has any resources 
           (like dynamically allocated memory), those will not be released because the 
           derived class's destructor is never executed.
        . Memory leaks and resource leaks: Without the derived class destructor being invoked, 
            resources (like memory, file handles, or other system resources) managed by the     
            derived class won't be properly cleaned up, leading to leaks.
        . When the destructor is not virtual, the compiler assumes that the pointer 
            is pointing to an object of the base class type, regardless of the actual (dynamic) 
            type. At runtime, the type of the object being pointed to is not considered for 
            non-virtual functions, and the statically known destructor (from the base class) is called.

*/
module;

#include <fmt/format.h>

export module poly_3;

namespace poly_3{

    namespace bad{

        export class Base {
        public:
            // No virtual destructor here
            ~Base() {
                fmt::println("Base class destructor");
            }
            virtual void show() const {
                fmt::println("Base class show()");
            }
        };

        export class Derived : public Base {
        public:
            int* data;

            Derived() {
                data = new int[100];  // Dynamically allocated memory
                fmt::println("Derived class constructor");
            }

            ~Derived() {
                delete[] data;  // Memory cleanup in the destructor
                fmt::println("Derived class destructor");
            }

            void show() const override {
                fmt::println("Derived class show()");
            }
        };

    } // namespace bad

    namespace good{

        export class Base {
        public:
            // Virtual destructor
            virtual ~Base() {
                fmt::println("Base class destructor");
            }

            virtual void show() const {
                fmt::println("Base class show()");
            }
        };

        export class Derived : public Base {
        public:
            int* data;

            Derived() {
                data = new int[100];
                fmt::println("Derived class constructor");
            }

            ~Derived() override {
                delete[] data;  // Memory cleanup
                fmt::println("Derived class destructor");
            }

            void show() const override {
                fmt::println("Derived class show()");
            }
        };
        
    } // namespace good
    
    
    
} // namespace poly_3
