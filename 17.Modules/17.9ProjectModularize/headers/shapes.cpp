#include "shapes.h"

#include <algorithm>
#include <cstdlib>
#include <format>
#include <utility>

// ---------------------------------------------------------------------------
// Rectangle
// ---------------------------------------------------------------------------
Rectangle::Rectangle(int x, int y, int width, int height, Color color)
    : x_{x}, y_{y}, width_{width}, height_{height}, color_{color} {}

void Rectangle::draw(Canvas& canvas) const {
    canvas.fill_rect(x_, y_, width_, height_, color_);
}

void Rectangle::translate(int dx, int dy) {
    x_ += dx;
    y_ += dy;
}

// Each derived class copies ITSELF. "*this" has the real type here, so the
// copy is a complete Rectangle, and the caller receives it as a Shape pointer.
std::unique_ptr<Shape> Rectangle::clone() const {
    return std::make_unique<Rectangle>(*this);
}

std::string Rectangle::name() const {
    return std::format("Rectangle {}x{}", width_, height_);
}

// ---------------------------------------------------------------------------
// Circle
// ---------------------------------------------------------------------------
Circle::Circle(int center_x, int center_y, int radius, Color color)
    : center_x_{center_x}, center_y_{center_y}, radius_{radius}, color_{color} {}

void Circle::draw(Canvas& canvas) const {
    // A pixel is inside the circle when its distance from the centre is at
    // most the radius: dx*dx + dy*dy <= r*r. Test every pixel of the
    // bounding square. set_pixel clips whatever falls outside the canvas.
    for (int dy{-radius_}; dy <= radius_; ++dy) {
        for (int dx{-radius_}; dx <= radius_; ++dx) {
            if (dx * dx + dy * dy <= radius_ * radius_) {
                canvas.set_pixel(center_x_ + dx, center_y_ + dy, color_);
            }
        }
    }
}

void Circle::translate(int dx, int dy) {
    center_x_ += dx;
    center_y_ += dy;
}

std::unique_ptr<Shape> Circle::clone() const {
    return std::make_unique<Circle>(*this);
}

std::string Circle::name() const {
    return std::format("Circle r={}", radius_);
}

// ---------------------------------------------------------------------------
// Line (Bresenham's algorithm: integers only, one pixel per step)
// ---------------------------------------------------------------------------
Line::Line(Point from, Point to, Color color, int thickness)
    : from_{from}, to_{to}, color_{color}, thickness_{std::max(thickness, 1)} {}

void Line::draw(Canvas& canvas) const {
    int x{from_.x};
    int y{from_.y};
    const int dx{std::abs(to_.x - from_.x)};
    const int dy{-std::abs(to_.y - from_.y)};
    const int step_x{from_.x < to_.x ? 1 : -1};
    const int step_y{from_.y < to_.y ? 1 : -1};
    int error{dx + dy};

    while (true) {
        // A thick line is a small square stamped at every step.
        canvas.fill_rect(x - thickness_ / 2, y - thickness_ / 2, thickness_, thickness_, color_);

        if (x == to_.x && y == to_.y) {
            break;
        }
        const int doubled{2 * error};
        if (doubled >= dy) {
            error += dy;
            x += step_x;
        }
        if (doubled <= dx) {
            error += dx;
            y += step_y;
        }
    }
}

void Line::translate(int dx, int dy) {
    from_.x += dx;
    from_.y += dy;
    to_.x += dx;
    to_.y += dy;
}

std::unique_ptr<Shape> Line::clone() const {
    return std::make_unique<Line>(*this);
}

std::string Line::name() const {
    return std::format("Line ({},{}) to ({},{})", from_.x, from_.y, to_.x, to_.y);
}

// ---------------------------------------------------------------------------
// Triangle
// ---------------------------------------------------------------------------
Triangle::Triangle(Point a, Point b, Point c, Color color)
    : a_{a}, b_{b}, c_{c}, color_{color} {}

namespace {

// Which side of the line from p to q the point r lies on: positive on one
// side, negative on the other, zero on the line itself.
int side(Point p, Point q, Point r) {
    return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}

}   // namespace

void Triangle::draw(Canvas& canvas) const {
    const int left{std::min({a_.x, b_.x, c_.x})};
    const int right{std::max({a_.x, b_.x, c_.x})};
    const int top{std::min({a_.y, b_.y, c_.y})};
    const int bottom{std::max({a_.y, b_.y, c_.y})};

    // A point is inside the triangle when it lies on the same side of all
    // three edges.
    for (int y{top}; y <= bottom; ++y) {
        for (int x{left}; x <= right; ++x) {
            const Point p{x, y};
            const int s1{side(a_, b_, p)};
            const int s2{side(b_, c_, p)};
            const int s3{side(c_, a_, p)};
            const bool all_non_negative{s1 >= 0 && s2 >= 0 && s3 >= 0};
            const bool all_non_positive{s1 <= 0 && s2 <= 0 && s3 <= 0};
            if (all_non_negative || all_non_positive) {
                canvas.set_pixel(x, y, color_);
            }
        }
    }
}

void Triangle::translate(int dx, int dy) {
    for (Point* point : {&a_, &b_, &c_}) {
        point->x += dx;
        point->y += dy;
    }
}

std::unique_ptr<Shape> Triangle::clone() const {
    return std::make_unique<Triangle>(*this);
}

std::string Triangle::name() const {
    return "Triangle";
}

// ---------------------------------------------------------------------------
// Group
// ---------------------------------------------------------------------------
Group::Group(std::string label)
    : label_{std::move(label)} {}

Group& Group::add(std::unique_ptr<Shape> shape) {
    children_.push_back(std::move(shape));
    return *this;
}

// One loop, and every child draws itself as its own type. A child that is
// itself a Group simply does the same again, one level down.
void Group::draw(Canvas& canvas) const {
    for (const auto& child : children_) {
        child->draw(canvas);
    }
}

void Group::translate(int dx, int dy) {
    for (const auto& child : children_) {
        child->translate(dx, dy);
    }
}

// A DEEP clone: every child is cloned too, so the copy shares nothing with
// the original and can be moved or changed on its own.
std::unique_ptr<Shape> Group::clone() const {
    auto copy{std::make_unique<Group>(label_)};
    for (const auto& child : children_) {
        copy->add(child->clone());
    }
    return copy;
}

std::string Group::name() const {
    return std::format("Group '{}' ({} shapes)", label_, count());
}

int Group::count() const {
    int total{0};
    for (const auto& child : children_) {
        total += child->count();
    }
    return total;
}
