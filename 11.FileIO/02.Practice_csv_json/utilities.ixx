module;

#include <fmt/format.h>
#include <filesystem>

export module utilities; 

import csv;
import json;

export void csv_demo(){

	std::filesystem::path file_path = R"(D:\sample_file.csv)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/sample_file.csv)"; // Linux

    // Write CSV data
    csv::write_csv(file_path);

    // Read and display the CSV data
    csv::read_csv(file_path);

}

export void json_demo(){

	std::filesystem::path file_path = R"(D:\sample_file.json)"; // Windows
	//std::filesystem::path file_path = R"(/path/to/your/sample_file.json)"; // Linux

	// Write JSON data
	json::write_json(file_path);

	// Read and display the JSON data
	json::read_json(file_path);

}
