#include <memory>
#include <print>
#include <utility>

#include "canvas.h"
#include "shapes.h"

// PROJECT: draw a picture from shapes.
//
// This file never mentions how a circle or a triangle is drawn. It builds a
// Group of shapes and asks it to draw(). Everything else is polymorphism:
// each shape draws itself, a Group draws its children, and a child that is
// itself a Group draws ITS children.

int main() {

    const Color sky{135, 206, 235};
    const Color grass{70, 160, 70};
    const Color sun_yellow{255, 220, 60};
    const Color wall{230, 220, 200};
    const Color roof_red{170, 60, 50};
    const Color door_brown{110, 70, 40};
    const Color mast_grey{90, 90, 90};
    const Color sensor_red{220, 40, 40};

    // One weather station: a small house with a mast carrying a sensor.
    Group station{"station"};
    station.add(std::make_unique<Rectangle>(60, 160, 90, 60, wall))
           .add(std::make_unique<Triangle>(Point{50, 160}, Point{105, 110}, Point{160, 160}, roof_red))
           .add(std::make_unique<Rectangle>(95, 185, 20, 35, door_brown))
           .add(std::make_unique<Line>(Point{180, 220}, Point{180, 120}, mast_grey, 4))
           .add(std::make_unique<Circle>(180, 112, 9, sensor_red));

    // The whole scene is a group too. The station appears twice: the second
    // one is a CLONE of the first, moved to the right. clone() copies the
    // station whatever its real type is, and all its children with it.
    Group scene{"scene"};
    scene.add(std::make_unique<Rectangle>(0, 220, 400, 80, grass))
         .add(std::make_unique<Circle>(340, 55, 32, sun_yellow))
         .add(station.clone());

    auto second_station{station.clone()};
    second_station->translate(175, 12);
    scene.add(std::move(second_station));

    // What did we build? Each shape reports its own name, virtually.
    std::println("{}", scene.name());
    for (const auto& child : scene.children()) {
        std::println("  {}", child->name());
    }

    Canvas canvas{400, 300, sky};
    scene.draw(canvas);

    if (canvas.write_png("scene.png")) {
        std::println("\nwrote scene.png ({} x {})", canvas.width(), canvas.height());
    }
    else {
        std::println("\ncould not write scene.png");
        return 1;
    }

    // Try this: add a new class, Ellipse, derived from Shape, in a new
    // header and source file. Not one line of Canvas, Group or this main
    // needs to change for it to be drawn. That is what "open for extension"
    // means, and it is the reason for all of this chapter.
    return 0;
}
