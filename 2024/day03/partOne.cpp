#include "../common/helper_functions.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main() {
  std::fstream myfile("../data/mul_input.txt");

  if (!myfile.is_open()) {
    throw("Error while opening the file!");
  }

  std::string line;
  std::smatch match;
  std::regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
  int i{0};
  long long result{0};
  while (getline(myfile, line)) {
    while (regex_search(line, match, pattern)) {
      auto twoNumsVec = extractIntsFromString(match.str(0));
      line = match.suffix().str();

      result += twoNumsVec[0] * twoNumsVec[1];
    }
  }
  std::cout << "Result: " << result << std::endl;

  myfile.close();
  return 0;
}
