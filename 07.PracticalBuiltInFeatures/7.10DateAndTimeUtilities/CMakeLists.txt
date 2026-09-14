cmake_minimum_required(VERSION 3.20)

# Project name
project(rooster)

# Set C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This lecture is split into one file per topic, each with its own main() -
# mirroring the reference chapter's own file layout, so each can be built
# and stepped through independently while presenting.
add_executable(rooster1_ratios main1_ratios.cpp)
add_executable(rooster2_durations main2_durations.cpp)
add_executable(rooster3_now main3_now.cpp)
add_executable(rooster4_timing main4_timing.cpp)
add_executable(rooster5_time_point main5_time_point.cpp)
add_executable(rooster6_time_point_conversions main6_time_point_conversions.cpp)
add_executable(rooster7_dates main7_dates.cpp)
add_executable(rooster8_time_zones main8_time_zones.cpp)

# main8_time_zones.cpp uses the IANA time zone database (get_tzdb,
# locate_zone, zoned_time). As of Clang 21, libc++ does not implement this
# yet, so that one target will fail to build with Clang - it builds fine
# with MSVC and with GCC's libstdc++.
