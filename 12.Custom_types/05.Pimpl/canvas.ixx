/*
        . Refactoring the Canvas class to use the Pimpl idiom.

        . Benefits: 
            . Faster compile times
            . Better encapsulation
            . Better separation of concerns

        . How: 
            . The module interface file only contains the public interface of the Canvas class.
            . The only private member of the Canvas class is a pointer to an Impl class.
            . All methods in the public interface forward the work to the Impl class.
            . Because the Impl member is a pointer, changes in the implementation don't cause for recompilation of the module interface file.
            . The Impl class definition is basicall what we had in the Canvas class before the refactoring, but just 
                moved inside the Impl class.
            . The rest is just rewiring the Canvas class to use the Impl class.
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