/*
    . An example showing error handling mechanisms in C++ side by side.
        . one without exceptions
        . one with exceptions
*/
module;

#include <fstream>
#include <filesystem>
#include <fmt/format.h>
#include <stdexcept>

export module exceptions_4;

namespace exceptions_4{

    namespace csv_no_except{

        export void write_csv(const std::filesystem::path& file_path) {
            // Create a CSV file with some data
            std::ofstream csv_file(file_path, std::ios::out);
            if (!csv_file) {
                fmt::println("Failed to create file: {}", file_path.string());
                return;
            }

            csv_file << "Name, Age, Occupation\n";
            csv_file << "Alice, 30, Engineer\n";
            csv_file << "Bob, 25, Designer\n";
            csv_file << "Charlie, 35, Teacher\n";

            csv_file.close();
            fmt::println("CSV file written successfully to: {}", file_path.string());
        }

        export void read_csv(const std::filesystem::path& file_path) {
            // Check if the file exists using std::filesystem
            if (!std::filesystem::exists(file_path)) {
                fmt::println("File does not exist: {}", file_path.string());
                return;
            }

            std::ifstream csv_file(file_path);
            if (!csv_file) {
                fmt::println("Failed to open file: {}", file_path.string());
                return;
            }

            std::string line;
            while (std::getline(csv_file, line)) {
                fmt::println("{}", line);
            }

            csv_file.close();
        }
        
    } // namespace csv_no_except

    namespace csv_with_except{

        export void write_csv(const std::filesystem::path& file_path) {
            // Create a CSV file with some data
            std::ofstream csv_file(file_path, std::ios::out);
            if (!csv_file) {
                throw std::runtime_error(fmt::format("Failed to create file: {}", file_path.string()));
            }

            csv_file << "Name, Age, Occupation\n";
            csv_file << "Alice, 30, Engineer\n";
            csv_file << "Bob, 25, Designer\n";
            csv_file << "Charlie, 35, Teacher\n";

            csv_file.close();
            fmt::println("CSV file written successfully to: {}", file_path.string());
        }

        export void read_csv(const std::filesystem::path& file_path) {
            // Check if the file exists using std::filesystem
            if (!std::filesystem::exists(file_path)) {
                throw std::runtime_error(fmt::format("File does not exist: {}", file_path.string()));
            }

            std::ifstream csv_file(file_path);
            if (!csv_file) {
                throw std::runtime_error(fmt::format("Failed to open file: {}", file_path.string()));
            }

            std::string line;
            while (std::getline(csv_file, line)) {
                fmt::println("{}", line);
            }

            csv_file.close();
        }
        
    } // namespace csv_with_except
    
    
} // namespace exceptions_4
