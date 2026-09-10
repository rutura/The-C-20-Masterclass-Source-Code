#include "report.h"

#include <algorithm>
#include <charconv>
#include <cmath>
#include <numeric>
#include <print>

// Shared analysis + reporting code. Identical in all three project
// versions. Uses: std::array, std::vector, std::string_view, <charconv>,
// enum class, std::optional, std::ranges::sort, <chrono>.

std::string_view category_name(Category c) {
    using enum Category;
    switch (c) {
        case Food:          return "Food";
        case Transport:     return "Transport";
        case Housing:       return "Housing";
        case Utilities:     return "Utilities";
        case Entertainment: return "Entertainment";
        case Other:         return "Other";
    }
    return "Other";
}

std::optional<Category> category_from_text(std::string_view text) {
    for (Category c : all_categories) {
        if (category_name(c) == text) {
            return c;
        }
    }
    return std::nullopt;
}

namespace {

// "2025-01-04" -> year_month_day, or nullopt.
std::optional<std::chrono::year_month_day> parse_date(std::string_view text) {
    // Expect exactly YYYY-MM-DD.
    if (text.size() != 10 || text[4] != '-' || text[7] != '-') {
        return std::nullopt;
    }

    int y{};
    int m{};
    int d{};
    auto ok = [](std::from_chars_result r, const char* end) {
        return r.ec == std::errc{} && r.ptr == end;
    };

    if (!ok(std::from_chars(text.data() + 0, text.data() + 4, y), text.data() + 4) ||
        !ok(std::from_chars(text.data() + 5, text.data() + 7, m), text.data() + 7) ||
        !ok(std::from_chars(text.data() + 8, text.data() + 10, d), text.data() + 10)) {
        return std::nullopt;
    }

    std::chrono::year_month_day date{
        std::chrono::year{y}, std::chrono::month{static_cast<unsigned>(m)},
        std::chrono::day{static_cast<unsigned>(d)}};

    return date.ok() ? std::optional{date} : std::nullopt;
}

std::optional<double> parse_amount(std::string_view text) {
    double value{};
    auto [ptr, ec]{std::from_chars(text.data(), text.data() + text.size(), value)};
    if (ec != std::errc{} || ptr != text.data() + text.size()) {
        return std::nullopt;
    }
    return value;
}

} // namespace

std::optional<Expense> make_expense(std::string_view date_text,
                                    std::string_view category_text,
                                    std::string_view amount_text,
                                    std::string_view note_text) {
    auto date{parse_date(date_text)};
    auto category{category_from_text(category_text)};
    auto amount{parse_amount(amount_text)};

    if (!date || !category || !amount) {
        return std::nullopt;
    }

    return Expense{*date, *category, *amount, std::string{note_text}};
}

std::optional<Expense> parse_expense_line(std::string_view line) {
    // Skip blank lines and the header row.
    if (line.empty() || line.starts_with("date,")) {
        return std::nullopt;
    }

    // Split on commas into up to 4 fields. We only need the first three
    // to be present; the note is optional.
    std::array<std::string_view, 4> fields{};
    std::size_t count{0};
    std::size_t start{0};
    while (count < fields.size()) {
        std::size_t comma{line.find(',', start)};
        if (comma == std::string_view::npos || count == fields.size() - 1) {
            fields[count++] = line.substr(start);
            break;
        }
        fields[count++] = line.substr(start, comma - start);
        start = comma + 1;
    }

    if (count < 3) {
        return std::nullopt;
    }

    return make_expense(fields[0], fields[1], fields[2],
                        count >= 4 ? fields[3] : std::string_view{});
}

std::vector<CategoryTotal> totals_by_category(const std::vector<Expense>& expenses) {
    // One running total per category, indexed by the enum's integer value.
    std::array<double, all_categories.size()> sums{};
    for (const Expense& e : expenses) {
        sums[static_cast<std::size_t>(e.category)] += e.amount;
    }

    std::vector<CategoryTotal> result{};
    for (Category c : all_categories) {
        double total{sums[static_cast<std::size_t>(c)]};
        if (total > 0.0) {
            result.push_back(CategoryTotal{c, total});
        }
    }

    // Biggest spender first.
    std::ranges::sort(result, [](const CategoryTotal& a, const CategoryTotal& b) {
        return a.total > b.total;
    });

    return result;
}

void print_bar_chart(const std::vector<CategoryTotal>& totals) {
    if (totals.empty()) {
        std::println("(no expenses)");
        return;
    }

    double grand{std::accumulate(
        totals.begin(), totals.end(), 0.0,
        [](double acc, const CategoryTotal& ct) { return acc + ct.total; })};

    double largest{totals.front().total};
    constexpr int bar_width{40};

    for (const CategoryTotal& ct : totals) {
        int bars{static_cast<int>(std::lround(ct.total / largest * bar_width))};
        std::string bar(static_cast<std::size_t>(bars), '#');
        std::println("{:>13} | {:<40} {:>9.2f}  ({:4.1f}%)",
                     category_name(ct.category), bar, ct.total,
                     ct.total / grand * 100.0);
    }
    std::println("{:>13} | {:<40} {:>9.2f}", "TOTAL", "", grand);
}
