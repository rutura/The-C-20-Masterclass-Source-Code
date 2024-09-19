#pragma once


#include <fstream>
#include <filesystem>
#include <vector>
namespace pod_types {
struct PODType {
    int id;
    double value;
};
// Function to write POD to a binary file (returns bool for success)
bool write_pod(const std::filesystem::path &filename, const PODType &pod);
// Function to read POD from a binary file (returns bool for success)
bool read_pod(const std::filesystem::path &filename, PODType &pod);
// Function to write a vector of PODType objects to a file
bool write_pod_vector(const std::filesystem::path &file_path,
  const std::vector<pod_types::PODType> &pod_vector);
// Function to read a vector of PODType objects from a file
bool read_pod_vector(const std::filesystem::path &file_path,
  std::vector<pod_types::PODType> &pod_vector);
}