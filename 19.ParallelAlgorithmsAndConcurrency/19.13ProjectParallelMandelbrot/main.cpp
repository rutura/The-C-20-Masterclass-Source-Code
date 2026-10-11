#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <execution>
#include <future>
#include <numeric>
#include <print>
#include <string>
#include <thread>
#include <vector>

#include "canvas.h"
#include "color.h"
#include "thread_pool.h"

// PROJECT: draw the Mandelbrot set onto the Canvas of chapter 10, four ways,
// and measure what the extra cores buy.
//
// For every pixel, treat it as a point c = (cr, ci) of the plane and repeat
//
//     z = z * z + c        starting from z = 0
//
// until z gets farther than 2 from the origin (the point ESCAPES) or we give
// up after max_iterations rounds (the point is IN the set: painted black).
// How many rounds it took picks the colour. Every pixel is independent of the
// others, which is the best case for parallel work. But NOT every pixel costs
// the same: points outside the set escape in a few rounds, points inside run
// the full max_iterations. That unevenness is what makes the way we split
// the work matter.

struct View {
    double left;              // real part at x = 0
    double top;               // imaginary part at y = 0
    double step;              // distance between neighbouring pixels
    int max_iterations;
};

int escape_time(double cr, double ci, int max_iterations) {
    double zr{0.0};
    double zi{0.0};
    int rounds{0};
    while (rounds < max_iterations && zr * zr + zi * zi <= 4.0) {
        double next_zr{zr * zr - zi * zi + cr};
        zi = 2.0 * zr * zi + ci;
        zr = next_zr;
        ++rounds;
    }
    return rounds;
}

Color colour_for(int rounds, int max_iterations) {
    if (rounds >= max_iterations) {
        return Color{0, 0, 0};
    }
    auto shade{static_cast<std::uint8_t>((rounds * 5) % 256)};
    return Color{shade, static_cast<std::uint8_t>(shade / 2), static_cast<std::uint8_t>(255 - shade)};
}

// ONE row is the unit of work in every version below. Each call writes only
// the pixels of its own row, so no two threads ever write the same byte of
// the canvas: no data race (19.4), and no lock needed.
void render_row(Canvas& canvas, const View& view, int y) {
    double ci{view.top + y * view.step};
    for (int x{0}; x < canvas.width(); ++x) {
        double cr{view.left + x * view.step};
        canvas.set_pixel(x, y, colour_for(escape_time(cr, ci, view.max_iterations), view.max_iterations));
    }
}

// ---- Version 1: one thread ---------------------------------------------------------
void render_serial(Canvas& canvas, const View& view) {
    for (int y{0}; y < canvas.height(); ++y) {
        render_row(canvas, view, y);
    }
}

// ---- Version 2: a parallel algorithm (19.2) -------------------------------------------
// The least code: for_each over the row numbers with the par policy. The
// library decides how to split and who runs what (in chunks, with work stealing).
void render_with_par(Canvas& canvas, const View& view) {
    std::vector<int> rows(static_cast<std::size_t>(canvas.height()));
    std::iota(rows.begin(), rows.end(), 0);
    std::for_each(std::execution::par, rows.begin(), rows.end(), [&canvas, &view](int y) {
        render_row(canvas, view, y);
    });
}

// ---- Version 3: threads, one fixed band each (19.3) ------------------------------------
// Cut the picture into as many equal bands as there are hardware threads, and
// give each thread one band. Simple, and it has a flaw: the bands in the
// middle of the picture are full of points of the set (the slow ones), so
// those threads finish long after the threads that got the cheap top and
// bottom. Most threads then sit idle waiting for the slowest.
void render_with_bands(Canvas& canvas, const View& view, unsigned thread_count) {
    int rows_per_band{(canvas.height() + static_cast<int>(thread_count) - 1) / static_cast<int>(thread_count)};
    std::vector<std::jthread> threads;
    for (unsigned t{0}; t < thread_count; ++t) {
        int first{static_cast<int>(t) * rows_per_band};
        int last{std::min(first + rows_per_band, canvas.height())};
        threads.emplace_back([&canvas, &view, first, last] {
            for (int y{first}; y < last; ++y) {
                render_row(canvas, view, y);
            }
        });
    }
}

