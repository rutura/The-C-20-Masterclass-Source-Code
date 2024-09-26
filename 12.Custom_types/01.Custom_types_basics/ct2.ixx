/*
    . Topics: 
        . the private and public access specifiers
        . constructors
            . Compiler generated default constructor
            . Default constructor
            . The need for default constructors
            . Explicitly defaulted default constructor
            . Explicitly deleted default constructor
        . destructors
        . setters and getters
        . const members functions
            . the mutable keyword
        . the this keyword
        . Different ways to allocate objects in C++
            . on the stack
            . on the heap with raw pointers
            . on the heap with smart pointers
*/
module;

#include <cstdint>
#include <fmt/format.h>
#include <chrono>
#include <string>

export module ct2;

namespace ct2{

    export class Pixel {

        public: 
            Pixel() = default;  //Explicitly defaulted default constructor

            Pixel(uint32_t color, unsigned int x, unsigned int y){
                m_color = color;
                m_pos_x = x;
                m_pos_y = y;
            }
            ~Pixel(){
                fmt::print("Pixel destroyed\n");
            }

            uint32_t get_color() const {
                ++m_access_count;
                m_last_accessed = std::chrono::system_clock::now();
                return m_color; 
            }
            void set_color(uint32_t color) {
                this->m_color = color;
                m_last_modified = std::chrono::system_clock::now();
            }

            unsigned int get_x() const {
                ++m_access_count;
                m_last_accessed = std::chrono::system_clock::now();
                return m_pos_x; 
            }
            void set_x(unsigned int x) {
                m_pos_x = x;
                m_last_modified = std::chrono::system_clock::now();
            }

            unsigned int get_y() const {
                ++m_access_count;
                m_last_accessed = std::chrono::system_clock::now();
                return m_pos_y; 
            }
            void set_y(unsigned int y) {
                m_pos_y = y;
                m_last_modified = std::chrono::system_clock::now();
            }

            std::string get_debug_info() const {
                return m_debug_info;
            }
            void set_debug_info(const std::string& info) const {
                m_debug_info = info;
            }

            // Add a function to print all the mutable variables
            void print_log() const {
                
                auto to_readable_time = [](const std::chrono::system_clock::time_point& tp) {
                    std::time_t time = std::chrono::system_clock::to_time_t(tp);
                    char buffer[26];
                    ctime_s(buffer, sizeof(buffer), &time);
                    return std::string(buffer);
                };

                fmt::print("Access count: {}\n", m_access_count);
                fmt::print("Last accessed: {}\n", to_readable_time(m_last_accessed));
                fmt::print("Last modified: {}\n", to_readable_time(m_last_modified));
                fmt::print("Debug info: {}\n", m_debug_info);
            }

        private: 
            uint32_t m_color{0xFF000000};
            unsigned int m_pos_x{0};
            unsigned int m_pos_y{0};

            mutable unsigned int m_access_count{0}; // Tracks how many times the pixel has been accessed
            mutable std::chrono::system_clock::time_point m_last_accessed; // Tracks the last time the pixel was accessed
            mutable std::chrono::system_clock::time_point m_last_modified; // Tracks the last time the pixel was modified
            mutable std::string m_debug_info; // Stores debug information
    };
    
} // namespace ct2