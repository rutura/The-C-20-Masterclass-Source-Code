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

    // Position struct definition
    export struct Position {
        unsigned int x{0};
        unsigned int y{0};

        // Constructors
        Position() = default;
        Position(unsigned int x, unsigned int y) : x(x), y(y) {}
    };

    // Pixel class definition
    export class Pixel {
        public:
        // Constructors
        Pixel() : m_pos(new Position()) {}
        Pixel(uint32_t color, unsigned int x, unsigned int y)
            : m_color(color), m_pos(new Position(x, y)) {}

        // Copy constructor
        Pixel(const Pixel& other)
            : m_color(other.m_color), m_pos(new Position(*other.m_pos)) {}

        // Copy assignment operator using the copy-and-swap idiom
        Pixel& operator=(const Pixel& other) {
            Pixel temp(other);  // Explicit copy made here
            swap(temp);
            return *this;
        }

        // Destructor
        ~Pixel() {
            delete m_pos;
        }

        // Getters
        uint32_t get_color() const { return m_color; }
        Position get_position() const { return *m_pos; }

        // Setters
        void set_color(uint32_t color) { m_color = color; }
        void set_position(unsigned int x, unsigned int y) {
            m_pos->x = x;
            m_pos->y = y;
        }

        // Serialization: Save a Pixel object to a binary file
        void serialize(std::ofstream& out) const {
            out.write(reinterpret_cast<const char*>(&m_color), sizeof(m_color));
            out.write(reinterpret_cast<const char*>(m_pos), sizeof(Position));
        }

        // Deserialization: Load a Pixel object from a binary file
        void deserialize(std::ifstream& in) {
            in.read(reinterpret_cast<char*>(&m_color), sizeof(m_color));
            in.read(reinterpret_cast<char*>(m_pos), sizeof(Position));
        }

    

        // Member swap function
        void swap(Pixel& other) noexcept {
            std::swap(m_color, other.m_color);
            std::swap(m_pos, other.m_pos);
        }

        private:
            uint32_t m_color{0xFF000000};
            Position* m_pos{nullptr}; // Raw pointer for position
    };

    export void save_pixels(const std::vector<Pixel>& pixels, const std::filesystem::path& filepath) {
        std::ofstream out(filepath, std::ios::binary);
        if (!out) {
            fmt::println("Error opening file for writing: {}\n", filepath.string());
            return;
        }
        for (const auto& pixel : pixels) {
            pixel.serialize(out);
        }
        out.close();
    }

    export std::vector<Pixel> load_pixels(const std::filesystem::path& filepath) {
        std::vector<Pixel> pixels;
        std::ifstream in(filepath, std::ios::binary);
        if (!in) {
            fmt::println("Error opening file for reading: {}\n", filepath.string());
            return pixels;
        }
        Pixel temp;
        while (in.peek() != EOF) {
            temp.deserialize(in);
            pixels.push_back(temp);
        }
        in.close();
        return pixels;
    }

} // namespace ct16