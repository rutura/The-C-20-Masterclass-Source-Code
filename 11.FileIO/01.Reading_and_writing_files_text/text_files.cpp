#include "text_files.h"

#include <fmt/format.h>
#include <fstream>
#include <string>

/*

//Other ways we could have writen to the file

// Way #1: 
	#include <fstream>
	#include <string>

	int main() {
		std::ofstream file("example.txt", std::ios::out | std::ios::binary);
		std::string content = "Hello, world!";
		file.write(content.c_str(), content.size());
		file.close();
		return 0;
	}

// Way #2:
	#include <cstdio>
	#include <string>

	int main() {
		FILE* file = fopen("example.txt", "w");
		if (file) {
			std::string content = "Hello, world!";
			fprintf(file, "%s", content.c_str());
			fclose(file);
		} else {
			std::cerr << "Unable to open file";
		}
		return 0;
	}

// Way #3:
	#include <cstdio>
	#include <string>

	int main() {
		FILE* file = fopen("example.txt", "wb");
		if (file) {
			std::string content = "Hello, world!";
			fwrite(content.c_str(), sizeof(char), content.size(), file);
			fclose(file);
		} else {
			std::cerr << "Unable to open file";
		}
		return 0;
	}

//Way #4:
	#include <fstream>
	#include <iterator>
	#include <string>

	int main() {
		std::ofstream file("example.txt");
		std::string content = "Hello, world!";
		std::copy(content.begin(), content.end(), std::ostream_iterator<char>(file));
		file.close();
		return 0;
	}


These methods provide different ways to write data to a file, each with its own use cases and advantages. The choice of method depends on the specific requirements of your application, such as whether you need to write text or binary data, or whether you prefer using C++ standard library features or C standard library functions.

*/

namespace text_files {
void write_file(const std::filesystem::path &file_path, const std::string &content)
{

  //Open the file for writing and in append mode
  //Creating the stream object attempts to open the file
  std::ofstream file(file_path, std::ios::out | std::ios::app);
  if (!file.is_open()) {
    fmt::println("Failed to open file for writing: {}", file_path.filename().string());
    return;
  }

  //Write to the file using one of the write functions
  //Se comment above for a few other ways we could write to the file
  file << content;

  //It's good practice to close the file when done
  //The file is closed when the file object goes out of scope
  //The destructor of the file object closes the file
}

void read_file(const std::filesystem::path &file_path)
{
  std::ifstream file(file_path, std::ios::in);// Open for reading
  if (!file.is_open()) {
    fmt::println("Failed to open file for reading: {}", file_path.filename().string());
    return;
  }

  /*
      . The std::getline function reads a line from the file and stores it in
          the string line. This proces is repeated until there are no more lines to read.
  */
  std::string line;
  while (std::getline(file, line)) { fmt::println("{}", line); }
}
}