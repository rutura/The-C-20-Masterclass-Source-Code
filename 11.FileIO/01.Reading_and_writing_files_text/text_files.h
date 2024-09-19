#pragma once

#include <string_view>
#include <iostream>
#include <filesystem>

namespace text_files {
void write_file(const std::filesystem::path &file_path, const std::string &content);
void read_file(const std::filesystem::path &file_path);
}