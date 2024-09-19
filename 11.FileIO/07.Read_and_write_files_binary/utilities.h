#pragma once

#include <span>
#include <string>
#include <vector>

bool write_data(const std::string &filename, std::span<const unsigned char> data);
size_t read_data(const std::string &filename, std::vector<unsigned char> &buffer);