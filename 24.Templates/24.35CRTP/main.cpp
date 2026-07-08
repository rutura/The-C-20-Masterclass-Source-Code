// Polymorphism (chapter 21) got dynamic dispatch through a base class
// pointer and virtual functions - resolved at runtime via a vtable lookup.
// CRTP (Curiously Recurring Template Pattern) gets similar-looking
// dispatch resolved entirely at compile time instead: a base class
// template parameterized on its own derived class, so it can call back
// into the derived class's methods directly - no virtual, no vtable, no
// runtime cost.

#include <print>

// Base is a template, and Derived passes *itself* as Base's template
// argument - the "curious" part this pattern is named for.
template <typename Derived>
class Shape {
public:
    double area() const {
        // static_cast, not dynamic_cast - safe here because Derived is
        // known at compile time, baked in as the template argument.
        // This calls Derived::areaImpl() directly, no vtable involved.
        return static_cast<const Derived*>(this)->areaImpl();
    }

    void describe() const {
        std::println("This shape has area {:.2f}", area());
    }
};

class Circle : public Shape<Circle> {
public:
    explicit Circle(double radius) : m_radius(radius) {}

    // Not virtual - this doesn't need to be, since Shape<Circle>::area()
    // already knows exactly which type it's dealing with.
    double areaImpl() const {
        return 3.14159 * m_radius * m_radius;
    }

private:
    double m_radius;
};

class Square : public Shape<Square> {
public:
    explicit Square(double side) : m_side(side) {}

    double areaImpl() const {
        return m_side * m_side;
    }

private:
    double m_side;
};

int main() {

    Circle circle(2.0);
    Square square(3.0);

    // Each call to describe() resolves areaImpl() at compile time - the
    // compiler generates a separate Shape<Circle>::area() and
    // Shape<Square>::area(), each calling its own type directly. Contrast
    // this with chapter 21's Shape*/Ellipse* array, where one function
    // pointer handled every derived type through one vtable, decided at
    // runtime.
    circle.describe();
    square.describe();

    // The tradeoff: unlike virtual dispatch, you can't put a Circle and a
    // Square in the same array through a common Shape* the way chapter 21
    // did - Shape<Circle> and Shape<Square> are two different,
    // unrelated-at-runtime types. CRTP trades that runtime flexibility for
    // zero dispatch overhead - useful when the exact set of types is known
    // at compile time and performance matters more than an open-ended
    // collection of shapes.

    return 0;
}
