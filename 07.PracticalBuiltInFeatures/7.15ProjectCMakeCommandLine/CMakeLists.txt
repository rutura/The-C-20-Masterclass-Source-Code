cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# The library. No STATIC or SHARED keyword: the command line decides.
#   cmake ...                        -> static archive (libstation.a / station.lib)
#   cmake ... -DBUILD_SHARED_LIBS=ON -> dynamic library (.so / .dll)
add_library(station stats.cpp stats.h report.cpp report.h)

# 7.14 wrote the export macro by hand. CMake can generate it: it writes
# station_export.h into the build folder, defining STATION_EXPORT as
# dllexport, dllimport, visibility or nothing, whichever fits this build.
include(GenerateExportHeader)
generate_export_header(station)
target_include_directories(station PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR})
set_target_properties(station PROPERTIES CXX_VISIBILITY_PRESET hidden)

# A static library has nothing to import, so tell the header so.
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(station PUBLIC STATION_STATIC_DEFINE)
endif()

# Create executable
add_executable(rooster main.cpp)
target_link_libraries(rooster PRIVATE station)

# MinGW's GCC 14 needs this extra library for std::println.
if(WIN32 AND NOT MSVC)
    target_link_libraries(rooster PRIVATE stdc++exp)
endif()

# What "cmake --install" copies, and where (relative to --prefix).
install(TARGETS rooster station
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
install(FILES stats.h report.h ${CMAKE_CURRENT_BINARY_DIR}/station_export.h
    DESTINATION include)
