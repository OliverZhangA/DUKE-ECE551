#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sort(std::istream & in) {
  std::string line;
  std::vector<std::string> lines;
  while (getline(in, line)) {
    lines.push_back(line);
  }
  if (!in.good() && !in.eof()) {
    std::cerr << "fail to read!" << std::endl;
    exit(EXIT_FAILURE);
  }
  std::sort(lines.begin(), lines.end());
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::cout << *it << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::ifstream in(argv[1]);
    sort(std::cin);
  }
  else if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::ifstream in(argv[i]);
      sort(in);
      in.close();
    }
  }
  return EXIT_SUCCESS;
}
