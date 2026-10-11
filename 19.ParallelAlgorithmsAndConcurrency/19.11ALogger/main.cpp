#include <cstddef>
#include <iostream>
#include <print>
#include <string>
#include <syncstream>
#include <thread>
#include <vector>

#include "logger.h"

int main() {
    // ---- 1. Why not just print from every thread? ---------------------------------------------
    // std::println writes one whole line in one call, and different calls do not
    // corrupt each other, but a line built from SEVERAL calls can be cut in two
    // by another thread's output. For a stream, std::osyncstream collects
    // everything written to it and hands it over in one piece when it is
    // destroyed. (This is the one place we use std::cout: osyncstream wraps a stream.)
    std::println("--- osyncstream: a line is never cut in two");
    {
        std::vector<std::jthread> stations;
        for (int station{0}; station < 4; ++station) {
            stations.emplace_back([station] {
                std::osyncstream out{std::cout};
                out << "[varies] station " << station << " says " << "hello" << " from its own thread\n";
            });
        }
    }

    // ---- 2. A logger with its own writer thread -------------------------------------------------------
    std::println("\n--- a logger");
    std::vector<std::string> written;               // the sink: only the writer thread touches it
    {
        Logger logger{[&written](const std::string& line) { written.push_back(line); }};

        std::vector<std::jthread> stations;
        for (int station{0}; station < 4; ++station) {
            stations.emplace_back([&logger, station] {
                for (int i{0}; i < 50; ++i) {
                    logger.log(Level::info, "station " + std::to_string(station) + " reading " + std::to_string(i));
                }
                if (station == 2) {
                    logger.log(Level::warning, "station 2 battery low");
                }
            });
        }
        // The stations are joined first (declared last, destroyed first),
        // then the logger's destructor drains the queue and stops the writer.
    }

    // `written` is safe to read now: the writer thread has been joined.
    std::println("lines written: {}", written.size());
    std::println("last line: {}", written.back());

    // The lines of ONE station must come out in the order that station logged
    // them, whatever the other stations did in between.
    bool in_order{true};
    for (int station{0}; station < 4; ++station) {
        std::string prefix{"[info] station " + std::to_string(station) + " reading "};
        int expected_next{0};
        for (const std::string& line : written) {
            if (line.starts_with(prefix)) {
                int number{std::stoi(line.substr(prefix.size()))};
                if (number != expected_next) {
                    in_order = false;
                }
                ++expected_next;
            }
        }
    }
    std::println("each station's lines are in its own order: {}", in_order);

    std::size_t warnings{0};
    for (const std::string& line : written) {
        if (line.starts_with("[warning]")) {
            ++warnings;
        }
    }
    std::println("warnings: {}", warnings);
    return 0;
}
