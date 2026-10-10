#pragma once

#include <string>
#include <utility>

#include <ftxui/dom/elements.hpp>

// Our OWN decorators, written to be used with ftxui's overloaded | operator.
//
// ftxui defines   Element operator|(Element, Decorator)   where a Decorator is
// any callable that takes an Element and returns an Element (a
// std::function<Element(Element)>). So a function that RETURNS a lambda of that
// shape is a decorator, and plugs into the pipe exactly like ftxui's own bold
// and border:
//
//     text("21.5 C") | level_color(21.5) | badge("OK")
//
// This is the same idea as the Bold, Pad and Border structs of 12.10, with the
// library supplying the operator| for us.

// Colour an element by how warm the reading is: blue when cold, red when hot,
// green otherwise.
inline ftxui::Decorator level_color(double celsius) {
    ftxui::Color chosen{ftxui::Color::Green};
    if (celsius < 10.0) {
        chosen = ftxui::Color::Blue;
    }
    else if (celsius > 30.0) {
        chosen = ftxui::Color::Red;
    }
    return ftxui::color(chosen);                      // ftxui's own decorator, returned from ours
}

// Put a small bold tag in front of an element: [OK] 21.5 C
inline ftxui::Decorator badge(std::string label) {
    return [label = std::move(label)](ftxui::Element inner) {
        return ftxui::hbox({
            ftxui::text("[" + label + "] ") | ftxui::bold,
            std::move(inner),
        });
    };
}
