/*
    . Exploring different arrangements for classes and member functions when templates are involved: 
        . The class is a template.
        . The class is not a template, but the member functions are templates.
        . Both the class and the member functions are templates.
*/
module;

export module templates_5;

namespace templates_5{

    // Class is a template, member uses the template parameter
    export template <typename T>
    class Calculator_1 {
    public:
        Calculator_1() = default;

        T add(T a, T b) { return a + b; }
        T subtract(T a, T b) { return a - b; }
        T multiply(T a, T b) { return a * b; }
        T divide(T a, T b) { return a / b; }
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
    
} // namespace templates_5