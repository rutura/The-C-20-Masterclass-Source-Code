/*
    . Deriving from standard exceptions: An example
*/
module;

#include <array>
#include <string>
#include <stdexcept>

export module exceptions_3;

namespace exceptions_3{

    export class ArrayIndexOutOfRangeException : public std::exception {
    public:
        ArrayIndexOutOfRangeException(int index, int max_size) noexcept
            : m_index(index), m_max_size(max_size),
            m_message("Error: Index " + std::to_string(m_index) +
                        " out of range (valid range: 0 to " + std::to_string(m_max_size - 1) + ")") {}

        const char* what() const noexcept override {
            return m_message.c_str();
        }

        int get_index() const { return m_index; }
        int get_max_size() const { return m_max_size; }

    private:
        int m_index;
        int m_max_size;
        std::string m_message;
    };


    // Template function to access elements safely from a std::array
    export template <typename T, std::size_t N>
    T access_element(const std::array<T, N>& arr, int index) {
        if (index < 0 || index >= static_cast<int>(N)) {
            throw ArrayIndexOutOfRangeException(index, N);
        }
        return arr[index];
    }
    
} // namespace exceptions_3
