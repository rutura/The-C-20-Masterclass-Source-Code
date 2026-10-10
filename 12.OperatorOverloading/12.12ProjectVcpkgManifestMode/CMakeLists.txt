cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# In manifest mode there is nothing to install by hand. When CMake configures
# with vcpkg's toolchain file, vcpkg reads vcpkg.json (next to this file),
# builds every library listed there, and puts the results in a folder inside the
# build directory (build/vcpkg_installed). This line then finds them.
find_package(ftxui CONFIG REQUIRED)

# Create executable
add_executable(rooster main.cpp)

# ftxui is split into three libraries, each one a target:
#   ftxui::screen      the grid of coloured characters that is drawn
#   ftxui::dom         the layout elements: text, hbox, vbox, border, gauge ...
#   ftxui::component   interactive pieces (buttons, menus). Not used in this folder.
target_link_libraries(rooster PRIVATE ftxui::screen ftxui::dom ftxui::component)
