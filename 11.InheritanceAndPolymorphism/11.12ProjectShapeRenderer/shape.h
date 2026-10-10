#pragma once

#include <memory>
#include <string>

#include "canvas.h"

// The ABSTRACT base class every shape derives from. It states what a shape
// can do, and nothing about how. Code that draws a picture depends only on
// this class, so a new kind of shape can be added without touching any of it.
class Shape {
public:
    // Virtual: shapes are deleted through Shape pointers (11.6).
    virtual ~Shape() = default;

    // Paint this shape onto the canvas.
    virtual void draw(Canvas& canvas) const = 0;

    // Move this shape by (dx, dy) pixels.
    virtual void translate(int dx, int dy) = 0;

    // Make an independent copy of this shape, whatever its real type is. A
    // copy constructor cannot do that through a base pointer: it would slice
    // (11.4). A virtual clone() can, because each derived class builds a copy
    // of ITSELF.
    virtual std::unique_ptr<Shape> clone() const = 0;

    virtual std::string name() const = 0;

    // How many drawable shapes this is. One, unless it is a group.
    virtual int count() const { return 1; }

protected:
    // Derived classes need to be copyable, so that clone() can copy them. But
    // outsiders must not be able to copy a Shape by value: that is slicing. So
    // the copy operations exist, and are protected.
    Shape() = default;
    Shape(const Shape&) = default;
    Shape& operator=(const Shape&) = default;
};
