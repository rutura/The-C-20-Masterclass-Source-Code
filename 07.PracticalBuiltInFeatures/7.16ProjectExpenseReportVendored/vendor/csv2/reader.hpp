
#pragma once
#include <cstring>
#if __has_include("sys/mman.h") || __has_include(<sys/mman.h>) || __has_include("windows.h") || __has_include(<windows.h>)
#define __CSV2_HAS_MMAN_H__ 1
#include <csv2/mio.hpp>
#endif
#include <csv2/parameters.hpp>
#include <istream>
#include <string>
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
	#include <string_view>
#endif

namespace csv2 {

template <class delimiter = delimiter<','>, class quote_character = quote_character<'"'>,
          class first_row_is_header = first_row_is_header<true>,
          class trim_policy = trim_policy::trim_whitespace>
class Reader {
  #if __CSV2_HAS_MMAN_H__
  mio::mmap_source mmap_;          // mmap source
  #endif
  const char *buffer_{nullptr};    // pointer to memory-mapped data
  size_t buffer_size_{0};          // mapped length of buffer
  size_t header_start_{0};         // start index of header (cache)
  size_t header_end_{0};           // end index of header (cache)

public:
  #if __CSV2_HAS_MMAN_H__
  // Use this if you'd like to mmap the CSV file
  template <typename StringType> bool mmap(StringType &&filename) {
    mmap_ = mio::mmap_source(filename);
    if (!mmap_.is_open() || !mmap_.is_mapped())
      return false;
    buffer_ = mmap_.data();
    buffer_size_ = mmap_.mapped_length();
    return true;
  }
  #endif

  // Use this if you have the CSV contents
  // in an std::string already
  template <typename StringType> bool parse(StringType &&contents) {
    buffer_ = std::forward<StringType>(contents).c_str();
    buffer_size_ = contents.size();
    return buffer_size_ > 0;
  }


  // Use this if you already have the CSV contents
  // in a std::string_view 
#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
  bool parse_view(std::string_view sv) {
    buffer_ = sv.data();
    buffer_size_ = sv.size();
    return buffer_size_ > 0;
  }
#endif


  class RowIterator;
  class Row;
  class CellIterator;

  class Cell {
    const char *buffer_{nullptr}; // Pointer to memory-mapped buffer
    size_t start_{0};             // Start index of cell content
    size_t end_{0};               // End index of cell content
    bool escaped_{false};         // Does the cell have escaped content?
    friend class Row;
    friend class CellIterator;

  public:
  
	// returns a view on the cell's contents if C++17 available
	#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 201703L) || __cplusplus >= 201703L)
      std::string_view read_view() const {
      const auto new_start_end = trim_policy::trim(buffer_, start_, end_);
      return std::string_view(buffer_ + new_start_end.first, new_start_end.second- new_start_end.first);
      }
	#endif
    // Returns the raw_value of the cell without handling escaped
    // content, e.g., cell containing """foo""" will be returned
    // as is
    template <typename Container> void read_raw_value(Container &result) const {
      if (start_ >= end_)
        return;
      result.reserve(end_ - start_);
      for (size_t i = start_; i < end_; ++i)
        result.push_back(buffer_[i]);
    }

    // If cell is escaped, convert and return correct cell contents,
    // e.g., """foo""" => ""foo""
    template <typename Container> void read_value(Container &result) const {
      if (start_ >= end_)
        return;
      result.reserve(end_ - start_);
      const auto new_start_end = trim_policy::trim(buffer_, start_, end_);
      for (size_t i = new_start_end.first; i < new_start_end.second; ++i)
        result.push_back(buffer_[i]);
      for (size_t i = 1; i < result.size(); ++i) {
        if (result[i] == quote_character::value && result[i - 1] == quote_character::value) {
          result.erase(i - 1, 1);
        }
      }
    }
  };

  class Row {
    const char *buffer_{nullptr}; // Pointer to memory-mapped buffer
    size_t start_{0};             // Start index of row content
    size_t end_{0};               // End index of row content
    friend class RowIterator;
    friend class Reader;

  public:
    // address of row
    const char *address() const { return buffer_; }
	// returns the char length of the row
	size_t length() const { return end_ - start_; }

    // Returns the raw_value of the row
    template <typename Container> void read_raw_value(Container &result) const {
      if (start_ >= end_)
        return;
      result.reserve(end_ - start_);
      for (size_t i = start_; i < end_; ++i)
        result.push_back(buffer_[i]);
    }

    class CellIterator {
      friend class Row;
      const char *buffer_;
      size_t buffer_size_;
      size_t start_;
      size_t current_;
      size_t end_;

