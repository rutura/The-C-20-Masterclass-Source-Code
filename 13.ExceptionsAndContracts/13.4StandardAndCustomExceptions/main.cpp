#include <exception>
#include <print>
#include <stdexcept>
#include <string>
#include <vector>

// The standard hierarchy, in the part that matters day to day:
//
//   std::exception
//   ├── std::logic_error          a bug in the caller: it could have been avoided
//   │   ├── std::invalid_argument
//   │   ├── std::out_of_range
//   │   └── std::domain_error
//   ├── std::runtime_error        something went wrong that nobody could predict
//   │   ├── std::range_error
//   │   ├── std::overflow_error
//   │   └── std::system_error
//   └── std::bad_alloc, std::bad_cast, ...   thrown by the language and library
//
// Every one of them answers what(), which returns a C string.

// A custom exception: derive from the closest standard class, so that existing
// handlers for the standard types still catch it, and add the data a handler
// would actually want.
class SensorError : public std::runtime_error {
public:
    SensorError(int sensor_id, const std::string& message)
        : std::runtime_error{"sensor " + std::to_string(sensor_id) + ": " + message},
          sensor_id_{sensor_id} {}

    int sensor_id() const noexcept { return sensor_id_; }

private:
    int sensor_id_;
};

// A more specific failure of the same family. Handlers for SensorError catch
// it too; handlers that care can ask for the narrower type first.
class SensorOffline final : public SensorError {
public:
    explicit SensorOffline(int sensor_id) : SensorError{sensor_id, "offline"} {}
};

class SensorOutOfRange final : public SensorError {
public:
    SensorOutOfRange(int sensor_id, double value)
        : SensorError{sensor_id, "reading " + std::to_string(value) + " is out of range"},
          value_{value} {}

    double value() const noexcept { return value_; }

private:
    double value_;
};

double read(int sensor_id) {
    switch (sensor_id) {
        case 1:  return 21.5;
        case 2:  throw SensorOffline{sensor_id};
        case 3:  throw SensorOutOfRange{sensor_id, 999.9};
        default: throw std::out_of_range{"no sensor with id " + std::to_string(sensor_id)};
    }
}

int main() {

    for (int id : {1, 2, 3, 4}) {
        try {
            std::println("sensor {} reads {}", id, read(id));
        }
        // Most specific first, the general ones last.
        catch (const SensorOutOfRange& error) {
            std::println("sensor {} out of range, value was {}", error.sensor_id(), error.value());
        }
        catch (const SensorError& error) {
            std::println("sensor problem, id {}: {}", error.sensor_id(), error.what());
        }
        // The catch-all for the standard family: also catches the library's own
        // exceptions (like the out_of_range above), so the program stays up.
        catch (const std::exception& error) {
            std::println("other failure: {}", error.what());
        }
    }

    // The library throws too. Three you will meet quickly:
    std::vector<int> values{1, 2, 3};
    try {
        std::println("{}", values.at(10));            // at() checks, operator[] does not
    }
    catch (const std::out_of_range& error) {
        std::println("\nvector::at: {}", error.what());
    }

    try {
        std::println("{}", std::stoi("hello"));
    }
    catch (const std::invalid_argument& error) {
        std::println("stoi: {}", error.what());
    }

    try {
        std::vector<int> huge(values.max_size() + 1);   // more than can ever exist
    }
    catch (const std::length_error&) {
        std::println("vector: length_error caught");
    }
    return 0;
}
