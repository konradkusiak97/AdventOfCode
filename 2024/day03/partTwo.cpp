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
  std::regex mul("mul\\(\\d{1,3},\\d{1,3}\\)");
  std::regex dont("\\)\\(t'nod");
  std::regex doPattern("\\)\\(od");
  int i{0};
  long long result{0};
  bool doMul = true;
  while (getline(myfile, line)) {
    while (std::regex_search(line, match, mul)) {
      auto twoNumsVec = extractIntsFromString(match.str(0));

      auto prefixToMul = reverseString(match.prefix().str());
      auto matchDont = findMatch(prefixToMul, dont);
      auto matchDo = findMatch(prefixToMul, doPattern);
      line = match.suffix().str();

      if (matchDont && matchDo) {
        if (matchDo->position() < matchDont->position()) {
          doMul = true;
        } else {
          doMul = false;
        }
      } else if (matchDo) {
        doMul = true;
      } else if (matchDont) {
        doMul = false;
      }

      if (doMul) {
        result += twoNumsVec[0] * twoNumsVec[1];
      }
    }
  }
  std::cout << "Result: " << result << std::endl;

  myfile.close();
  return 0;
}
