#include <fstream>
#include <print>
#include <string>
#include <filesystem>

// Part 1 of the file lecture: write a list of names to a text file.
//
// A file is just another stream. std::cout sends characters to the
// console; std::ofstream ("output file stream") sends them to a file
// with the same << operator.

int main() {

    // Working directory
    std::println("Working directory: {}",
        std::filesystem::current_path().string());

    // Opening the stream with a filename creates (or truncates) the file
    // in the program's working directory - see the lecture notes for
    // where that actually is when you run from an IDE.
    std::ofstream out{"names.txt"};

    // Always check the file actually opened before writing to it.
    if (!out) {
        std::println("Could not open names.txt for writing.");
        return 1;
    }

    // One name per line. The '\n' is what makes each name its own line,
    // which is exactly what read.cpp relies on when it reads line by line.
    for (const std::string& name : {"Ada", "Alan", "Grace", "Linus", "Bjarne"}) {
        out << name << '\n';
    }

    // The stream also closes automatically when `out` goes out of scope,
    // but closing explicitly makes the "we're done writing" point clear.
    out.close();

    std::println("Wrote 5 names to names.txt");

    return 0;
}
