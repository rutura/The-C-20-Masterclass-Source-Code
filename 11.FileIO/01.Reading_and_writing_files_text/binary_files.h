#pragma once

#include <filesystem>
#include <vector>

namespace binary_files {
void write_file(const std::filesystem::path &file_path, const std::vector<char> &content);
std::vector<char> read_file(const std::filesystem::path &file_path);
}