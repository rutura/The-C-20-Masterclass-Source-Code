// Every stream keeps a current position - where the next read or write will
// happen. Reading/writing normally just advances it. seekg/seekp jump it to
// an arbitrary spot, and tellg/tellp report where it currently is - useful
// once you know a file's layout well enough to jump straight to a record
// instead of reading through everything before it.
//
// This only works cleanly against *fixed-width* records - a name field that
// might be 4 or 8 characters long makes "record 3 starts at byte 24"
// meaningless. So this lecture pads every record to the same width on write.

#include <print>
#include <fstream>
#include <string>
#include <format>

namespace {
    constexpr int recordWidth = 20; // bytes per record, including the '\n'
}

// Pads "name score" to exactly recordWidth - 1 characters, then a newline,
// so every record starts at a predictable byte offset: record i starts at
// byte i * recordWidth.
std::string makeFixedWidthRecord(const std::string& name, int score) {
    std::string body = std::format("{} {}", name, score);
    body.resize(recordWidth - 1, ' '); // pad with spaces up to the width
    return body + "\n";
}

int main() {

    const std::string fileName = "fixed_roster.txt";

    // --- Write three fixed-width records ---
    {
        std::ofstream out(fileName);
        out << makeFixedWidthRecord("Alice", 91);
        out << makeFixedWidthRecord("Bilal", 78);
        out << makeFixedWidthRecord("Chen", 88);
    }
    std::println("Wrote 3 fixed-width records of {} bytes each.", recordWidth);

    // --- seekg: jump straight to record index 2 (Chen) without reading
    // records 0 and 1 first ---
    std::ifstream in(fileName);
    int targetRecord{2};
    in.seekg(targetRecord * recordWidth, std::ios::beg);

    std::string line;
    std::getline(in, line);
    std::println("");
    std::println("Record {} via seekg: \"{}\"", targetRecord, line);

    // --- tellg: report the position after that read ---
    std::println("Position after reading record {}: {}", targetRecord, static_cast<long long>(in.tellg()));
    in.close();

    // --- seekp: overwrite record index 1 (Bilal) in place, without
    // touching records 0 or 2 ---
    std::fstream edit(fileName, std::ios::in | std::ios::out);
    edit.seekp(1 * recordWidth, std::ios::beg);
    edit << makeFixedWidthRecord("Bilal", 82); // corrected score
    edit.close();

    // --- Read the whole file back to confirm only record 1 changed ---
    std::ifstream verify(fileName);
    std::println("");
    std::println("File after overwriting record 1 in place:");
    while (std::getline(verify, line)) {
        std::println("  \"{}\"", line);
    }

    return 0;
}
