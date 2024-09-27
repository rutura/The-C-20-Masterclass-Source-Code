module;

#include <string_view>
#include <fmt/format.h>
#include <memory>
#include <vector>
#include <cstdint>
#include <filesystem>

export module utilities; 

import ct1;
import ct2;
import ct3;
import ct4;
import ct5;
import ct6;
import ct7;
import ct8;
import ct9;
import ct10;
import ct11;
import ct12; // Not used
import ct13;
import ct14;
import ct15;
import ct16;
import ct17;


export void ct1_demo(){

	/*
		. {:#010x} is a format specifier that will print the hex value with 10 digits and 0 padding.
		. #  indicates that the output should include the 0x prefix for hexadecimal numbers.
		. 010 indicates that the output should be 10 characters wide and zero-padded.
		. x indicates that the number should be printed in lowercase hexadecimal.	
	*/
	ct1::Pixel p;

	//Change the data inside the Pixel object
	p.m_color = 0x00FF00FF;
	p.pos_x = 10;
	p.pos_y = 20;

	fmt::println("Pixel color: {:#010x}", p.m_color);
	fmt::println("Pixel position: ({}, {})", p.pos_x, p.pos_y);
}


export void ct2_demo(){
	
	//Create the object on the stack
	ct2::Pixel p{0x00FF00FF, 10, 20 };

	//Change the data inside the Pixel object
	p.set_color(0x00FF00FF);
	p.set_x(10);
	p.set_y(20);

	fmt::println("Pixel color: {:#010x}", p.get_color());
	fmt::println("Pixel position: ({}, {})", p.get_x(), p.get_y());

	//Create objects on the heap with raw pointers
	ct2::Pixel* p1 = new ct2::Pixel(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p1->get_color());
	fmt::println("Pixel position: ({}, {})", p1->get_x(), p1->get_y());
	delete p1;

	//Create objects on the heap with smart pointers
	auto p2 = std::make_unique<ct2::Pixel>(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p2->get_color());
	fmt::println("Pixel position: ({}, {})", p2->get_x(), p2->get_y());
	p2->print_access_count();

	//When the default constructor is needed
	/*
	ct2::Pixel p;		// Compilation error
	ct2::Pixel pixels1[10];	// Compilation error
	ct2::Pixel* pixels2 = new ct2::Pixel[10];	// Compilation error
	ct2::Pixel pixels3[]{ct2::Pixel(0x00FF00FF, 10, 20), ct2::Pixel(0x00FF00FF, 10, 20)};	// OK
	*/

}

export void ct3_demo(){
	
	ct3::Pixel p;

	//Change the data inside the Pixel object
	p.set_color(0x00FF00FF);
	p.set_x(10);
	p.set_y(20);

	fmt::println("Pixel color: {:#010x}", p.get_color());
	fmt::println("Pixel position: ({}, {})", p.get_x(), p.get_y());

	//Create objects on the heap with raw pointers
	ct3::Pixel* p1 = new ct3::Pixel(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p1->get_color());
	fmt::println("Pixel position: ({}, {})", p1->get_x(), p1->get_y());
	delete p1;

	//Create objects on the heap with smart pointers
	auto p2 = std::make_unique<ct3::Pixel>(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p2->get_color());
	fmt::println("Pixel position: ({}, {})", p2->get_x(), p2->get_y());
}

export void ct4_demo(){
	
	ct4::Pixel p;

	//Change the data inside the Pixel object
	p.set_color(0x00FF00FF);
	p.set_x(10);
	p.set_y(20);

	fmt::println("Pixel color: {:#010x}", p.get_color());
	fmt::println("Pixel position: ({}, {})", p.get_x(), p.get_y());

	//Create objects on the heap with raw pointers
	ct4::Pixel* p1 = new ct4::Pixel(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p1->get_color());
	fmt::println("Pixel position: ({}, {})", p1->get_x(), p1->get_y());
	delete p1;

	//Create objects on the heap with smart pointers
	auto p2 = std::make_unique<ct4::Pixel>(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p2->get_color());
	fmt::println("Pixel position: ({}, {})", p2->get_x(), p2->get_y());
}


