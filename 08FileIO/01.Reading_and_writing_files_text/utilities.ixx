module;
#include <filesystem>
#include <fmt/format.h>



export module utilities; 

import text_files;
import binary_files;

export void read_write_text_files(){
    std::filesystem::path file_path = R"(D:\sample_file.txt)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.txt)"; // Linux

    std::string content = "\nHello, world!\nThis is a test.";

    // Write content to the file
    text_files::write_file(file_path, content);
    
    // Read content back from the file and print it
    //fmt::println("Content read from the file:");
    text_files::read_file(file_path);	
}

export void read_write_binary_files(){
    // Define file path
	std::filesystem::path file_path = R"(D:\sample_file.bin)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.bin)"; // Linux

    // Example content to write (binary data)
    std::vector<char> content = {'H', 'e', 'l', 'l', 'o', ' ', 'B', 'i', 'n', 'a', 'r', 'y', '!'};

    // Write binary data to file
    binary_files::write_file(file_path, content);

    // Read binary data from file
    std::vector<char> read_content = binary_files::read_file(file_path);

    // Display the read content as text
    if (!read_content.empty()) {
        fmt::print("Read content: {}\n", std::string(read_content.begin(), read_content.end()));
    } else {
        fmt::print("No content read from file.\n");
    }	
}
