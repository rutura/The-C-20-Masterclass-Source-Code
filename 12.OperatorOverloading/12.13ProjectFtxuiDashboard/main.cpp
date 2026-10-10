#include <format>
#include <print>
#include <string>
#include <vector>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

#include "decorators.h"

// PROJECT, part C: a weather dashboard, drawn with ftxui.
//
// One row per sensor: its name, a gauge showing where the reading sits on a
// 0 to 40 degree scale, and the value with a status badge. The layout is a TREE
// of elements, and almost every line below uses the overloaded | operator that
// chapter 12 is about, including two decorators of our own (decorators.h).

using ftxui::bold;
using ftxui::border;
using ftxui::center;
using ftxui::Element;
using ftxui::EQUAL;
using ftxui::gauge;
using ftxui::hbox;
using ftxui::separator;
using ftxui::size;
using ftxui::text;
using ftxui::vbox;
using ftxui::WIDTH;
using ftxui::window;

struct SensorReading {
    std::string name;
    double celsius;
};

std::string status_for(double celsius) {
    if (celsius < 10.0) {
        return "COLD";
    }
    if (celsius > 30.0) {
        return "HOT";
    }
    return "OK";
}

// Build the element for one row.
Element row(const SensorReading& reading) {
    return hbox({
        text(reading.name) | size(WIDTH, EQUAL, 8),
        gauge(static_cast<float>(reading.celsius / 40.0)) | size(WIDTH, EQUAL, 24) | level_color(reading.celsius),
        text(std::format(" {:5.1f} C ", reading.celsius)) | level_color(reading.celsius) | badge(status_for(reading.celsius)),
    });
}

int main() {

    const std::vector<SensorReading> readings{
        {"north", 21.5},
        {"east", 8.0},
        {"roof", 33.5},
        {"cellar", 14.0},
    };

    // Collect the rows into a list of elements.
    std::vector<Element> rows;
    for (const SensorReading& reading : readings) {
        rows.push_back(row(reading));
    }

    // Assemble the whole dashboard: a window with a title, a separator, the
    // rows, and a footer, each decorated with |.
    Element dashboard = window(
        text(" Weather station ") | bold,
        vbox({
            vbox(std::move(rows)),
            separator(),
            text(std::format("{} sensors reporting", readings.size())) | center,
        })
    );

    // Render the element tree into a Screen and print it.
    auto screen = ftxui::Screen::Create(ftxui::Dimension::Fit(dashboard));
    ftxui::Render(screen, dashboard);
    screen.Print();
    std::println("");

    // Next steps, not part of this folder: ftxui can also make the dashboard
    // INTERACTIVE (buttons, menus, a screen that refreshes), with
    // ftxui::ScreenInteractive and the ftxui::component library that is already
    // linked in the CMakeLists.txt. Its documentation has examples.
    return 0;
}
