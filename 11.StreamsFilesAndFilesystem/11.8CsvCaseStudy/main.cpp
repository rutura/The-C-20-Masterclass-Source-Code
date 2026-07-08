// This chapter's payoff: everything so far - ifstream, getline,
// istringstream - combines to parse a real-shaped file end to end.
// students.csv holds one header row followed by "name,course,score,semester"
// records. The goal: read it, and report each course's average score.

#include <print>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <format>
#include <stdexcept>

struct Enrollment {
    std::string name;
    std::string course;
    int score{};
    std::string semester;
};

// std::print needs a formatter to know how to render a custom type - same
// pattern used for Book/Point/Student in the Algorithms/Ranges chapter.
template <>
struct std::formatter<Enrollment> : std::formatter<std::string> {
    auto format(const Enrollment& e, std::format_context& ctx) const {
        return std::formatter<std::string>::format(
            std::format("{} / {} / {} / {}", e.name, e.course, e.score, e.semester), ctx);
    }
};

// Splits one CSV line into its comma-separated fields using the same
// istringstream + getline(delimiter) idiom from 12.3StringStreams.
std::vector<std::string> splitCsvLine(const std::string& line) {
    std::vector<std::string> fields;
    std::istringstream lineReader(line);
    std::string field;
    while (std::getline(lineReader, field, ',')) {
        fields.push_back(field);
    }
    return fields;
}

int main() {

    std::ifstream in("students.csv");
    if (!in) {
        std::println("Could not open students.csv - run this from the lecture folder.");
        return 1;
    }

    std::vector<Enrollment> enrollments;

    std::string line;
    std::getline(in, line); // discard the header row ("name,course,score,semester")

    while (std::getline(in, line)) {
        auto fields = splitCsvLine(line);
        if (fields.size() != 4) {
            continue; // skip a malformed row rather than crash on it
        }

        Enrollment e;
        e.name = fields[0];
        e.course = fields[1];
        try {
            e.score = std::stoi(fields[2]);
        } catch (const std::invalid_argument&) {
            continue; // skip a row whose score isn't a number rather than crash on it
        }
        e.semester = fields[3];
        enrollments.push_back(e);
    }

    std::println("Parsed {} enrollment records:", enrollments.size());
    for (const auto& e : enrollments) {
        std::println("  {}", e);
    }

    // --- Aggregate: average score per course ---
    // A std::map<std::string, ...> keyed by course name, accumulating a
    // running total and count so the average can be computed once, after
    // every record has been seen.
    std::map<std::string, int> totalByCourse;
    std::map<std::string, int> countByCourse;

    for (const auto& e : enrollments) {
        totalByCourse[e.course] += e.score;
        countByCourse[e.course] += 1;
    }

    std::println("");
    std::println("Average score by course:");
    for (const auto& [course, total] : totalByCourse) {
        double average = static_cast<double>(total) / countByCourse[course];
        std::println("  {:<12} {:.1f}", course, average);
    }

    return 0;
}
