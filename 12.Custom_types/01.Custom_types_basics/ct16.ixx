/*
    . Add serialization to binary file for Pixel class
    . Flexes our muscles with file I/O
*/
module;

#include <cstdint>
#include <filesystem>
#include <memory>
#include <fmt/format.h>
#include <fstream>
#include <vector>

export module ct16;

namespace ct16{

   export struct Position {
        unsigned int x{0};
        unsigned int y{0};
    };

    export class Pixel {
    public:
        Pixel() = default;
        Pixel(uint32_t color, unsigned int x, unsigned int y);
        
        // Copy constructor for deep copy
        Pixel(const Pixel& other);

        // Copy assignment operator using copy-and-swap idiom
        Pixel& operator=(const Pixel &other);

        ~Pixel();
        
        // Getters and setters for color
        uint32_t get_color() const;
        void set_color(uint32_t color);

        // Getters and setters for raw pointer (m_pos)
        unsigned int get_x() const;
        unsigned int get_y() const;
        void set_x(unsigned int x);
        void set_y(unsigned int y);

        // Getters and setters for smart pointer (m_smart_pos)
        unsigned int get_smart_x() const;
        unsigned int get_smart_y() const;
        void set_smart_x(unsigned int x);
        void set_smart_y(unsigned int y);

        // Member swap function
        void swap(Pixel& other){
            std::swap(m_color, other.m_color);
            std::swap(m_pos, other.m_pos);
            std::swap(m_smart_pos, other.m_smart_pos);
        }

        // Serialization function for a single Pixel
        void serialize(std::ofstream& ofs) const {
            ofs.write(reinterpret_cast<const char*>(&m_color), sizeof(m_color));
            ofs.write(reinterpret_cast<const char*>(&m_pos->x), sizeof(m_pos->x));
            ofs.write(reinterpret_cast<const char*>(&m_pos->y), sizeof(m_pos->y));
        }

        // Deserialization function for a single Pixel
        void deserialize(std::ifstream& ifs) {
            ifs.read(reinterpret_cast<char*>(&m_color), sizeof(m_color));
            m_pos = new Position();
            ifs.read(reinterpret_cast<char*>(&m_pos->x), sizeof(m_pos->x));
            ifs.read(reinterpret_cast<char*>(&m_pos->y), sizeof(m_pos->y));
        }

    private:
        uint32_t m_color{0xFF000000};
        Position* m_pos{nullptr}; // Raw pointer for position
        std::unique_ptr<Position> m_smart_pos; // Smart pointer for position
    };

    // Constructor
    Pixel::Pixel(uint32_t color, unsigned int x, unsigned int y)
        : m_color{color}, 
          m_pos{new Position{x, y}}, 
          m_smart_pos{std::make_unique<Position>(Position{x, y})} 
    {
    }

    // Copy constructor for deep copy with raw pointer and smart pointer
    Pixel::Pixel(const Pixel& other)
        : m_color{other.m_color}, 
          m_pos{new Position{*other.m_pos}}, 
          m_smart_pos{std::make_unique<Position>(*other.m_smart_pos)} {
        fmt::print("Pixel deep copied (with both raw and smart pointers)\n");
    }

    // Copy assignment operator using copy-and-swap idiom
    Pixel& Pixel::operator=(const Pixel& other) {
        Pixel temp(other); // Create a temporary copy
        swap(temp); // Swap the contents with the temporary copy
        fmt::print("Pixel copy-assigned (with both raw and smart pointers)\n");
        return *this;
    }

    // Destructor to clean up raw pointer
    Pixel::~Pixel() {
        delete m_pos; // Clean up memory allocated by raw pointer
        fmt::print("Pixel destroyed\n");
    }

    // Get color
    uint32_t Pixel::get_color() const {
        return m_color;
    }

    // Set color
    void Pixel::set_color(uint32_t color) {
        m_color = color;
    }

    // Getters for raw pointer position (m_pos)
    unsigned int Pixel::get_x() const {
        return m_pos->x;
    }

    unsigned int Pixel::get_y() const {
        return m_pos->y;
    }

    // Setters for raw pointer position (m_pos)
    void Pixel::set_x(unsigned int x) {
        m_pos->x = x;
    }

    void Pixel::set_y(unsigned int y) {
        m_pos->y = y;
    }

    // Getters for smart pointer position (m_smart_pos)
    unsigned int Pixel::get_smart_x() const {
        return m_smart_pos->x;
    }

    unsigned int Pixel::get_smart_y() const {
        return m_smart_pos->y;
    }

    // Setters for smart pointer position (m_smart_pos)
    void Pixel::set_smart_x(unsigned int x) {
        m_smart_pos->x = x;
    }

    void Pixel::set_smart_y(unsigned int y) {
        m_smart_pos->y = y;
    }

    // Global swap function
    void swap(Pixel& first, Pixel& second) {
        first.swap(second);
    }

    

    // Function to write a vector of Pixel objects to a file
    export void write_pixels_to_file(const std::vector<Pixel>& pixels, const std::filesystem::path& file_path) {
        std::ofstream ofs(file_path, std::ios::binary);
        if (!ofs) {
            fmt::print("Failed to open file for writing: {}\n", file_path.string());
            return;
        }

        size_t vector_size = pixels.size();
        ofs.write(reinterpret_cast<const char*>(&vector_size), sizeof(vector_size));

        for (const auto& p : pixels) {
            p.serialize(ofs);
        }

        fmt::print("Serialized {} pixel(s) to file: {}\n", vector_size, file_path.string());
    }

    // Function to read a vector of Pixel objects from a file
    export std::vector<Pixel> read_pixels_from_file(const std::filesystem::path& file_path) {
        std::ifstream ifs(file_path, std::ios::binary);
        if (!ifs) {
            fmt::print("Failed to open file for reading: {}\n", file_path.string());
            return {};
        }

        size_t vector_size;
        ifs.read(reinterpret_cast<char*>(&vector_size), sizeof(vector_size));

        std::vector<Pixel> pixels(vector_size);
        for (auto& p : pixels) {
            p.deserialize(ifs);
        }

        fmt::print("Deserialized {} pixel(s) from file: {}\n", vector_size, file_path.string());
        return pixels;
    }

} // namespace ct16