export void ct5_demo(){

	ct5::Pixel p;

	//Change the data inside the Pixel object
	p.set_color(0x00FF00FF);
	p.set_x(10);
	p.set_y(20);

	fmt::println("Pixel color: {:#010x}", p.get_color());
	fmt::println("Pixel position: ({}, {})", p.get_x(), p.get_y());
	

	// Recursive lambda with explicit object parameters
	auto fib = [](auto self, int n) -> int {
		if(n <= 1) return n;
		return self(self, n - 1) + self(self, n - 2);
	};

	fmt::println("Fibonacci(10): {}", fib(fib, 10));
}

export void ct6_demo(){

	//Use the default constructor
	ct6::Pixel p;

	//Constructor a ct6::Pixel passing in values at construction
	//ct6::Pixel p(0x00FFFFFF, 100, 200);

	fmt::println("Pixel color: {:#010x}", p.get_color());
	fmt::println("Pixel position: ({}, {})", p.get_x(), p.get_y());

	//Create objects on the heap with raw pointers
	ct6::Pixel* p1 = new ct6::Pixel(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p1->get_color());
	fmt::println("Pixel position: ({}, {})", p1->get_x(), p1->get_y());
	delete p1;

	//Create objects on the heap with smart pointers
	auto p2 = std::make_unique<ct6::Pixel>(0x00FF00FF, 10, 20);
	fmt::println("Pixel color: {:#010x}", p2->get_color());
	fmt::println("Pixel position: ({}, {})", p2->get_x(), p2->get_y());
}

export void ct7_demo(){

	
	ct7::Pixel p(0x00FF00FF, ct7::Position{10,20}, 0x00FF00FF);

	//Change the data inside the Pixel object
	p.set_color(0x00FF00FF);
	p.set_x(10);
	p.set_y(20);

}

export void ct8_demo(){

	ct8::Pixel p1(0x00FF00FF, 10, 20);
	ct8::Pixel p2 = p1;

	fmt::println("Pixel 1 color: {:#010x}", p1.get_color());
	fmt::println("Pixel 1 position: ({}, {})", p1.get_x(), p1.get_y());
	fmt::println("Pixel 2 color: {:#010x}", p2.get_color());
	fmt::println("Pixel 2 position: ({}, {})", p2.get_x(), p2.get_y());
}

// Example function that takes a Pixel by value
void process_pixel(ct9::Pixel p) {
    fmt::print("Processing pixel: color={}, pos=({}, {})\n", p.get_color(), p.get_x(), p.get_y());
}

// Example function that returns a Pixel by value
ct9::Pixel create_pixel() {
    ct9::Pixel p{0xFF0000, 30, 40};
    return p;  // Copy constructor may be invoked here (but likely optimized out)
}

export void ct9_demo(){
	
	ct9::Pixel p1(0x00FF00FF, 10, 20);
	ct9::Pixel p2 = p1; //Deep copy
	/*

	fmt::println("Pixel 1 color: {:#010x}", p1.get_color());
	fmt::println("Pixel 1 position: ({}, {})", p1.get_x(), p1.get_y());
	fmt::println("Pixel 2 color: {:#010x}", p2.get_color());
	fmt::println("Pixel 2 position: ({}, {})", p2.get_x(), p2.get_y());

	p1.set_x(100);
	p1.set_y(200);

	fmt::println("After changing the position of Pixel 1");
	fmt::println("Pixel 1 color: {:#010x}", p1.get_color());
	fmt::println("Pixel 1 position: ({}, {})", p1.get_x(), p1.get_y());
	fmt::println("Pixel 2 color: {:#010x}", p2.get_color());
	fmt::println("Pixel 2 position: ({}, {})", p2.get_x(), p2.get_y());
	*/

	//Cases where the copy constructor is called
	// 1. Copy initialization
	/*
    ct9::Pixel p1{0xFFFFFF, 10, 20};
    ct9::Pixel p2 = p1;  // Copy constructor is called
	*/

    // 2. Passing by value
    //process_pixel(p1);  // Copy constructor is called to pass p1 to the function

    // 3. Returning by value: This may not always call the copy constructor due to RVO (Return Value Optimization)
    //ct9::Pixel p3 = create_pixel();  // Copy constructor may be called (or elided)

    // 5. Copying an object in a collection (vector)
	/*
    std::vector<ct9::Pixel> pixels;
    pixels.push_back(p1);  // Copy constructor is called when adding to the vector
	*/

    // 6. Explicit copy constructor
    //ct9::Pixel p5(p1);  // Copy constructor is explicitly called


}


