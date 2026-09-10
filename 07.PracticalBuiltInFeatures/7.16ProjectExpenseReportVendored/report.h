#pragma once

#include <array>
#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

// The chapter project: read a CSV of expenses, total them by category,
// and print a bar chart - timing each phase.
//
// This header is the part that DOES NOT change between the three
// versions of the project. Only how the CSV file becomes a
// std::vector<Expense> differs (hand-rolled here, the csv2 library in
// 7.16 and 7.17). Everything below is plain chapter-7 material.

// The fixed set of spending categories. enum class: scoped names, no
// accidental int conversions, one byte of storage.
enum class Category : std::uint8_t {
    Food,
    Transport,
    Housing,
    Utilities,
    Entertainment,
    Other,
};

// Every Category, in order - handy for iterating and for indexing a
// fixed-size std::array of totals.
inline constexpr std::array<Category, 6> all_categories{
    Category::Food, Category::Transport, Category::Housing,
    Category::Utilities, Category::Entertainment, Category::Other,
};

std::string_view category_name(Category c);

// Text -> Category. Returns nullopt if the text matches no category.
std::optional<Category> category_from_text(std::string_view text);

// One row of the file.
struct Expense {
    std::chrono::year_month_day date{};
    Category category{Category::Other};
    double amount{0.0};
    std::string note{};
};

// Parse one CSV line ("2025-01-04,Food,42.50,groceries") into an Expense.
// Returns nullopt if the line is blank, a header, or malformed.
std::optional<Expense> parse_expense_line(std::string_view line);

// Build an Expense from four already-split fields. Used by the csv2-based
// loaders (7.16 / 7.17), which let the library do the splitting.
// Returns nullopt if any of date / category / amount is malformed.
std::optional<Expense> make_expense(std::string_view date_text,
                                    std::string_view category_text,
                                    std::string_view amount_text,
                                    std::string_view note_text);

// A category and its summed amount, for reporting.
struct CategoryTotal {
    Category category{};
    double total{0.0};
};

// Sum the expenses by category, largest total first.
std::vector<CategoryTotal> totals_by_category(const std::vector<Expense>& expenses);

// Print the totals as a simple text bar chart.
void print_bar_chart(const std::vector<CategoryTotal>& totals);
