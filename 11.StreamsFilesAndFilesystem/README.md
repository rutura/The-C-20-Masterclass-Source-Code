# Chapter 11: Streams, Files & Filesystem

## Why this chapter exists

You've been using streams since chapter 3 - `std::cin >>` reads from one,
`std::print`/`std::println` write to another - and the chapter 4 capstone
(`4.9ExpenseTrackerProject`) already opens an `std::ofstream`/`std::ifstream`
to save and reload a ledger between runs. But "here's a line that happens to
work" isn't the same as understanding what a stream actually is, what else
it can point at besides the console, or how to work with a file that's more
structured than one line of two numbers. This chapter is where that becomes
explicit: manipulators, string streams, file reading/writing on their own
terms, seeking around inside a file, `<filesystem>`, and a real end-to-end
case study - closing on `<chrono>`, another kind of data a program persists
alongside file contents.

## What a program like this actually needs

| Need | Example | C++ tool |
|---|---|---|
| Control console output without `std::format` | pad a number to a fixed width in older-style code | `<iomanip>` manipulators (`std::setw`, `std::setprecision`, `std::boolalpha`) |
| Build or take apart a string using stream syntax | parsing `"Groceries,62.75,yes"` into three fields | `std::istringstream` / `std::ostringstream` |
| Save data between runs | the expense tracker's ledger file | `std::ofstream` |
| Load data back on the next run | the expense tracker reading its ledger on startup | `std::ifstream`, `std::getline` |
| Jump to a specific record without reading everything before it | overwriting one fixed-width record in place | `seekg`/`seekp`/`tellg`/`tellp` |
| Ask questions about paths and folders | does this file exist, what's in this directory | `std::filesystem` |
| Parse a real, multi-row data file | a CSV of student scores | `std::ifstream` + `std::istringstream`, together |
| Track a calendar date alongside other data | "which semester was this" | `<chrono>` (`year_month_day`, `std::format`'s chrono specifiers) |

## Lecture by lecture

- **12.2 Streams Recap & Manipulators** - what a stream is, framed against
  the `std::print`/`std::cin` you've already been using; the older
  `<iomanip>` manipulator style (`std::setw`, `std::setprecision`,
  `std::boolalpha`, `std::hex`) you'll still see in existing code, contrasted
  with chapter 5's `std::format` mini-language.
- **12.3 String Streams** - `std::ostringstream` to build a string piece by
  piece, `std::istringstream` to pull one apart into typed fields - the same
  `>>`/`getline` idioms you already know, just pointed at a string instead of
  the console.
- **12.4 Writing File Streams** - `std::ofstream`, explicitly narrated
  against the expense tracker's own ledger-writing line; truncate vs.
  `std::ios::app` append mode.
- **12.5 Reading File Streams** - `std::ifstream`, narrated against the
  expense tracker's ledger-loading code; `>>` extraction for known,
  fixed-order values vs. `std::getline` for line-oriented, variable-length
  content.
- **12.6 Seek and Tell** - `seekg`/`seekp`/`tellg`/`tellp` against
  fixed-width records, jumping straight to (and overwriting) one record
  without touching the rest of the file.
- **12.7 Filesystem Basics** - `std::filesystem::path`, `exists`,
  `is_directory`/`is_regular_file`, `create_directories`, and
  `directory_iterator` to list a folder's contents.
- **12.8 CSV Case Study** - parsing `students.csv` (name, course, score,
  semester) end to end using everything so far - `ifstream` + `getline` +
  `istringstream` together - then aggregating an average score per course.
- **12.9 Chrono Date & Time** - `std::chrono::system_clock::now()`,
  `year_month_day` as a calendar date (not a time_point), and formatting a
  date with `std::format`'s chrono specifiers.

## How C++'s latest features help

- **`<filesystem>`** (C++17) replaces OS-specific path-handling calls with
  one portable API - `exists`, `is_directory`, `directory_iterator`, and
  `path`'s own `operator/` for joining path segments safely.
- **`<chrono>`'s calendar types** (C++20) - `year_month_day`, `std::chrono::day`,
  `std::chrono::month` - give a date its own strong types instead of three
  easily-swapped `int`s, and `std::format` understands them directly (no
  separate date-formatting library needed).
- **`std::format`'s mini-language covers dates too** - `{:%Y-%m-%d}` and
  `{:%B %d, %Y}` are the exact same `{}` syntax from chapter 5, now formatting
  a `year_month_day` instead of a number.

## Building the code

Every lecture folder has its own `CMakeLists.txt`, same as the rest of the
course. If you don't have a C++23 compiler installed locally, use one of the
ready-made Docker images in [`../docker`](../docker) - see that folder's
README for exact commands.

Lectures that read a file expect to be run from their own lecture folder
(e.g. `12.8CsvCaseStudy`'s `students.csv` sits right next to its `main.cpp`) -
the same working-directory assumption `4.9ExpenseTrackerProject` documents.
