/*
        . Refactoring the pimpl example to use the rule of zero
            . The new code is stored in the modern namespace
            . We store pixels in a vector instead of a 2D array
            . The set_pixel_at and get_pixel_at methods are updated to work with the new storage
                . using the formula x * m_width + y to calculate the index of the pixel in the vector
                . this formula is known as row-major order
        . Problems: 
            . Storing Canvas::Impl definition in the implementation file is causing 
                an error claiming that the definition of Impl is not found
            . We can get away with storing the definition in the module interface file
                but this is not the best practice
            . The implementation details are leaking in the interface file, but we'll leave it to that for now.

*/
module;

#include <cstddef>
#include <fmt/format.h>
#include <vector>
#include <memory>

export module canvas;

export import pixel;

namespace raw{
    export class Canvas {
    public:
        Canvas(std::size_t width, std::size_t height);

        Canvas(const Canvas& src);
        Canvas& operator=(const Canvas& rhs);

        ~Canvas();

        Canvas(Canvas&& other) noexcept;
        Canvas& operator=(Canvas&& other) noexcept;

        void set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel);
        const Pixel& get_pixel_at(std::size_t x, std::size_t y) const;

        void swap(Canvas& other) noexcept;
        void print() const;
    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
    };
    export void swap(Canvas& first, Canvas& second) noexcept;
}   // namespace raw

namespace modern{

    export class Canvas {
    public:
        Canvas(std::size_t width, std::size_t height);

        void set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel);
        const Pixel& get_pixel_at(std::size_t x, std::size_t y) const;

        void print() const;
    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
    };

    //Canvas Impl definition
    class Canvas::Impl {
        public:
            Impl(std::size_t width, std::size_t height);

            void set_pixel_at(std::size_t x, std::size_t y, const Pixel& pixel);
            const Pixel& get_pixel_at(std::size_t x, std::size_t y) const;

            void print() const;

        private:
            void verify_coordinate(std::size_t x, std::size_t y) const;
            std::size_t m_width{ 0 };
            std::size_t m_height{ 0 };
            std::vector<Pixel> m_pixels;
    };

}   // namespace modern