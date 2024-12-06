#include "../common/helper_functions.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

  std::vector<std::vector<char>> mapArea =
      extractLinesFromFile("../data/map_area.txt");

  return 0;
}
