#pragma once

#include <memory>
#include <string>
#include <vector>

#include "color.h"
#include "shape.h"

struct Point {
    int x;
    int y;
};

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int width, int height, Color color);

    void draw(Canvas& canvas) const override;
    void translate(int dx, int dy) override;
    std::unique_ptr<Shape> clone() const override;
    std::string name() const override;

private:
    int x_;
    int y_;
    int width_;
    int height_;
    Color color_;
};

class Circle : public Shape {
public:
    Circle(int center_x, int center_y, int radius, Color color);

    void draw(Canvas& canvas) const override;
    void translate(int dx, int dy) override;
    std::unique_ptr<Shape> clone() const override;
    std::string name() const override;

private:
    int center_x_;
    int center_y_;
    int radius_;
    Color color_;
};

class Line : public Shape {
public:
    Line(Point from, Point to, Color color, int thickness = 1);

    void draw(Canvas& canvas) const override;
    void translate(int dx, int dy) override;
    std::unique_ptr<Shape> clone() const override;
    std::string name() const override;

private:
    Point from_;
    Point to_;
    Color color_;
    int thickness_;
};

class Triangle : public Shape {
public:
    Triangle(Point a, Point b, Point c, Color color);

    void draw(Canvas& canvas) const override;
    void translate(int dx, int dy) override;
    std::unique_ptr<Shape> clone() const override;
    std::string name() const override;

private:
    Point a_;
    Point b_;
    Point c_;
    Color color_;
};

// A Group is a Shape that CONTAINS other shapes. It is a shape too, so a
// group can hold groups, and the code that draws a picture does not have to
// know the difference. It is the "has-a" of 10.11 and the "is-a" of this
// chapter at the same time.
class Group : public Shape {
public:
    explicit Group(std::string label);

    // Takes ownership of the shape. Returns *this, so adds can be chained (10.10).
    Group& add(std::unique_ptr<Shape> shape);

    void draw(Canvas& canvas) const override;
    void translate(int dx, int dy) override;
    std::unique_ptr<Shape> clone() const override;
    std::string name() const override;
    int count() const override;

    const std::vector<std::unique_ptr<Shape>>& children() const { return children_; }

private:
    std::string label_;
    std::vector<std::unique_ptr<Shape>> children_;
};
