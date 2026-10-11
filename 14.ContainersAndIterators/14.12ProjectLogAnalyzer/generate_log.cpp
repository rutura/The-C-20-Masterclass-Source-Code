#include <algorithm>
#include <array>
#include <charconv>
#include <cstddef>
#include <cstdint>
#include <format>
#include <fstream>
#include <print>
#include <random>
#include <string>
#include <string_view>
#include <vector>

// Writes a made-up web server log in the Common Log Format, one request per line:
//
//   203.0.113.7 - - [01/Mar/2026:13:55:36 +0000] "GET /index.html HTTP/1.1" 200 2326
//
// The data is invented but not uniform: a few pages, clients and hours are far
// busier than the rest, as in a real log. The generator is deterministic. The
// same seed gives the same file on every machine, so everyone sees the same
// numbers in the analyzer. (std::mt19937 is specified exactly by the standard;
// the std:: distributions are not, so the helpers below use plain arithmetic.)
//
// Usage:  rooster_generate [lines] [output file]      default: 100000 access.log

namespace {

std::mt19937 engine{2026};

// A number in [0, 1) with 24 bits of randomness.
double unit() {
    return static_cast<double>(engine() >> 8) / 16'777'216.0;
}

// An index in [0, size), skewed towards 0: power 1 is uniform, higher is more skewed.
std::size_t skewed_index(std::size_t size, int power) {
    double u{unit()};
    double scaled{u};
    for (int i{1}; i < power; ++i) {
        scaled *= u;
    }
    return static_cast<std::size_t>(scaled * static_cast<double>(size));
}

std::size_t uniform(std::size_t size) {
    return static_cast<std::size_t>(unit() * static_cast<double>(size));
}

const std::array<std::string_view, 24> pages{
    "/", "/index.html", "/products", "/products/widget", "/products/gadget", "/cart", "/checkout",
    "/login", "/logout", "/about", "/contact", "/blog", "/blog/2026/01/launch", "/blog/2026/02/update",
    "/static/app.js", "/static/style.css", "/static/logo.png", "/api/items", "/api/items/42",
    "/api/status", "/search", "/help", "/faq", "/downloads/manual.pdf"};

// Links that do not exist, which produce 404 responses.
const std::array<std::string_view, 5> missing{
    "/old-page", "/wp-login.php", "/products/discontinued", "/admin", "/favicon.old.ico"};

std::string client_address(std::size_t index) {
    static constexpr std::array<std::string_view, 3> networks{"203.0.113", "198.51.100", "192.0.2"};
    return std::format("{}.{}", networks[index % 3], 1 + (index / 3) % 100);
}

std::size_t body_size(std::string_view path) {
    auto ends_with{[&](std::string_view suffix) { return path.ends_with(suffix); }};
    if (ends_with(".js")) {
        return 40'000 + uniform(60'000);
    }
    if (ends_with(".css")) {
        return 10'000 + uniform(20'000);
    }
    if (ends_with(".png")) {
        return 20'000 + uniform(180'000);
    }
    if (ends_with(".pdf")) {
        return 500'000 + uniform(1'500'000);
    }
    if (path.starts_with("/api")) {
        return 200 + uniform(4'800);
    }
    return 2'000 + uniform(28'000);
}

}  // namespace

int main(int argc, char** argv) {
    std::size_t lines{100'000};
    std::string output{"access.log"};
    if (argc > 1) {
        std::string_view text{argv[1]};
        std::from_chars(text.data(), text.data() + text.size(), lines);
    }
    if (argc > 2) {
        output = argv[2];
    }

    // Seconds into the day, bell shaped around midday (the average of two
    // uniform numbers), then sorted: a log is written in time order.
    std::vector<std::uint32_t> seconds;
    seconds.reserve(lines);
    for (std::size_t i{0}; i < lines; ++i) {
        // Two separate statements: the order in which the operands of + are
        // evaluated is unspecified, and the file must be identical everywhere.
        double first{unit()};
        double second{unit()};
        seconds.push_back(static_cast<std::uint32_t>((first + second) / 2.0 * 86'400.0));
    }
    std::ranges::sort(seconds);

    // Binary mode: on Windows text mode would turn every \n into \r\n, and the
    // file would no longer be identical on every platform.
    std::ofstream file{output, std::ios::binary};
    if (!file) {
        std::println("cannot write {}", output);
        return 1;
    }

    for (std::uint32_t time_of_day : seconds) {
        std::string client{client_address(skewed_index(300, 3))};     // some clients are far busier
        std::string_view method{"GET"};
        std::size_t roll{uniform(100)};
        if (roll >= 98) {
            method = "HEAD";
        } else if (roll >= 90) {
            method = "POST";
        }

        std::string_view path{};
        int status{200};
        std::string bytes;
        if (uniform(100) < 4) {                                       // 4 percent of requests hit a missing link
            path = missing[skewed_index(missing.size(), 2)];
            status = 404;
            bytes = std::to_string(150 + uniform(100));
        } else {
            path = pages[skewed_index(pages.size(), 2)];              // some pages are far busier
            std::size_t kind{uniform(1000)};
            if (kind < 900) {
                status = 200;
            } else if (kind < 965) {
                status = 304;
            } else if (kind < 990) {
                status = 301;
            } else {
                status = 500;
            }
            bytes = (status == 304) ? "-" : std::to_string(status == 301 ? 0 : body_size(path));
        }

        // About 1 line in 500 is damaged, the way real logs are.
        if (uniform(500) == 0) {
            file << "-- truncated line --\n";
            continue;
        }

        file << std::format("{} - - [01/Mar/2026:{:02}:{:02}:{:02} +0000] \"{} {} HTTP/1.1\" {} {}\n",
                            client, time_of_day / 3600, time_of_day / 60 % 60, time_of_day % 60,
                            method, path, status, bytes);
    }

    std::println("wrote {} lines to {}", lines, output);
    return 0;
}
