module;

#include <stdexcept>
#include <utility>
#include <fmt/format.h>

module canvas;

namespace raw{
    Canvas::Canvas(std::size_t width, std::size_t height)
        : m_width{width}, m_height{height} {
        m_pixels = new Pixel*[m_width];
        for (std::size_t i = 0; i < m_width; ++i) {
            m_pixels[i] = new Pixel[m_height];
        }
    }

    Canvas::Canvas(const Canvas& src)
        : Canvas(src.m_width, src.m_height) {
        for (std::size_t i = 0; i < m_width; ++i) {
            for (std::size_t j = 0; j < m_height; ++j) {
                m_pixels[i][j] = src.m_pixels[i][j];
            }
        }
    }

    Canvas::~Canvas() {
        for (std::size_t i = 0; i < m_width; ++i) {
            delete[] m_pixels[i];
        }
        delete[] m_pixels;
        fmt::println("Canvas destroyed");
    }

    //Copy assignment operator without the copy and swap idiom
    /*
    Canvas& Canvas::operator=(const Canvas& rhs) {
        if (this == &rhs) {
            return *this;
        }

        // Clean up existing resources
        for (std::size_t i = 0; i < m_width; ++i) {
            delete[] m_pixels[i];
        }
        delete[] m_pixels;

        // Reallocate and copy
        m_width = rhs.m_width;
        m_height = rhs.m_height;

        m_pixels = new Pixel*[m_width];
        for (std::size_t i = 0; i < m_width; ++i) {
            m_pixels[i] = new Pixel[m_height];
        }

        for (std::size_t i = 0; i < m_width; ++i) {
            for (std::size_t j = 0; j < m_height; ++j) {
                m_pixels[i][j] = rhs.m_pixels[i][j];
            }
        }

        return *this;
    }
    */

    //Copy assignment operator with the copy and swap idiom
    Canvas& Canvas::operator=(const Canvas& rhs) {
        Canvas temp(rhs);
        swap(temp);
        return *this;
    }

    void Canvas::set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel) {
        verify_coordinate(x, y);
        m_pixels[x][y] = pixel;
    }

    Pixel& Canvas::get_pixel_at(std::size_t x, std::size_t y) {
        verify_coordinate(x, y);
        return m_pixels[x][y];
    }

    void Canvas::swap(Canvas& other) noexcept {
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_pixels, other.m_pixels);
    }

    void Canvas::print() const {
            for (std::size_t y = 0; y < m_height; ++y) {
                for (std::size_t x = 0; x < m_width; ++x) {
                    const Pixel& pixel = m_pixels[y][x];
                    auto color = pixel.get_color();
                    fmt::print("#{0:06X} ", color);
                }
                fmt::print("\n");
            }
        }

    void Canvas::verify_coordinate(std::size_t x, std::size_t y) const {
        if (x >= m_width || y >= m_height) {
            throw std::out_of_range("Invalid coordinate");
        }
    }

    void swap(Canvas& first, Canvas& second) noexcept {
        first.swap(second);
    }

}   // namespace raw

namespace modern{

    Canvas::Canvas(std::size_t width, std::size_t height)
        : m_width(width), m_height(height), m_pixels(width, std::vector<Pixel>(height)) {}

    Canvas::Canvas(const Canvas& src)
        : m_width(src.m_width), m_height(src.m_height), m_pixels(src.m_pixels) {}

    void Canvas::set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel) {
        verify_coordinate(x, y);
        m_pixels[x][y] = pixel;
    }

    Pixel& Canvas::get_pixel_at(std::size_t x, std::size_t y) {
        verify_coordinate(x, y);
        return m_pixels[x][y];
    }

    void Canvas::print() const {
        for (const auto& row : m_pixels) {
            for (const auto& pixel : row) {
                fmt::print("{:06X} ", pixel.get_color());
            }
            fmt::print("\n");
        }
    }

    void Canvas::verify_coordinate(std::size_t x, std::size_t y) const {
        if (x >= m_width || y >= m_height) {
            throw std::out_of_range("Coordinate out of range");
        }
    }
} // namespace modern



