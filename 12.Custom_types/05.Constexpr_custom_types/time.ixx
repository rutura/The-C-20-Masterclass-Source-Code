module;

#include <iostream>
#include <stdexcept>
#include <fmt/format.h>

export module time;

namespace it_1 {
    // Iteration 1 will make the class constexpr
    export class Time24 {
        public:
            // Constructor
            constexpr Time24(int h = 0, int m = 0) : hour(h), minute(m) {
                validate_time();
            }

            // Getter functions
            constexpr int get_hour() const { return hour; }
            constexpr int get_minute() const { return minute; }

            // Set functions
            constexpr void set_hour(int h) {
                hour = h;
                validate_time();
            }

            constexpr void set_minute(int m) {
                minute = m;
                validate_time();
            }

            // Add minutes, wrapping hours correctly
            constexpr void add_minutes(int m) {
                minute += m;
                hour += minute / 60;
                minute %= 60;
                hour %= 24;
            }

            // Add hours
            constexpr void add_hours(int h) {
                hour = (hour + h) % 24;
            }

            void print_time() const {
                fmt::print("{:02}:{:02}\n", hour, minute);
            }

        private:
            int hour;   // 0-23
            int minute; // 0-59

            constexpr void validate_time() const {
                if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60) {
                    throw std::invalid_argument("Invalid time: hour must be [0, 23] and minute [0, 59].");
                }
            }
    };
}  // namespace it_1

namespace it_2 {
    // Iteration 2 will make the class consteval
    export class Time24 {
        public:
            // Constructor
            consteval Time24(int h = 0, int m = 0) : hour(h), minute(m) {
                validate_time();
            }

            // Getter functions
            consteval int get_hour() const { return hour; }
            consteval int get_minute() const { return minute; }

            // Set functions
            consteval void set_hour(int h) {
                hour = h;
                validate_time();
            }

            consteval void set_minute(int m) {
                minute = m;
                validate_time();
            }

            // Add minutes, wrapping hours correctly
            consteval void add_minutes(int m) {
                minute += m;
                hour += minute / 60;
                minute %= 60;
                hour %= 24;
            }

            // Add hours
            consteval void add_hours(int h) {
                hour = (hour + h) % 24;
            }

            void print_time() const {
                fmt::print("{:02}:{:02}\n", hour, minute);
            }

        private:
            int hour;   // 0-23
            int minute; // 0-59

            consteval void validate_time() const {
                if (hour < 0 || hour >= 24 || minute < 0 || minute >= 60) {
                    throw std::invalid_argument("Invalid time: hour must be [0, 23] and minute [0, 59].");
                }
            }
    };
}  // namespace it_2



