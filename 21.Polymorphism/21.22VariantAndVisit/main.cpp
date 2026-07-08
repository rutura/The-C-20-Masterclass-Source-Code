// Every lecture in this chapter has gotten polymorphic behavior through
// inheritance: a base class pointer/reference, virtual functions, dynamic
// dispatch. std::variant is a different way to get similar behavior for a
// *closed*, known-in-advance set of types - no base class, no virtual
// functions, no vtable - at the cost of not being open to new types the
// way a new subclass would be.

#include <print>
#include <variant>
#include <string>
#include <vector>

struct Circle {
    double radius;
};

struct Square {
    double side;
};

struct Rectangle {
    double width;
    double height;
};

using Shape = std::variant<Circle, Square, Rectangle>;

// std::visit calls the right overload for whichever alternative the
// variant currently holds - the compile-time equivalent of what a virtual
// function call resolves at runtime through a vtable.
double area(const Shape& shape) {
    return std::visit(
        [](const auto& s) -> double {
            using T = std::decay_t<decltype(s)>;
            if constexpr (std::is_same_v<T, Circle>) {
                return 3.14159 * s.radius * s.radius;
            } else if constexpr (std::is_same_v<T, Square>) {
                return s.side * s.side;
            } else if constexpr (std::is_same_v<T, Rectangle>) {
                return s.width * s.height;
            }
        },
        shape);
}

std::string name(const Shape& shape) {
    return std::visit(
        [](const auto& s) -> std::string {
            using T = std::decay_t<decltype(s)>;
            if constexpr (std::is_same_v<T, Circle>) return "Circle";
            else if constexpr (std::is_same_v<T, Square>) return "Square";
            else return "Rectangle";
        },
        shape);
}

int main() {

    std::vector<Shape> shapes{
        Circle{2.0},
        Square{3.0},
        Rectangle{4.0, 5.0},
    };

    for (const auto& shape : shapes) {
        std::println("{}: area = {:.2f}", name(shape), area(shape));
    }

    // std::holds_alternative / std::get check and extract a specific
    // alternative, the variant equivalent of dynamic_cast against a base
    // class pointer.
    Shape first = shapes[0];
    if (std::holds_alternative<Circle>(first)) {
        const Circle& c = std::get<Circle>(first);
        std::println("");
        std::println("First shape is a Circle with radius {}", c.radius);
    }

    // Assigning a different alternative works exactly like reassigning a
    // base-class pointer to point at a different derived object - except
    // here the "object" itself changes type in place, no allocation or
    // pointer indirection involved.
    Shape reassignable = Circle{1.0};
    std::println("");
    std::println("reassignable holds a {} (area {:.2f})", name(reassignable), area(reassignable));
    reassignable = Rectangle{2.0, 3.0};
    std::println("reassignable holds a {} (area {:.2f})", name(reassignable), area(reassignable));

    return 0;
}
