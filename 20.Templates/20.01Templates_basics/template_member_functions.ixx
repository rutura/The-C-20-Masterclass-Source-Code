module;

export module template_member_functions;

namespace template_member_functions{

    //Class is a template, member uses the template parameter
    export template <typename T>
    class Calculator_1{

    public:
        Calculator_1(){}

        T add(T a, T b){
            return a + b;
        }

        T subtract(T a, T b){
            return a - b;
        }

        T multiply(T a, T b){
            return a * b;
        }

        T divide(T a, T b){
            return a / b;
        }
    };


    //Class is not a template, member is a function template
    export class Calculator_2{
    public:
        Calculator_2(){}

        template <typename T>
        T add(T a, T b){
            return a + b;
        }

        template <typename T>
        T subtract(T a, T b){
            return a - b;
        }

        template <typename T>
        T multiply(T a, T b){
            return a * b;
        }

        template <typename T>
        T divide(T a, T b){
            return a / b;
        }
    };

    //Both class and member are templates
    // Template class Box that can hold any type of item
    export template <typename T>
    class Box {
    private:
        T item;
    public:
        // Constructor to initialize the item
        Box(T item) : item(item) {}

        // Method to get the item
        T getItem() const {
            return item;
        }

        // Template member function to compare the item with another item of a different type
        template <typename U>
        bool compare(const U& other) const {
            return item == other; // There may be assumptions made on the U type here, but we'll just use ==.
        }
    };

}   // namespace template_member_functions
