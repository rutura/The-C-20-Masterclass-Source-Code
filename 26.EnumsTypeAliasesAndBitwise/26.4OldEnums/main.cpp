#include <print>

// Plain (unscoped) enums predate enum class: their enumerators leak into
// the surrounding scope instead of staying namespaced under the enum's own
// name, and they implicitly convert to their underlying integer type -
// both of which enum class was introduced to fix.
enum Direction : unsigned char {
    TopLeft = 64, TopRight, Center, BottomLeft, BottomRight
};

enum Tool {
    Pen, Marker, Eraser, Rectangle, Circle, PaintBucket
};

int main() {

    Direction direction{Direction::TopLeft};
    Tool tool{Tool::Pen};

    std::println("direction : {}", static_cast<unsigned int>(direction));
    std::println("tool : {}", static_cast<int>(tool));

    // This compiles with no cast at all: a plain enum implicitly converts to
    // its underlying integer type, so two completely unrelated enums can be
    // compared without the compiler ever objecting. enum class blocks this.
    std::println("(tool > direction) : {}", tool > direction);

    return 0;
}