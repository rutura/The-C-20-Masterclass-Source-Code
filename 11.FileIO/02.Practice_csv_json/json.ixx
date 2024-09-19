module;

#include <fstream>
#include <filesystem>
#include <fmt/format.h>

export module json;

namespace json{

    export void write_json(const std::filesystem::path& file_path) {
        // Create a JSON file with some data
        std::ofstream json_file(file_path, std::ios::out);
        if (!json_file) {
            fmt::println("Failed to create file: {}", file_path.string());
            return;
        }

        // Simple JSON-like format (not using a library)
        // For simplicity, I'll use a minimal JSON-like structure, as C++ doesn't have built-in JSON handling. In real-world projects, you'd typically use libraries like nlohmann/json. However, this example focuses on the writing and reading process using the standard library.
        json_file << "{\n";
        json_file << "  \"name\": \"Alice\",\n";
        json_file << "  \"age\": 30,\n";
        json_file << "  \"occupation\": \"Engineer\"\n";
        json_file << "}\n";

        json_file.close();
        fmt::println("JSON file written successfully to: {}", file_path.string());
    }

    export void read_json(const std::filesystem::path& file_path) {
        // Check if the file exists using std::filesystem
        if (!std::filesystem::exists(file_path)) {
            fmt::println("File does not exist: {}", file_path.string());
            return;
        }

        std::ifstream json_file(file_path);
        if (!json_file) {
            fmt::println("Failed to open file: {}", file_path.string());
            return;
        }

        std::string line;
        while (std::getline(json_file, line)) {
            fmt::println("{}", line);
        }

        json_file.close();
    }
    
} // namespace json