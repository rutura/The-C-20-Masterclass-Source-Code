#pragma once

#include <filesystem>
#include <vector>
#include <fstream>
#include <string>

namespace non_pod_types{
class Person{
public:
    std::string name;
    int age;
    void serialize(std::ofstream &ofs) const;
    void deserialize(std::ifstream &ifs);
};
void write_persons_to_file(const std::vector<Person> &persons, const std::filesystem::path &file_path);
std::vector<Person> read_persons_from_file(const std::filesystem::path &file_path);
}