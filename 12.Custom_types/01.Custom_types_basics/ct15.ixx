/*
    . Writting and reading objects to/from files
        . POD types
        . Non-POD types
        . csv
        . json
*/
module;

#include <fstream>
#include <filesystem>
#include <vector>
#include <fmt/format.h>

export module ct15;

namespace pod_types {

    export struct PODType {
        int id;
        double value;
    };

    // Function to write POD to a binary file (returns bool for success)
    export bool write_pod(const std::filesystem::path& filename, const PODType& pod) {
        std::ofstream out_file(filename, std::ios::binary);
        if (!out_file) {
            return false;
        }
        out_file.write(reinterpret_cast<const char*>(&pod), sizeof(PODType));
        return out_file.good();
    }

    // Function to read POD from a binary file (returns bool for success)
    export bool read_pod(const std::filesystem::path& filename, PODType& pod) {
        std::ifstream in_file(filename, std::ios::binary);
        if (!in_file) {
            return false;
        }
        in_file.read(reinterpret_cast<char*>(&pod), sizeof(PODType));
        return in_file.good();
    }

    // Function to write a vector of PODType objects to a file
    export bool write_pod_vector(const std::filesystem::path& file_path,
                            const std::vector<pod_types::PODType>& pod_vector) {
        std::ofstream out_file(file_path, std::ios::binary);
        if (!out_file) {
            fmt::print("Failed to open file for writing.\n");
            return false;
        }

        for (const auto& pod : pod_vector) {
            out_file.write(reinterpret_cast<const char*>(&pod), sizeof(pod_types::PODType));
        }

        if (!out_file.good()) {
            fmt::print("Failed to write PODType objects to file.\n");
            return false;
        }

        out_file.close();
        return true;
    }

    // Function to read a vector of PODType objects from a file
    export bool read_pod_vector(const std::filesystem::path& file_path,
                                    std::vector<pod_types::PODType>& pod_vector) {
        std::ifstream in_file(file_path, std::ios::binary);
        if (!in_file) {
            fmt::print("Failed to open file for reading.\n");
            return false;
        }

        pod_types::PODType read_pod;
        while (in_file.read(reinterpret_cast<char*>(&read_pod), sizeof(pod_types::PODType))) {
            pod_vector.push_back(read_pod);
        }

        if (!in_file.eof() && !in_file.good()) {
            fmt::print("Failed to read PODType objects from file.\n");
            return false;
        }

        in_file.close();
        return true;
    }

}   // namespace pod_types



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
}   // namespace non_pod_types