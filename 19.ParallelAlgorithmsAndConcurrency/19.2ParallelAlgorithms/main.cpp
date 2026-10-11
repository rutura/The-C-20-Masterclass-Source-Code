#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <execution>
#include <numeric>
#include <print>
#include <thread>
#include <vector>

// Until now every algorithm of chapter 15 ran on ONE core. A modern machine
// has many, and most of the standard algorithms accept an EXECUTION POLICY as
// a new first argument that allows them to use them:
//
//     std::transform(first, last, out, f)                        one thread
//     std::transform(std::execution::par, first, last, out, f)   many threads
//
// The policies live in <execution>:
//
//     seq         sequential: the same as no policy
//     par         parallel: the work is split over threads
//     par_unseq   parallel AND vectorized: each thread may also interleave the
//                 steps of several elements (SIMD), so the function must not
//                 take locks or wait for anything
//     unseq       vectorized only, on the calling thread (C++20)
//
// The policy is a PERMISSION, not an order: the library may still run it on
// one thread (a small range, or no TBB: see the CMakeLists.txt).

// Runs `work` and returns how many milliseconds it took. `Work&&` is a
// forwarding reference (16.10): it accepts a lambda of any kind.
template <typename Work>
double milliseconds(Work&& work) {
    auto started{std::chrono::steady_clock::now()};
    work();
    auto finished{std::chrono::steady_clock::now()};
    return std::chrono::duration<double, std::milli>(finished - started).count();
}

// Timings and the machine's size differ from computer to computer, so every
// line that has them starts with [varies].
void report(const char* what, double sequential_ms, double parallel_ms) {
    std::println("[varies] {:<26} seq {:7.1f} ms   par {:7.1f} ms   speedup {:.1f}x",
                 what, sequential_ms, parallel_ms, sequential_ms / parallel_ms);
}

// A pseudo-random sequence that is the same on every machine (like 18.3).
std::vector<std::int32_t> make_numbers(std::size_t count) {
    std::vector<std::int32_t> numbers(count);
    std::uint32_t state{2026};
    for (std::int32_t& number : numbers) {
        state = state * 1664525u + 1013904223u;
        number = static_cast<std::int32_t>(state >> 8);
    }
    return numbers;
}

int main() {
    std::println("[varies] hardware threads: {}", std::thread::hardware_concurrency());

    // ---- 1. transform: independent work on every element ---------------------------
    // Each result depends only on its own input, which is what makes this
    // perfectly parallel. The function is expensive enough to be worth it.
    std::println("--- transform");
    std::vector<double> input(10'000'000);
    std::iota(input.begin(), input.end(), 1.0);
    std::vector<double> sequential_out(input.size());
    std::vector<double> parallel_out(input.size());

    auto heavy{[](double x) { return std::sqrt(x) * std::sin(x); }};

    double sequential_ms{milliseconds([&] {
        std::transform(input.begin(), input.end(), sequential_out.begin(), heavy);
    })};
    double parallel_ms{milliseconds([&] {
        std::transform(std::execution::par, input.begin(), input.end(), parallel_out.begin(), heavy);
    })};
    report("transform of 10M doubles", sequential_ms, parallel_ms);
    std::println("same results: {}", sequential_out == parallel_out);

    // ---- 2. Not everything is worth it -------------------------------------------
    // Handing work to other threads has a fixed cost. For a small range the
    // cost is bigger than the work: 2,000 calls on 1,000 elements each.
    std::println("\n--- small ranges");
    std::vector<double> small_in(1'000, 2.0);
    std::vector<double> small_out(small_in.size());
    sequential_ms = milliseconds([&] {
        for (int repeat{0}; repeat < 2'000; ++repeat) {
            std::transform(small_in.begin(), small_in.end(), small_out.begin(), heavy);
        }
    });
    parallel_ms = milliseconds([&] {
        for (int repeat{0}; repeat < 2'000; ++repeat) {
            std::transform(std::execution::par, small_in.begin(), small_in.end(), small_out.begin(), heavy);
        }
    });
    report("2,000 x 1,000 doubles", sequential_ms, parallel_ms);

    std::vector<std::int32_t> numbers{make_numbers(10'000'000)};

    // ---- 3. reduce: the parallel accumulate ---------------------------------------
    // std::accumulate (15.7) has no policy and goes left to right. std::reduce
    // is allowed to add the elements IN ANY ORDER and grouping, so it can
    // split the range: the operation must be associative and commutative.
    std::println("\n--- reduce");
    std::int64_t sum_accumulate{0};
    std::int64_t sum_reduce{0};
    sequential_ms = milliseconds([&] {
        sum_accumulate = std::accumulate(numbers.begin(), numbers.end(), std::int64_t{0});
    });
    parallel_ms = milliseconds([&] {
        sum_reduce = std::reduce(std::execution::par, numbers.begin(), numbers.end(), std::int64_t{0});
    });
    report("sum of 10M ints", sequential_ms, parallel_ms);
    std::println("accumulate {}   reduce {}   equal: {}", sum_accumulate, sum_reduce, sum_accumulate == sum_reduce);

    // With integers the grouping cannot change the answer. With doubles it can,
    // because floating-point addition is not associative: the sums agree
    // to about 15 digits, and may differ in the last ones from run to run.
    double sum_of_doubles{std::reduce(std::execution::par, sequential_out.begin(), sequential_out.end(), 0.0)};
    double sum_in_order{std::accumulate(sequential_out.begin(), sequential_out.end(), 0.0)};
    std::println("doubles: agree to 6 digits: {}", std::abs(sum_of_doubles - sum_in_order) < 1e-6 * std::abs(sum_in_order));

    // ---- 4. sort ----------------------------------------------------------------------
    std::println("\n--- sort");
    std::vector<std::int32_t> to_sort_seq{numbers};
    std::vector<std::int32_t> to_sort_par{numbers};
    sequential_ms = milliseconds([&] {
        std::sort(to_sort_seq.begin(), to_sort_seq.end());
    });
    parallel_ms = milliseconds([&] {
        std::sort(std::execution::par, to_sort_par.begin(), to_sort_par.end());
    });
    report("sort of 10M ints", sequential_ms, parallel_ms);
    std::println("same order: {}   sorted: {}", to_sort_seq == to_sort_par, std::is_sorted(to_sort_par.begin(), to_sort_par.end()));

    // ---- 5. for_each and count_if ---------------------------------------------------------
    std::println("\n--- for_each and count_if");
    std::vector<double> celsius(input.size(), 20.0);
    parallel_ms = milliseconds([&] {
        std::for_each(std::execution::par, celsius.begin(), celsius.end(), [](double& value) { value = value * 9.0 / 5.0 + 32.0; });
    });
    std::println("[varies] for_each par: {:.1f} ms", parallel_ms);
    std::println("every value is now {}", celsius.front());

    auto even_count_seq{std::count_if(numbers.begin(), numbers.end(), [](std::int32_t value) { return value % 2 == 0; })};
    auto even_count_par{std::count_if(std::execution::par, numbers.begin(), numbers.end(), [](std::int32_t value) { return value % 2 == 0; })};
    std::println("even numbers: {} and {}", even_count_seq, even_count_par);

    // The rules of the road (see the notes):
    //   - the function you pass must not touch shared data without protection
    //     (19.4): a lambda that does ++counter on an outer variable is a data race
    //   - an exception that escapes the function calls std::terminate
    //   - the std::ranges:: algorithms have NO policy overloads: use the
    //     iterator-pair form (15.2) when you want a policy
    return 0;
}
