/*
    . Exploring variadic class templates.
        . We lay out the problem by setting up a simple tuple named bag.
            . We do this and test it in the simple namespace.
        . We would want to set up bags that can store any number of elements of different types.
            . We do this and test it in the wild namespace.

    . How It Works:
        . Supppose you declare a bag like this:
            . Bag<int, double, std::string> myBag(42, 3.14, "Hello, world!");
            . This Bag holds three different types of values: an int, a double, and a std::string.
                . Step1: What Happens When You Declare Bag<int, double, std::string>?
                    . The compiler sees Bag<int, double, std::string>. This means you're creating a Bag with three types:
                        Head = int
                        Tail = double, std::string
                    . Because the Bag is recursive, the class template splits the types like this:
                        The first type (int) is stored in the current Bag object.
                        The remaining types (double, std::string) are stored in a base class of the current Bag.

                . Step 2: The First Level of the Bag
                    . The first Bag looks like this:
                        . Bag<int, double, std::string>
                    . Here:
                        . The Head is int, so m_value will store the int value 42.
                        . The Tail is double, std::string, which means this Bag inherits from Bag<double, std::string>.
                . Step 3: The Second Level of the Bag
                    . The next step is creating the base class, Bag<double, std::string>. 
                      This is the second level of the recursion:
                        . The Head is double, so m_value will store the double value 3.14.
                        . The Tail is std::string, which means this Bag inherits from Bag<std::string>.
                . Step 4: The Third Level of the Bag
                    . Finally, we get to the base class Bag<std::string>:
                        . The Head is std::string, so m_value will store the string "Hello, world!".
                        . The Tail is empty (<>), so this is the end of the recursion. It inherits from the empty Bag<>.

                    . At this point, your Bag<int, double, std::string> is fully built. It looks like this in terms of inheritance:

                        Bag<int, double, std::string>  --> stores int (42)
                            |
                            v
                        Bag<double, std::string>       --> stores double (3.14)
                            |
                            v
                        Bag<std::string>               --> stores std::string ("Hello, world!")
                            |
                            v
                        Bag<>                          --> empty base case

                . Step 5: How Does the Constructor Work?
                    . When you call the constructor like this:
                        . Bag<int, double, std::string> myBag(42, 3.14, "Hello, world!");

                    . Here’s what happens step-by-step:
                        . Top-Level Constructor (Bag<int, double, std::string>):
                            . The constructor takes 42 (an int) and passes the rest (3.14, "Hello, world!") to the base class Bag<double, std::string>.
                            . It stores 42 in m_value.

                        . Second-Level Constructor (Bag<double, std::string>):
                            . The constructor takes 3.14 (a double) and passes "Hello, world!" to the base class Bag<std::string>.
                            . It stores 3.14 in m_value.

                        . Third-Level Constructor (Bag<std::string>):
                            . The constructor takes "Hello, world!" (a std::string) and calls the base case Bag<>.
                            . It stores "Hello, world!" in m_value.

                        . Now all the values are stored, and the Bag structure is complete.

                . Step 6: Accessing the Values: 
                    . Here is code that is declaring a bag and accessing the value: 
                        Bag<int, double, std::string> myBag(42, 3.14, "Hello, world!");
                        std::cout << myBag.get_value() << std::endl; // Prints: 42
                        std::cout << myBag.get_tail().get_value() << std::endl; // Prints: 3.14
                        std::cout << myBag.get_tail().get_tail().get_value() << std::endl; // Prints: Hello, world!
                    . We access the first value by just calling the get_value method.
                    . To access the others, we have to somehow jump to the base class and call get_value there.
                    . We do this by casting the current object to the base class and then calling get_value.
                        . This is what we do in the get_tail method.
                        . Notice that it returns a reference to the base class.
                            . The syntax is weird but that's what it does.
                    . You can't keep going up and calling get_value indefinitely though.
                        . You can go up to just before the base case.
                        . Refer to the chart to make this apparent.


*/
module;

export module templates_3;

namespace templates_3{

    namespace simple{
        export template<typename T1, typename T2, typename T3>
        struct Bag {
            T1 first;
            T2 second;
            T3 third;
            Bag(T1 a, T2 b, T3 c) : first(a), second(b), third(c) {}
        };
    } // namespace simple 

    namespace wild{

        // Base case for recursion: an empty Bag
        export template<typename... Types>
        class Bag;  // Forward declaration

        // Specialization for the empty Bag
        export template<>
        class Bag<> {
            // Empty base case
        };

        // Recursive case: inherit from Bag of the tail
        export template<typename Head, typename... Tail>
        class Bag<Head, Tail...> : public Bag<Tail...> {
        public:
            // Constructor initializes the current value and passes the rest to the base class
            Bag(Head v, Tail... tail) : Bag<Tail...>(tail...), m_value(v) {}

            // Getter for the current value
            Head get_value() const { return m_value; }

            // Getter for the tail
            const Bag<Tail...>& get_tail() const { return *this; }
        public: 
            Head m_value;
        };

    } // namespace wild
    
    
} // namespace templates_3