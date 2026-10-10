#include <cstddef>
#include <print>

// A log of readings that owns a block of heap memory. This is the class that
// 9.9 said you would write: the new[] is in the constructor, the delete[] is
// in the destructor, and so the memory can never be forgotten.
class ReadingLog {
public:
    explicit ReadingLog(std::size_t capacity)
        : data_{new double[capacity]{}}, capacity_{capacity} {
        std::println("  log of {} created", capacity_);
    }

    // The destructor: a function with the class name and a ~ in front. It runs
    // automatically, exactly once, when the object's life ends, however that
    // happens. It never takes parameters and never returns anything.
    ~ReadingLog() {
        std::println("  log of {} destroyed ({} readings stored)", capacity_, size_);
        delete[] data_;
    }

    // Copying would make two logs think they own the same block, which ends in
    // a double delete. Until 10.7 shows the right way, forbid it outright.
    ReadingLog(const ReadingLog&) = delete;
    ReadingLog& operator=(const ReadingLog&) = delete;

    bool add(double reading) {
        if (size_ == capacity_) {
            return false;
        }
        data_[size_++] = reading;
        return true;
    }

    std::size_t size() const { return size_; }

    double average() const {
        if (size_ == 0) {
            return 0.0;
        }
        double total{0.0};
        for (std::size_t i{0}; i < size_; ++i) {
            total += data_[i];
        }
        return total / static_cast<double>(size_);
    }

private:
    double* data_;
    std::size_t capacity_;
    std::size_t size_{0};
};

// The destructor runs on EVERY way out of the scope. This function leaves
// early, and the log still cleans up: the thing 9.9 said a raw new/delete
// pair cannot promise.
bool store_if_valid(double reading) {
    ReadingLog log{4};

    if (reading < -50.0 || reading > 60.0) {
        std::println("  reading {} is out of range, leaving early", reading);
        return false;                 // the destructor runs here
    }

    log.add(reading);
    std::println("  stored {}", reading);
    return true;                      // and here
}

int main() {

    std::println("a log in main:");
    ReadingLog main_log{8};
    main_log.add(68.0);
    main_log.add(72.5);
    std::println("  average so far {:.2f}", main_log.average());

    std::println("\nnested scopes: objects are destroyed in REVERSE order of creation");
    {
        ReadingLog outer{2};
        {
            ReadingLog inner{3};
            std::println("  leaving the inner scope");
        }
        std::println("  leaving the outer scope");
    }

    std::println("\nleaving a function early:");
    store_if_valid(21.0);
    store_if_valid(99.0);

    std::println("\na log on the heap: new runs the constructor, delete the destructor");
    ReadingLog* heap_log{new ReadingLog{5}};
    std::println("  using it, size {}", heap_log->size());
    delete heap_log;

    std::println("\na temporary lives until the end of the statement:");
    std::println("  size of a temporary log: {}", ReadingLog{6}.size());
    std::println("  (the temporary is already gone)");

    std::println("\nend of main, main_log is destroyed after this line");
    return 0;
}
