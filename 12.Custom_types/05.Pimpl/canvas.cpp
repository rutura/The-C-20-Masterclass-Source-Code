module;

#include <stdexcept>
#include <utility>
#include <fmt/format.h>
#include <memory>

module canvas;

namespace raw{

    //Canvas::Impl definition
    class Canvas::Impl {
        public:
            Impl(std::size_t width, std::size_t height);

            Impl(const Impl& src);
            Impl& operator=(const Impl& rhs);

            ~Impl();

            Impl(Impl&& other) noexcept;
            Impl& operator=(Impl&& other) noexcept;

            void set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel);
            const Pixel& get_pixel_at(std::size_t x, std::size_t y) const;

            void swap(Impl& other) noexcept;
            void print() const;

        private:
            void verify_coordinate(std::size_t x, std::size_t y) const;
            std::size_t m_width{ 0 };
            std::size_t m_height{ 0 };
            Pixel** m_pixels{ nullptr };
    };


    //Canvas::Impl member implementation
    Canvas::Impl::Impl(std::size_t width, std::size_t height)
        : m_width{width}, m_height{height} {

        fmt::println("Regular constructor");
        m_pixels = new Pixel*[m_width];
        for (std::size_t i = 0; i < m_width; ++i) {
            m_pixels[i] = new Pixel[m_height];
        }
    }

    //Copy constructor
    Canvas::Impl::Impl(const Impl& src)
        : Impl(src.m_width, src.m_height) {
            fmt::println("Copy constructor");
        for (std::size_t i = 0; i < m_width; ++i) {
            for (std::size_t j = 0; j < m_height; ++j) {
                m_pixels[i][j] = src.m_pixels[i][j];
            }
        }
    }
    
    //Copy assignment operator with the copy and swap idiom
    Canvas::Impl& Canvas::Impl::operator=(const Impl& rhs) {
        fmt::println("Copy assignment operator");
        Impl temp(rhs);
        swap(temp);
        return *this;
    }

    //Destructor
    Canvas::Impl::~Impl() {
        for (std::size_t i = 0; i < m_width; ++i) {
            delete[] m_pixels[i];
        }
        delete[] m_pixels;
        fmt::println("Canvas destroyed");
        m_pixels =  nullptr;
    }

    //Move constructor
    Canvas::Impl::Impl(Impl&& other) noexcept{
        fmt::println("Move constructor");
        swap(other); // Steal the data from other and let it die.
    }

    //Move assignment operator through the swap method
    Canvas::Impl& Canvas::Impl::operator=(Impl&& other) noexcept {
        fmt::println("Move assignment operator");
        if (this == &other) {
            return *this;
        }
        swap(other);
        return *this;
    }

    void Canvas::Impl::set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel) {
        verify_coordinate(x, y);
        m_pixels[x][y] = pixel;
    }

    const Pixel& Canvas::Impl::get_pixel_at(std::size_t x, std::size_t y) const {
        verify_coordinate(x, y);
        return m_pixels[x][y];
    }

    void Canvas::Impl::swap(Impl& other) noexcept {
        std::swap(m_width, other.m_width);
        std::swap(m_height, other.m_height);
        std::swap(m_pixels, other.m_pixels);
    }

    void Canvas::Impl::print() const {
        for (std::size_t x = 0; x < m_width; ++x) {
            for (std::size_t y = 0; y < m_height; ++y) {
                const Pixel& pixel = m_pixels[x][y];
                auto color = pixel.get_color();
                fmt::print("#{0:06X} ", color);
            }
            fmt::print("\n");
        }
    }

    void Canvas::Impl::verify_coordinate(std::size_t x, std::size_t y) const {
        if (x >= m_width || y >= m_height) {
            throw std::out_of_range("Invalid coordinate");
        }
    }

    //-------------------------------------------------------------------------//
    //---------------Canvas Implementation in terms of Impl--------------------//
    //-------------------------------------------------------------------------//

    //Canvas constructor
    Canvas::Canvas(std::size_t width, std::size_t height)
        : m_impl{std::make_unique<Impl>(width, height)} {}

    //Copy constructor
    Canvas::Canvas(const Canvas& src)
        : m_impl{std::make_unique<Impl>(*src.m_impl)} {}

    //Move constructor
    Canvas::Canvas(Canvas&& other) noexcept
        : m_impl{std::move(other.m_impl)} {}

    //Destructor
    Canvas::~Canvas() = default;

    //Copy assignment operator
    Canvas& Canvas::operator=(const Canvas& rhs) {
        *m_impl = *rhs.m_impl;
        return *this;
    }

    //Move assignment operator
    Canvas& Canvas::operator=(Canvas&& other) noexcept {
        if (this != &other) {
            m_impl = std::move(other.m_impl);
        }
        return *this;
    }

    //The pixel methods
    const Pixel& Canvas::get_pixel_at(std::size_t x, std::size_t y) const {
        return m_impl->get_pixel_at(x, y);
    }

    void Canvas::set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel) {
        m_impl->set_pixel_at(x, y, pixel);
    }

    void Canvas::swap(Canvas& other) noexcept {
        m_impl->swap(*other.m_impl);
    }

    void Canvas::print() const {
        m_impl->print();
    }

    //Swap method
    void swap(Canvas& first, Canvas& second) noexcept {
        first.swap(second);
    }
}   // namespace raw