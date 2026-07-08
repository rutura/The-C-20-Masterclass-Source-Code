// <filesystem> (C++17) is the standard, portable way to ask questions
// about paths and directories - does this exist, is it a file or a folder,
// what's in this folder - without shelling out to OS-specific calls.

#include <print>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {

    // std::filesystem::path wraps a path string and knows how to take it
    // apart - no manual string-splitting on '/' or '\\' needed, and it
    // handles both separators portably.
    fs::path notesPath = "notes_dir/notes.txt";

    std::println("path            : {}", notesPath.string());
    std::println("filename        : {}", notesPath.filename().string());
    std::println("extension       : {}", notesPath.extension().string());
    std::println("parent_path     : {}", notesPath.parent_path().string());

    // --- exists / is_directory: check before you act ---
    std::println("");
    std::println("exists before creating anything : {}", fs::exists(notesPath));

    // create_directories makes every missing directory in the path, the
    // same way `mkdir -p` does - fs::create_directory alone would fail if
    // notes_dir didn't already exist.
    fs::create_directories(notesPath.parent_path());
    std::println("notes_dir exists now             : {}", fs::exists(notesPath.parent_path()));
    std::println("notes_dir is_directory           : {}", fs::is_directory(notesPath.parent_path()));

    // Write a couple of files into it using the ofstream from two lectures
    // ago - <filesystem> and <fstream> work together, one locates things,
    // the other reads/writes their contents.
    {
        std::ofstream a(notesPath);
        a << "first file\n";
    }
    {
        std::ofstream b(notesPath.parent_path() / "extra.txt");
        b << "second file\n";
    }
    // path's operator/ appends a path segment with the correct separator
    // for the platform - safer than string-concatenating "/" by hand.

    std::println("notes.txt exists now             : {}", fs::exists(notesPath));
    std::println("notes.txt is_directory           : {}", fs::is_directory(notesPath));
    std::println("notes.txt is_regular_file        : {}", fs::is_regular_file(notesPath));

    // --- directory_iterator: list what's actually in a folder ---
    std::println("");
    std::println("Contents of {}:", notesPath.parent_path().string());
    for (const auto& entry : fs::directory_iterator(notesPath.parent_path())) {
        std::println("  {} ({} bytes)", entry.path().filename().string(), entry.file_size());
    }

    // Clean up what this lecture created, so re-running it starts fresh.
    fs::remove_all(notesPath.parent_path());
    std::println("");
    std::println("Cleaned up notes_dir. exists now : {}", fs::exists(notesPath.parent_path()));

    return 0;
}
