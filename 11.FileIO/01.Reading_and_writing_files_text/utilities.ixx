module;
#include <filesystem>
#include <fmt/format.h>



export module utilities; 

import text_files;
import binary_files;
import pod_types;
import non_pod_types;

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


export void read_write_pod_types(){

    // Define file path
    std::filesystem::path file_path = R"(D:\sample_pod_file.bin)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.bin)"; // Linux

    // Create a PODType object
    pod_types::PODType pod = {42, 3.14159};

    // Write the PODType object to a binary file
    if (pod_types::write_pod(file_path, pod)) {
        fmt::print("PODType object written to file.\n");
    } else {
        fmt::print("Failed to write PODType object to file.\n");
    }

    // Read the PODType object from the binary file
    pod_types::PODType read_pod;
    if (pod_types::read_pod(file_path, read_pod)) {
        fmt::print("PODType object read from file: id={}, value={}\n", read_pod.id, read_pod.value);
    } else {
        fmt::print("Failed to read PODType object from file.\n");
    }

}

export void write_and_read_several_pod_types(){
    
    // Define file path
    std::filesystem::path file_path = R"(D:\sample_pod_vector.bin)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.bin)"; // Linux

    // Create a vector of PODType objects
    std::vector<pod_types::PODType> pod_vector = {
        {1, 1.1},
        {2, 2.2},
        {3, 3.3},
        {4, 4.4},
        {5, 5.5}
    };

    // Write the vector of PODType objects to a binary file
    if (pod_types::write_pod_vector(file_path, pod_vector)) {
        fmt::print("PODType objects written to file.\n");
    } else {
        fmt::print("Failed to write PODType objects to file.\n");
    }

    // Read the vector of PODType objects from the binary file
    std::vector<pod_types::PODType> read_pod_vector;
    if (pod_types::read_pod_vector(file_path, read_pod_vector)) {
        fmt::print("PODType objects read from file:\n");
        for (const auto& pod : read_pod_vector) {
            fmt::print("id={}, value={}\n", pod.id, pod.value);
        }
    } else {
        fmt::print("Failed to read PODType objects from file.\n");
    }
}

export void write_read_several_non_pod_types(){

    std::vector<non_pod_types::Person> persons = {{"Alice", 30}, {"Bob", 25}, {"Charlie", 40}};
    std::filesystem::path file_path = R"(D:\sample_non_pod_vector.bin)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.bin)"; // Linux


    // Serialize the vector of person objects
    non_pod_types::write_persons_to_file(persons, file_path);

    // Deserialize the vector of person objects
    std::vector<non_pod_types::Person> loaded_persons = non_pod_types::read_persons_from_file(file_path);

    // Print the loaded data
    for (const auto& p : loaded_persons) {
        fmt::println("Name: {}, Age: {}", p.name, p.age);
    }
}