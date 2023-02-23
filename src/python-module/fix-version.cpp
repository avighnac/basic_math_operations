#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc < 2)
    return 0;

  std::ifstream in(argv[1]);
  std::string version;
  std::getline(in, version);

  bool main = version.find("-main") != std::string::npos;

  // 0.0.1-main.116.2397cac
  // Find first occurence of '-'
  version = version.substr(version.find('-') + 1, version.length());
  // main.116.2397cac
  // Find first occurence of '.'
  version = version.substr(version.find('.') + 1, version.length());
  // 116.2397cac
  std::string patch = version.substr(0, version.find('.'));

  std::string new_version;
  if (main) {
    new_version += "1.0." + patch;
  } else
    new_version += "0.0." + patch;

  std::cout << new_version << std::endl;

  // Rewrite version to same file.
  in.close();
  std::ofstream out(argv[1]);
  out << new_version;
  out.close();
}