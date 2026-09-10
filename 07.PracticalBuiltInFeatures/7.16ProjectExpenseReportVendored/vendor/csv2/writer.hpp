
#pragma once
#include <cstring>
#include <csv2/parameters.hpp>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>

namespace csv2 {

template <class delimiter = delimiter<','>, typename Stream = std::ofstream> class Writer {
  Stream &stream_; // output stream for the writer
public:
  Writer(Stream &stream) : stream_(stream) {}

  ~Writer() {
    stream_.close();
  }

  template <typename Container> void write_row(Container &&row) {
    const auto &strings = std::forward<Container>(row);
    const auto delimiter_string = std::string(1, delimiter::value);
    std::copy(strings.begin(), strings.end() - 1,
              std::ostream_iterator<std::string>(stream_, delimiter_string.c_str()));
    stream_ << strings.back() << "\n";
  }

  template <typename Container> void write_rows(Container &&rows) {
    const auto &container_of_rows = std::forward<Container>(rows);
    for (const auto &row : container_of_rows) {
      write_row(row);
    }
  }
};

} // namespace csv2
