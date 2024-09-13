/*
       . Variadic templates allow you to create templates that can accept an arbitrary number of template arguments. This is especially useful when you don't know how many arguments you will have at compile time.
       .  Practical Example: Creating a Simple Tuple Class
            . A tuple is a data structure that can hold a fixed number of elements of different types. Let's create a simple tuple class using variadic templates to understand how they work.

            . Imagine you want to create a class that can store a combination of different types, like an integer, a string, and a float. You could define a class like this:

                template<typename T1, typename T2, typename T3>
                class MyTuple {
                public:
                    T1 first;
                    T2 second;
                    T3 third;

                    MyTuple(T1 a, T2 b, T3 c) : first(a), second(b), third(c) {}
                };
            . This works, but it's rigid—you can only create tuples with exactly three elements. To make it more flexible, let's use variadic templates. See below.

            . Here’s what happens:

                . The class MyTuple<Head, Tail...> inherits from MyTuple<Tail...>, which means it stores the first element (Head) and delegates the rest to the inherited class.
                . This recursion continues until there are no types left, so we need a base case:
                    template<>
                    class MyTuple<> {
                        // Empty base case
                    };

                . With this infrastructure in place, we can create tuples of any size as shown in utilities.ixx.
                . Notice that we rely on casting to upstream classes to further access the values. 


*/
module;

#include <fmt/format.h>

export module variadic_class_templates;

namespace variadic_class_templates{

    // Base case for recursion: an empty MyTuple
    export template<typename... Types>
    class MyTuple;  // Forward declaration

    export template<>
    class MyTuple<> {
        // Empty base case
    };

    // Recursive case: inherit from MyTuple of the tail
    export template<typename Head, typename... Tail>
    class MyTuple<Head, Tail...> : public MyTuple<Tail...> {
        Head value;

    public:
        // Constructor initializes the current value and passes the rest to the base class
        MyTuple(Head v, Tail... tail) : MyTuple<Tail...>(tail...), value(v) {}

        // Getter for the current value
        Head getValue() { return value; }
    };

}   // namespace variadic_class_templates