    public:
      CellIterator(const char *buffer, size_t buffer_size, size_t start, size_t end)
          : buffer_(buffer), buffer_size_(buffer_size), start_(start), current_(start_), end_(end) {
      }

      CellIterator &operator++() {
        current_ += 1;
        return *this;
      }

      Cell operator*() {
        bool escaped{false};
        class Cell cell;
        cell.buffer_ = buffer_;
        cell.start_ = current_;
        cell.end_ = end_;

        size_t last_quote_location = 0;
        bool quote_opened = false;
        for (auto i = current_; i < end_; i++) {
          current_ = i;
          if (buffer_[i] == delimiter::value && !quote_opened) {
            // actual delimiter
            // end of cell
            cell.end_ = current_;
            cell.escaped_ = escaped;
            return cell;
          } else {
            if (buffer_[i] == quote_character::value) {
              if (!quote_opened) {
                // first quote for this cell
                quote_opened = true;
                last_quote_location = i;
              } else {
                escaped = (last_quote_location == i - 1);
                last_quote_location += (i - last_quote_location) * size_t(!escaped);
                quote_opened = escaped || (buffer_[i + 1] != delimiter::value);
              }
            }
          }
        }
        cell.end_ = current_ + 1;
        return cell;
      }

      bool operator!=(const CellIterator &rhs) { return current_ != rhs.current_; }
    };

    CellIterator begin() const { return CellIterator(buffer_, end_ - start_, start_, end_); }
    CellIterator end() const { return CellIterator(buffer_, end_ - start_, end_, end_); }
  };

  class RowIterator {
    friend class Reader;
    const char *buffer_;
    size_t buffer_size_;
    size_t start_;
    size_t end_;

  public:
    RowIterator(const char *buffer, size_t buffer_size, size_t start)
        : buffer_(buffer), buffer_size_(buffer_size), start_(start), end_(start_) {}

    RowIterator &operator++() {
      start_ = end_ + 1;
      end_ = start_;
      return *this;
    }

    Row operator*() {
      Row result;
      result.buffer_ = buffer_;
      result.start_ = start_;
      result.end_ = end_;

      if (const char *ptr =
              static_cast<const char *>(memchr(&buffer_[start_], '\n', (buffer_size_ - start_)))) {
        end_ = start_ + (ptr - &buffer_[start_]);
        result.end_ = end_;
        start_ = end_ + 1;
      } else {
        // last row
        end_ = buffer_size_;
        result.end_ = end_;
      }
      return result;
    }

    bool operator!=(const RowIterator &rhs) { return start_ != rhs.start_; }
  };

  RowIterator begin() const {
    if (buffer_size_ == 0)
      return end();
    if (first_row_is_header::value) {
      const auto header_indices = header_indices_();
      return RowIterator(buffer_, buffer_size_, header_indices.second  > 0 ? header_indices.second + 1 : 0);
    } else {
      return RowIterator(buffer_, buffer_size_, 0);
    }
  }

  RowIterator end() const { return RowIterator(buffer_, buffer_size_, buffer_size_ + 1); }

private:
  std::pair<size_t, size_t> header_indices_() const {
    size_t start = 0, end = 0;

    if (const char *ptr =
            static_cast<const char *>(memchr(&buffer_[start], '\n', (buffer_size_ - start)))) {
      end = start + (ptr - &buffer_[start]);
    }
    return {start, end};
  }

public:

  Row header() const {
    size_t start = 0, end = 0;
    Row result;
    result.buffer_ = buffer_;
    result.start_ = start;
    result.end_ = end;

    if (const char *ptr =
            static_cast<const char *>(memchr(&buffer_[start], '\n', (buffer_size_ - start)))) {
      end = start + (ptr - &buffer_[start]);
      result.end_ = end;
    }
    return result;
  }

  /**
   * @returns The number of rows (excluding the header)
  */
  size_t rows(bool ignore_empty_lines = false) const {
    size_t result{0};
    if (!buffer_ || buffer_size_ == 0)
      return result;
    
    // Count the first row if not header
    if (not first_row_is_header::value
        and (not ignore_empty_lines
        or *(static_cast<const char*>(buffer_)) != '\r'))
      ++result;

    for (const char *p = buffer_
        ; (p = static_cast<const char *>(memchr(p, '\n', (buffer_ + buffer_size_) - p)))
        ; ++p) {
      if (ignore_empty_lines
          and (p >= buffer_ + buffer_size_ - 1
          or *(p + 1) == '\r'))
        continue;
      ++result;
    }
    return result;
  }

  size_t cols() const {
    size_t result{0};
    for (const auto cell : header())
      result += 1;
    return result;
  }
};
} // namespace csv2
