#include "pod_types.h"

//Introduce writing objects later on when we have covered custom types.
//This is just so we have the subject covered all together.
//We show how to handle a single object and several objects in a collection.

#include <fmt/format.h>

namespace pod_types {
bool write_pod(const std::filesystem::path &filename, const PODType &pod)
{
  std::ofstream out_file(filename, std::ios::binary);
  if (!out_file) { return false; }
  out_file.write(reinterpret_cast<const char *>(&pod), sizeof(PODType));
  return out_file.good();
}

// Function to read POD from a binary file (returns bool for success)
bool read_pod(const std::filesystem::path &filename, PODType &pod)
{
  std::ifstream in_file(filename, std::ios::binary);
  if (!in_file) { return false; }
  in_file.read(reinterpret_cast<char *>(&pod), sizeof(PODType));
  return in_file.good();
}

// Function to write a vector of PODType objects to a file
bool write_pod_vector(const std::filesystem::path &file_path,
  const std::vector<pod_types::PODType> &pod_vector)
{
  std::ofstream out_file(file_path, std::ios::binary);
  if (!out_file) {
    fmt::print("Failed to open file for writing.\n");
    return false;
  }

  for (const auto &pod : pod_vector) {
    out_file.write(reinterpret_cast<const char *>(&pod), sizeof(pod_types::PODType));
  }

  if (!out_file.good()) {
    fmt::print("Failed to write PODType objects to file.\n");
    return false;
  }

  out_file.close();
  return true;
}

// Function to read a vector of PODType objects from a file
bool read_pod_vector(const std::filesystem::path &file_path,
  std::vector<pod_types::PODType> &pod_vector)
{
  std::ifstream in_file(file_path, std::ios::binary);
  if (!in_file) {
    fmt::print("Failed to open file for reading.\n");
    return false;
  }

  pod_types::PODType read_pod;
  while (in_file.read(reinterpret_cast<char *>(&read_pod), sizeof(pod_types::PODType))) {
    pod_vector.push_back(read_pod);
  }

  if (!in_file.eof() && !in_file.good()) {
    fmt::print("Failed to read PODType objects from file.\n");
    return false;
  }

  in_file.close();
  return true;
}

}// namespace pod_types