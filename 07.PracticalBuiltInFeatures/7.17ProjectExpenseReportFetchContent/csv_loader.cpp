#include "csv_loader.h"

#include <array>

#include <csv2/reader.hpp>

// csv2 does the tokenising: quoting, delimiters, trimming, the header
// row. We just walk rows and cells and hand the field text to
// make_expense() from report.h - the same builder the hand-rolled
// version ends up calling.

LoadResult load_expenses(const std::string& path) {
    LoadResult out{};

    csv2::Reader<csv2::delimiter<','>,
                 csv2::quote_character<'"'>,
                 csv2::first_row_is_header<true>,
                 csv2::trim_policy::trim_whitespace>
        reader{};

    // mmap maps the file into memory; false means it could not be opened.
    if (!reader.mmap(path)) {
        return out;                       // out.opened stays false
    }

    std::string cell_value{};
    for (const auto row : reader) {
        std::array<std::string, 4> fields{};   // date, category, amount, note
        std::size_t i{0};
        for (const auto cell : row) {
            if (i >= fields.size()) {
                break;
            }
            cell_value.clear();
            cell.read_value(cell_value);       // unescaped field text
            fields[i] = cell_value;
            ++i;
        }

        if (i == 0) {
            continue;                          // blank line
        }
        ++out.rows_seen;

        if (auto e{make_expense(fields[0], fields[1], fields[2], fields[3])}) {
            out.expenses.push_back(*e);
        } else {
            ++out.skipped;
        }
    }

    out.opened = true;
    return out;
}
