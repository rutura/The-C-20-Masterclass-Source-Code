#include <print>
#include <string>

// Chapter 5 introduced std::string for basic text. Here is the rest of
// the everyday toolkit: measuring, indexing, searching, and editing.

int main() {
    std::string path{"/home/ada/reports/2025-summary.txt"};

    // size() and length() are the same function under two names.
    std::println("path       : {}", path);
    std::println("length     : {}", path.length());
    std::println("size       : {}", path.size());
    std::println("capacity   : {}", path.capacity());   // >= size; storage in hand
    std::println("empty()    : {}", path.empty());

    // Index a character. [] is unchecked; at() throws std::out_of_range.
    std::println("first char : {}", path[0]);
    std::println("at(1)      : {}", path.at(1));
    std::println("front/back : {} {}", path.front(), path.back());

    // find() returns the index of the first match, or std::string::npos
    // (a sentinel "not found" value) if there is none.
    std::size_t slash{path.rfind('/')};                 // last '/'
    std::size_t dot{path.rfind('.')};                   // last '.'
    std::println("last '/' at index {}", slash);
    std::println("last '.' at index {}", dot);

    if (path.find("summary") != std::string::npos) {
        std::println("\"summary\" appears in the path");
    }

    // substr(pos, count) copies out a piece. Combine with find() to pull
    // the filename and the extension.
    std::string filename{path.substr(slash + 1)};       // to the end
    std::string stem{filename.substr(0, filename.rfind('.'))};
    std::string extension{path.substr(dot + 1)};
    std::println("filename   : {}", filename);
    std::println("stem       : {}", stem);
    std::println("extension  : {}", extension);

    // + and += build new text. += avoids a temporary, so prefer it when
    // appending in a loop.
    std::string greeting{"Hello"};
    greeting += ", ";
    greeting += "world!";
    std::println("greeting   : {}", greeting);

    // Editing in place: insert(pos, text) and erase(pos, count).
    std::string label{"report.txt"};
    label.insert(0, "final-");
    std::println("after insert: {}", label);
    label.erase(0, 6);                                  // drop "final-"
    std::println("after erase : {}", label);

    // replace(pos, count, text) swaps out a run of characters.
    std::string sentence{"the quick brown fox"};
    sentence.replace(4, 5, "slow");                     // "quick" -> "slow"
    std::println("replaced    : {}", sentence);

    // C++20 prefix/suffix checks, C++23 contains - they say what you mean
    // better than a find() comparison.
    std::println("starts_with(\"/home\") : {}", path.starts_with("/home"));
    std::println("ends_with(\".txt\")    : {}", path.ends_with(".txt"));
    std::println("contains(\"reports\")  : {}", path.contains("reports"));

    // Escape sequences inside a normal string literal.
    std::println("tab\tand\nnewline, a quote \" and a backslash \\");

    // A raw string literal R"(...)" takes every character literally - no
    // escaping. Ideal for Windows paths, regexes, JSON snippets.
    std::string win_path{R"(C:\Users\ada\reports\2025-summary.txt)"};
    std::string json{R"({"name": "Ada", "active": true})"};
    std::println("raw path   : {}", win_path);
    std::println("raw json   : {}", json);

    return 0;
}
