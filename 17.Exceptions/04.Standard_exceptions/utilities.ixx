module;

#include <string_view>
#include <iostream>
#include <array>
#include <filesystem>
#include <fmt/format.h>

export module utilities; 

import exceptions_1;
import exceptions_2;
import exceptions_3;
import exceptions_4;

// #1: Catching standard exceptions
export void exceptions_1_demo(){
	using exceptions_1::Animal;
	using exceptions_1::Feline;

	Animal animal;	// Animal can't bee cast to Feline. But we catch the exception and we are OK.
	try {
		Feline &feline_ref = dynamic_cast<Feline &>(animal); // will throw std::bad_cast
	} catch (std::exception &ex) {
		fmt::println("Something is wrong : {}", ex.what());
	}

	fmt::println("END.");
}

// #2: Throwing standard exceptions
export  void exceptions_2_demo(){

	exceptions_2::Students students("John Snow", "Terry Boomd", "Nicholai Itchenko", "Bilom Atunde", "Lily Park");

	try {
		// fmt::println( students.get_student(2) );
		fmt::println("{}", students.get_student(-2));
	} catch (std::exception &ex) {
		fmt::println("Exception cought : {}", ex.what());
	}
	fmt::println("END.");
}

// #3: Deriving from standard exceptions
export void exceptions_3_demo(){

	using exceptions_3::ArrayIndexOutOfRangeException;
	using exceptions_3::access_element;

	// Using std::array for safer array management
    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    try {
        // This will throw an exception as we attempt to access an invalid index (e.g., 10)
        int value = access_element(arr, 10);
		fmt::println("Element at index 10: {}", value);
    } catch (const ArrayIndexOutOfRangeException& e) {
		fmt::println("Caught exception: {}", e.what());
    }
}


//#4: Using exceptions with file I/O
export void exceptions_4_demo(){

	/*
	{
		//Without exceptions
		std::filesystem::path file_path = R"(D:\sample_file.csv)"; // Windows
		//std::filesystem::path file_path = R"(/path/to/your/sample_file.csv)"; // Linux

		using exceptions_4::csv_no_except::write_csv;
		using exceptions_4::csv_no_except::read_csv;

		//Write and read the file
		//write_csv(file_path);
		read_csv(file_path);
	}
	*/

	{
		//With exceptions
		std::filesystem::path file_path = R"(D:\sample_file.csv)"; // Windows
		//std::filesystem::path file_path = R"(/path/to/your/sample_file.csv)"; // Linux

		using exceptions_4::csv_with_except::write_csv;
		using exceptions_4::csv_with_except::read_csv;

		//Write and read the file
		/*
		try{
			write_csv(file_path);
		} catch (std::exception &ex) {
			fmt::println("Exception cought : {}", ex.what());
		}
		*/

		try{
			read_csv(file_path);
		} catch (std::exception &ex) {
			fmt::println("Exception cought : {}", ex.what());
		}
	}


}