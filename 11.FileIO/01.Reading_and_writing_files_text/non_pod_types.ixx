module;

#include <filesystem>
#include <fmt/format.h>
#include <vector>
#include <fstream>
#include <string>

export module non_pod_types;

namespace non_pod_types{

    export class Person {
    public:
        std::string name;
        int age;

        // Serialization function for a single person
        void serialize(std::ofstream& ofs) const {
            size_t name_size = name.size();
            ofs.write(reinterpret_cast<const char*>(&name_size), sizeof(name_size));
            ofs.write(name.data(), name_size);
            ofs.write(reinterpret_cast<const char*>(&age), sizeof(age));
        }

        // Deserialization function for a single person
        void deserialize(std::ifstream& ifs) {
            size_t name_size;
            ifs.read(reinterpret_cast<char*>(&name_size), sizeof(name_size));

            name.resize(name_size);

            //Read the name and age from the file and store in the object's members: name and age
            ifs.read(name.data(), name_size);
            ifs.read(reinterpret_cast<char*>(&age), sizeof(age));
        }
    };


    // Function to write a vector of person objects to a file
    export void write_persons_to_file(const std::vector<Person>& persons, const std::filesystem::path& file_path) {
        std::ofstream ofs(file_path, std::ios::binary);
        if (!ofs) {
            fmt::println("Failed to open file for writing: {}", file_path.string());
            return;
        }

        size_t vector_size = persons.size();
        ofs.write(reinterpret_cast<const char*>(&vector_size), sizeof(vector_size));

        for (const auto& p : persons) {
            p.serialize(ofs);
        }

        fmt::println("Serialized {} person(s) to file: {}", vector_size, file_path.string());
    }

    // Function to read a vector of person objects from a file
    export std::vector<Person> read_persons_from_file(const std::filesystem::path& file_path) {
        std::ifstream ifs(file_path, std::ios::binary);
        if (!ifs) {
            fmt::println("Failed to open file for reading: {}", file_path.string());
            return {};
        }

        size_t vector_size;
        ifs.read(reinterpret_cast<char*>(&vector_size), sizeof(vector_size));

        std::vector<Person> persons(vector_size);
        for (auto& p : persons) {
            p.deserialize(ifs);
        }

        fmt::println("Deserialized {} person(s) from file: {}", vector_size, file_path.string());
        return persons;
    }
}