#pragma once

#include <charconv>
#include <cstddef>
#include <optional>
#include <string_view>
#include <system_error>

// One parsed line of the log. The text fields are string_views (7.9) that
// point INTO the buffer the file was read into, so no line is copied. The
// price: the buffer must outlive every LogEntry. main() keeps it alive.
struct LogEntry {
    std::string_view client;
    std::string_view method;
    std::string_view path;
    int hour;
    int status;
    std::size_t bytes;
};

namespace detail {

// Reads an integer from the whole of `text`. Returns false if it is not one.
template <typename Integer>
bool to_number(std::string_view text, Integer& value) {
    auto result{std::from_chars(text.data(), text.data() + text.size(), value)};
    return result.ec == std::errc{} && result.ptr == text.data() + text.size();
}

}  // namespace detail

// 203.0.113.7 - - [01/Mar/2026:13:55:36 +0000] "GET /index.html HTTP/1.1" 200 2326
//
// A damaged line is not an error to stop for: it is a normal outcome of
// reading real logs, so the result is a std::optional (13.2).
inline std::optional<LogEntry> parse_line(std::string_view line) {
    LogEntry entry{};

    auto space{line.find(' ')};
    auto open_bracket{line.find('[')};
    auto close_bracket{line.find(']')};
    if (space == std::string_view::npos || open_bracket == std::string_view::npos ||
        close_bracket == std::string_view::npos || close_bracket < open_bracket + 15) {
        return std::nullopt;
    }
    entry.client = line.substr(0, space);

    // "01/Mar/2026:13:55:36 +0000": the hour sits in characters 12 and 13.
    std::string_view stamp{line.substr(open_bracket + 1, close_bracket - open_bracket - 1)};
    if (!detail::to_number(stamp.substr(12, 2), entry.hour)) {
        return std::nullopt;
    }

    // "GET /index.html HTTP/1.1" between the quotes.
    auto quote_open{line.find('"', close_bracket)};
    auto quote_close{quote_open == std::string_view::npos ? quote_open : line.find('"', quote_open + 1)};
    if (quote_close == std::string_view::npos) {
        return std::nullopt;
    }
    std::string_view request{line.substr(quote_open + 1, quote_close - quote_open - 1)};
    auto first_space{request.find(' ')};
    auto second_space{request.rfind(' ')};
    if (first_space == std::string_view::npos || second_space == first_space) {
        return std::nullopt;
    }
    entry.method = request.substr(0, first_space);
    entry.path = request.substr(first_space + 1, second_space - first_space - 1);

    // After the closing quote: " 200 2326". A dash means "no body".
    std::string_view rest{line.substr(quote_close + 2)};
    auto split{rest.find(' ')};
    if (split == std::string_view::npos || !detail::to_number(rest.substr(0, split), entry.status)) {
        return std::nullopt;
    }
    std::string_view bytes{rest.substr(split + 1)};
    if (bytes == "-") {
        entry.bytes = 0;
    } else if (!detail::to_number(bytes, entry.bytes)) {
        return std::nullopt;
    }
    return entry;
}