// ---- Version 4: a thread pool with one small job per row (19.10) -------------------------
// Many small jobs: whenever a worker finishes a row it takes the next one from
// the queue, so a worker that got cheap rows simply does more of them. The
// work balances itself, at the price of one queue operation per row.
void render_with_pool(ThreadPool& pool, Canvas& canvas, const View& view) {
    std::vector<std::future<void>> rows;
    rows.reserve(static_cast<std::size_t>(canvas.height()));
    for (int y{0}; y < canvas.height(); ++y) {
        rows.push_back(pool.submit([&canvas, &view, y] { render_row(canvas, view, y); }));
    }
    for (std::future<void>& row : rows) {
        row.get();
    }
}

// ---- Measuring ---------------------------------------------------------------------------------
// The best of three runs: the least disturbed by whatever else the computer was doing.
template <typename Work>
double best_milliseconds(Work&& work) {
    double best{1e300};
    for (int run{0}; run < 3; ++run) {
        auto started{std::chrono::steady_clock::now()};
        work();
        double elapsed{std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - started).count()};
        best = std::min(best, elapsed);
    }
    return best;
}

bool same_pixels(const Canvas& a, const Canvas& b) {
    if (a.width() != b.width() || a.height() != b.height()) {
        return false;
    }
    for (int y{0}; y < a.height(); ++y) {
        for (int x{0}; x < a.width(); ++x) {
            Color left{a.pixel(x, y)};
            Color right{b.pixel(x, y)};
            if (left.r != right.r || left.g != right.g || left.b != right.b) {
                return false;
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    int width{argc > 1 ? std::stoi(argv[1]) : 1600};
    int height{argc > 2 ? std::stoi(argv[2]) : 1200};
    int max_iterations{argc > 3 ? std::stoi(argv[3]) : 500};

    // The window on the plane: 3 units wide, centred on -0.7 + 0i.
    View view{-2.2, -1.125, 3.0 / width, max_iterations};

    unsigned hardware{std::max(1u, std::thread::hardware_concurrency())};
    std::println("Mandelbrot {} x {}, up to {} rounds per pixel", width, height, max_iterations);
    std::println("[varies] {} hardware threads", hardware);

    Canvas serial{width, height};
    Canvas with_par{width, height};
    Canvas with_bands{width, height};
    Canvas with_pool{width, height};
    ThreadPool pool{hardware};

    double serial_ms{best_milliseconds([&] { render_serial(serial, view); })};
    double par_ms{best_milliseconds([&] { render_with_par(with_par, view); })};
    double bands_ms{best_milliseconds([&] { render_with_bands(with_bands, view, hardware); })};
    double pool_ms{best_milliseconds([&] { render_with_pool(pool, with_pool, view); })};

    std::println("[varies] {:<28} {:8.1f} ms", "one thread", serial_ms);
    std::println("[varies] {:<28} {:8.1f} ms   speedup {:.1f}x", "std::execution::par", par_ms, serial_ms / par_ms);
    std::println("[varies] {:<28} {:8.1f} ms   speedup {:.1f}x", "one band per thread", bands_ms, serial_ms / bands_ms);
    std::println("[varies] {:<28} {:8.1f} ms   speedup {:.1f}x", "thread pool, a job per row", pool_ms, serial_ms / pool_ms);

    // A faster program that draws a different picture would be a bug.
    std::println("par is identical to serial: {}", same_pixels(serial, with_par));
    std::println("bands are identical to serial: {}", same_pixels(serial, with_bands));
    std::println("pool is identical to serial: {}", same_pixels(serial, with_pool));

    if (serial.write_png("mandelbrot.png")) {
        std::println("wrote mandelbrot.png ({} x {})", serial.width(), serial.height());
    }
    else {
        std::println("could not write mandelbrot.png");
        return 1;
    }
    return 0;
}
