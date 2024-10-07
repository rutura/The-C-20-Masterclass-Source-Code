/*
    . Exploring Member Hiding

        . In C++, when a derived class defines a member (either a variable or a 
            function) with the same name as one in its base class, the base class 
            member is said to be "hidden." This means that within the scope of the 
            derived class, any attempt to access the member with that name will 
            refer to the derived class's member, rather than the base class's 
            member.

        . Key Points:
            . Hiding in Member Variables:
                . the member variable m_member_var is defined 
                    in both Parent and Child. When we refer to m_member_var in 
                    the Child class, it will refer to the Child's m_member_var 
                    instead of the Parent's m_member_var. This means that any 
                    access to m_member_var in Child will not see the Parent's 
                    m_member_var unless we explicitly specify the base class 
                    (using Parent::m_member_var).

            . Hiding in Member Functions:
                . The print_var function is defined in both classes. When called 
                    on a Child object, it will invoke the print_var of Child, and 
                    the one in Parent will be hidden. If you want to call the Parent's print_var, you would need to use an instance of Parent or explicitly reference it if you're in the context of Child.

            . Accessing Base Class Members:
                The show_values function in Child demonstrates how to access the 
                Parent class's m_member_var explicitly with Parent::m_member_var. 
                This is necessary to differentiate between the two members since 
                they share the same name.
                
*/
module;

#include <fmt/format.h>

export module inh_poly_4;

namespace inh_poly_4{

    // Parent class
    export class Parent {
    public:
        Parent() = default;
        Parent(int member_var) : m_member_var(member_var) {}

        void print_var() const {
            fmt::println("The value in parent is: {}", m_member_var);
        }

    protected:
        int m_member_var{ 100 }; // Default value
    };

    // Child class
    export class Child : public Parent {
    public:
        Child() = default; // Default constructor
        Child(int member_var) : Parent(member_var), m_member_var(member_var) {} // Initialize base member

        void print_var() const {
            fmt::println("The value in child is: {}", m_member_var);
        }

        void show_values() const {
            fmt::println("The value in child is: {}", m_member_var);
            fmt::println("The value in parent is: {}", Parent::m_member_var); // Access parent member
        }

    private:
        int m_member_var{ 1000 }; // Child-specific member
    };
    
} // namespace inh_poly_4