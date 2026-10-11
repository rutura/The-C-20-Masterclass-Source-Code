#pragma once

#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <stop_token>
#include <string>
#include <thread>
#include <utility>

// Every thread of a program wants to say what it is doing, and the slow part of
// saying it (writing to a file, the console, the network) should not make the
// thread wait. A LOGGER solves both with the queue of 19.7:
//
//     station thread 1 ---+
//     station thread 2 ---+--> [ queue of messages ] --> ONE writer thread --> the sink
//     station thread 3 ---+
//
// The caller only pays for locking and pushing a string. A single thread does
// the writing, so the sink (a file, say) is never used by two threads at once
// and needs no lock of its own, and the lines of one thread come out in the
// order that thread logged them.
enum class Level { info, warning, error };

class Logger {
public:
    using Sink = std::function<void(const std::string&)>;

    // `sink` is called for every line, always from the writer thread.
    explicit Logger(Sink sink)
        : sink_{std::move(sink)},
          writer_{[this](std::stop_token token) { write_lines(token); }} {}

    // Leaving the scope drains the queue first (like the pool of 19.10), then
    // says goodbye: nothing that was logged is lost.
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(Level level, std::string message) {
        {
            std::lock_guard<std::mutex> lock{mutex_};
            lines_.push_back(std::string{name_of(level)} + " " + std::move(message));
        }
        wakeup_.notify_one();
    }

private:
    static const char* name_of(Level level) {
        switch (level) {
        case Level::info:    return "[info]";
        case Level::warning: return "[warning]";
        case Level::error:   return "[error]";
        }
        return "[?]";
    }

    void write_lines(std::stop_token token) {
        while (true) {
            std::string line;
            {
                std::unique_lock<std::mutex> lock{mutex_};
                if (!wakeup_.wait(lock, token, [this] { return !lines_.empty(); })) {
                    break;                          // stop requested and nothing left to write
                }
                line = std::move(lines_.front());
                lines_.pop_front();
            }
            sink_(line);                            // slow work, done without holding the lock
        }
        sink_("[info] logger shut down");
    }

    Sink sink_;
    std::mutex mutex_;
    std::condition_variable_any wakeup_;
    std::deque<std::string> lines_;
    std::jthread writer_;                           // last member: stopped and joined first
};
