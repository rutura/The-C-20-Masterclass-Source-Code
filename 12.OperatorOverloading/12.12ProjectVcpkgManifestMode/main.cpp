#include <print>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

// PROJECT, part B: manifest mode, and a first look at ftxui.
//
// ftxui is a library for drawing text-mode user interfaces: boxes, borders,
// colours and gauges, in the terminal. It describes a screen as a TREE OF
// ELEMENTS (a layout), and then renders it.
//
// The important line is this one, which you will recognize from 12.10:
//
//     text("north") | bold | border
//
// | is an overloaded operator. Each decorator on the right wraps the element on
// the left in something new: here, make it bold, then put a border around it.

// Explicit using-declarations instead of "using namespace ftxui;": each name
// is listed, so a reader can see exactly what comes from the library.
using ftxui::bold;
using ftxui::border;
using ftxui::center;
using ftxui::color;
using ftxui::Color;
using ftxui::Element;
using ftxui::hbox;
using ftxui::separator;
using ftxui::text;
using ftxui::vbox;

int main() {

    // A layout is built from the inside out: text, joined by hbox (a row) and
    // vbox (a column), decorated with |.
    Element panel = vbox({
        text("Weather station") | bold | center,
        separator(),
        hbox({text("north  "), text("21.5 C") | color(Color::Green)}),
        hbox({text("east   "), text("19.0 C") | color(Color::Blue)}),
        hbox({text("roof   "), text("33.5 C") | color(Color::Red)}),
    }) | border;

    // A Screen is a grid of character cells. Render() fills it from the
    // element tree, and Print() writes it to the terminal, with colours, as
    // escape sequences. Dimension::Fit makes the screen exactly as big as the
    // element needs.
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(panel));
    ftxui::Render(screen, panel);
    screen.Print();
    std::println("");

    return 0;
}
