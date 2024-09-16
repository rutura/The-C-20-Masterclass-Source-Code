module;

#include <string_view>
//#include <iostream>
#include <fmt/format.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <functional>
#include <span>
#include <cassert>
#include <memory>

//Global module fragment : #include , preprocessor directives
export module utilities; // Name doesn't have to match the .ixx file

// Function to write binary data to a file
export bool write_data(const std::string& filename, std::span<const unsigned char> data) {
	std::ofstream ofile(filename, std::ios::binary);
	
	// Check if the file opened successfully
	if (!ofile.is_open()) {
		fmt::println("Failed to open file for writing.");
		return false;
	}
	
	// Perform the write and check if it succeeded
	ofile.write(reinterpret_cast<const char*>(data.data()), data.size_bytes());
	if (ofile.fail()) {
		fmt::println("Failed to write data to file.");
		return false;
	}

	ofile.close();
	return true;
}

// Function to read binary data from a file
export size_t read_data(const std::string& filename, std::vector<unsigned char>& buffer) {
	std::ifstream ifile(filename, std::ios::ate | std::ios::binary);

	// Check if the file opened successfully
	if (!ifile.is_open()) {
		fmt::println("Failed to open file for reading.");
		return 0;
	}

	// Get the file size
	size_t length = static_cast<size_t>(ifile.tellg());
	ifile.seekg(0, std::ios_base::beg);

	// Resize the buffer to the file size
	buffer.resize(length);

	// Perform the read and check if it succeeded
	ifile.read(reinterpret_cast<char*>(buffer.data()), length);
	if (ifile.fail()) {
		fmt::println("Failed to read data from file.");
		return 0;
	}

	size_t readbytes = static_cast<size_t>(ifile.gcount());
	ifile.close();

	return readbytes;
}