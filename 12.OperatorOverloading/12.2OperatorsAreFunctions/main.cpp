#include <print>

// A 2D vector: a position or a displacement, say a wind arrow on a map.
struct Vec2 {
    double x;
    double y;
};

// An operator is a function with a funny name: "operator" followed by the
// symbol. This one is what runs when you write  a + b  for two Vec2 values.
Vec2 operator+(Vec2 a, Vec2 b) {
    return Vec2{a.x + b.x, a.y + b.y};
}

Vec2 operator-(Vec2 a, Vec2 b) {
    return Vec2{a.x - b.x, a.y - b.y};
}

// Unary minus takes ONE operand: the same symbol, a different operator.
Vec2 operator-(Vec2 v) {
    return Vec2{-v.x, -v.y};
}

// Multiplying a vector by a plain number: one operand is a Vec2, the other a double.
Vec2 operator*(Vec2 v, double factor) {
    return Vec2{v.x * factor, v.y * factor};
}

void show(const char* label, Vec2 v) {
    std::println("{:<18} ({}, {})", label, v.x, v.y);
}

int main() {

    Vec2 a{1.0, 2.0};
    Vec2 b{3.0, 4.0};

    // The operator form is the readable one...
    Vec2 sum{a + b};
    show("a + b", sum);

    // ...and it is EXACTLY the same call as this. The compiler turns the first
    // into the second.
    Vec2 sum_again{operator+(a, b)};
    show("operator+(a, b)", sum_again);

    show("a - b", a - b);
    show("-a", -a);
    show("b * 2.0", b * 2.0);

    // Precedence and associativity are those of the built-in operators and
    // cannot be changed. * still binds tighter than +, so this is a + (b * 2.0).
    show("a + b * 2.0", a + b * 2.0);

    // Chained, left to right, exactly like numbers:
    show("a + b + a - b", a + b + a - b);

    // This does not compile: only Vec2 * double was written, not double * Vec2.
    // 12.3 shows how to make both orders work.
    //     show("2.0 * b", 2.0 * b);               // error: no operator*(double, Vec2)

    // What you can and cannot do:
    //   - overload most operators: + - * / % ++ -- == != < > <= >= <=> [] () -> << >> and more
    //   - NOT invent new ones: there is no "**" for powers
    //   - NOT overload  ::  .  .*  ?:  sizeof
    //   - at least one operand must be a type you wrote: you cannot redefine 1 + 2
    //   - precedence, associativity and operand count stay as they are
    //
    // And the one rule that matters most: an operator should do what its
    // symbol suggests. A + that subtracts, or a << that opens a file, is legal
    // and a disaster for whoever reads the code. If you cannot think of an
    // obvious meaning, write a named function instead.
    return 0;
}
