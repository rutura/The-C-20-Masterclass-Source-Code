module;

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <fmt/core.h>

export module binary_files;

namespace binary_files{


    // Function to write binary data to a file
    export void write_file(const std::filesystem::path& file_path, const std::vector<char>& content) {
        std::ofstream file(file_path, std::ios::out | std::ios::binary); // Binary mode
        if (!file.is_open()) {
            fmt::print("Failed to open file for writing: {}\n", file_path.filename().string());
            return;
        }

        // Write the entire content to the file as binary
        // Knowing the size of the binary data is important.
        file.write(content.data(), content.size());
    }

    // Function to read binary data from a file
    export std::vector<char> read_file(const std::filesystem::path& file_path) {
        std::ifstream file(file_path, std::ios::in | std::ios::binary); // Binary mode
        if (!file.is_open()) {
            fmt::print("Failed to open file for reading: {}\n", file_path.filename().string());
            return {};
        }

        // Get the file size by seeking to the end
        //file.seekg(0, std::ios::end);
        //std::streamsize size = file.tellg();
        //file.seekg(0, std::ios::beg);

        //Get the size of the file using std::filesystem::file_size
        std::streamsize size = std::filesystem::file_size(file_path);

        // Allocate a buffer and read the file into it
        std::vector<char> buffer(size);
        if (file.read(buffer.data(), size)) {
            return buffer;
        }

        return {};
    }

}




