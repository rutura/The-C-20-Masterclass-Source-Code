#include <print>

class Vec2 {
public:
    Vec2(double x, double y) : x_{x}, y_{y} {}

    double x() const { return x_; }
    double y() const { return y_; }

    // COMPOUND assignment changes the object it is called on, so it is a MEMBER,
    // and it returns *this by reference so that it behaves like the built-in
    // += (10.10). It is the real work.
    Vec2& operator+=(const Vec2& other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    Vec2& operator-=(const Vec2& other) {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    Vec2& operator*=(double factor) {
        x_ *= factor;
        y_ *= factor;
        return *this;
    }

    // Unary minus does not change the object: const member.
    Vec2 operator-() const {
        return Vec2{-x_, -y_};
    }

    // The BINARY operators are built from the compound ones. They are
    // "hidden friends": defined inside the class with the keyword friend, which
    // makes them FREE functions (not members) that can see the private data.
    // The first parameter is taken BY VALUE: it is already the copy we want to
    // modify and return.
    friend Vec2 operator+(Vec2 a, const Vec2& b) {
        a += b;
        return a;
    }

    friend Vec2 operator-(Vec2 a, const Vec2& b) {
        a -= b;
        return a;
    }

    // Multiplication by a number works in BOTH orders only if there are two
    // functions. As a member, only  vec * 2.0  could ever work, because a
    // member's left operand is always the object itself.
    friend Vec2 operator*(Vec2 v, double factor) {
        v *= factor;
        return v;
    }

    friend Vec2 operator*(double factor, Vec2 v) {
        v *= factor;
        return v;
    }

private:
    double x_;
    double y_;
};

// Increment and decrement come in two forms. The compiler tells them apart by
// a dummy int parameter: prefix has none, postfix has one.
class Countdown {
public:
    explicit Countdown(int start) : value_{start} {}

    Countdown& operator--() {              // prefix:  --c   decrement, then give the new value
        --value_;
        return *this;
    }

    Countdown operator--(int) {            // postfix: c--   give the OLD value, then decrement
        Countdown old{*this};              // a copy is needed, so postfix is the costlier one
        --value_;
        return old;
    }

    int value() const { return value_; }

private:
    int value_;
};

void show(const char* label, const Vec2& v) {
    std::println("{:<22} ({}, {})", label, v.x(), v.y());
}

int main() {

    Vec2 position{1.0, 2.0};
    Vec2 wind{3.0, 4.0};

    show("position + wind", position + wind);
    show("2.0 * wind", 2.0 * wind);
    show("wind * 0.5", wind * 0.5);
    show("-wind", -wind);

    // The compound operator changes the object in place and, being the
    // building block, creates no temporary.
    position += wind;
    show("after position += wind", position);
    position *= 2.0;
    show("after position *= 2.0", position);

    // Because += returns a reference, it can be chained like the built-in one.
    Vec2 a{0.0, 0.0};
    (a += wind) += wind;
    show("(a += wind) += wind", a);

    std::println("\nprefix and postfix:");
    Countdown prefix{3};
    Countdown postfix{3};
    int from_prefix{(--prefix).value()};       // decrements, then reads 2
    int from_postfix{(postfix--).value()};     // reads the OLD 3, then decrements
    std::println("  --c gave {}, c is now {}", from_prefix, prefix.value());
    std::println("  c-- gave {}, c is now {}", from_postfix, postfix.value());

    // Which operators MUST be members: =  []  ()  ->  (the language insists).
    // Which should be: compound assignment and anything that changes the object.
    // Which should be free: symmetric binary operators, so that both operands
    // are treated alike and the left one can be converted (12.8).
    return 0;
}