export void ct10_demo(){

	//ct10::Pixel p1;                    // Uses default constructor
	//ct10::Pixel p2{0xFFFF0000};         // Uses color-only constructor, which delegates to the three-argument constructor
	ct10::Pixel p3{0xFF00FF00, 100, 50}; // Directly uses the three-argument constructor
	ct10::Pixel p4{p3};                 // Uses copy constructor with delegation

}


export void ct11_demo(){

	/*
	uint32_t color = 0xFF00FF00;
	ct11::print_pixel(color);	//If the one param constructor is explicit, this will not compile
	*/

	/*
	ct11::Pixel p1{0xFF00FF00, 100, 50}; // Directly uses the three-argument constructor
	ct11::print_pixel(p1);
	*/

}


export void ct13_demo(){

	ct13::Pixel p1{0xFF00FF00, 100, 50};
	ct13::Pixel p2{0x00FF00FF, 200, 150};

	p2 = p1;

	fmt::println("Pixel 1 color: {:#010x}", p1.get_color());
	fmt::println("Pixel 1 position: ({}, {})", p1.get_x(), p1.get_y());
	fmt::println("Pixel 2 color: {:#010x}", p2.get_color());
	fmt::println("Pixel 2 position: ({}, {})", p2.get_x(), p2.get_y());
}


export void ct14_demo(){
	ct14::Pixel p1{0xFF00FF00, 100, 50};
	ct14::Pixel p2{0x00FF00FF, 200, 150};

	p2 = p1;

	fmt::println("Pixel 1 color: {:#010x}", p1.get_color());
	fmt::println("Pixel 1 position: ({}, {})", p1.get_x(), p1.get_y());
	fmt::println("Pixel 2 color: {:#010x}", p2.get_color());
	fmt::println("Pixel 2 position: ({}, {})", p2.get_x(), p2.get_y());


	//Distinguishing between copy and assignment
	/*
	ct14::Pixel p3{0xFF00FF00, 100, 50};
	ct14::Pixel p4{p3}; // Copy constructor

	p4 = p3; // Assignment operator
	*/
}


//ct15: Reading and writting POD and non-POD types
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



export void ct15_demo(){
	read_write_pod_types();
	write_and_read_several_pod_types();
	write_read_several_non_pod_types();

}


export void ct16_demo(){

    // Create a vector of Pixel objects
    std::vector<ct16::Pixel> pixels = {
        ct16::Pixel(0xFF0000FF, 10, 20), // Red pixel at (10, 20)
        ct16::Pixel(0xFF00FF00, 30, 40), // Green pixel at (30, 40)
        ct16::Pixel(0xFFFF0000, 50, 60)  // Blue pixel at (50, 60)
    };

    // Define the file path for serialization
    std::filesystem::path file_path = R"(D:\serialized_pixels.bin)"; // Windows
    //std::filesystem::path file_path = R"(/path/to/your/input_file.bin)"; // Linux

    // Serialize the vector of Pixel objects to a file
	ct16::save_pixels(pixels, file_path);

	//Deserialize the vector of Pixel objects from the file
	std::vector<ct16::Pixel> deserialized_pixels = ct16::load_pixels(file_path);

	// Print the deserialized Pixel objects to verify
	fmt::println("Deserialized Pixels from binary file");
	for (const auto& p : deserialized_pixels) {
		auto position = p.get_position();
		fmt::print("Pixel color: {:#08X}, Position: ({}, {})\n", p.get_color(), position.x, position.y);
	}
}

export void ct17_demo(){
	ct17::Pixel p1{0xFF00FF00, 100, 50};
	ct17::Pixel p2{0x00FF00FF, 200, 150};

	ct17::Canvas canvas;
	canvas.display_pixel(p1);
	canvas.display_pixel(p2);

	ct17::print_pixel(p1);
	ct17::print_pixel(p2);

	canvas.modify_pixel(p1, 0xFFFF0000, 300, 250);
	canvas.display_pixel(p1);
	ct17::print_pixel(p1);
}