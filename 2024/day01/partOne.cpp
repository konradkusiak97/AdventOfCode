#include "../common/helper_functions.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  std::vector<std::vector<int>> integers2D;
  extractIntegersFromFile("../data/input.txt", integers2D);
  auto transposedInts2D = transpose(integers2D);

  std::sort(transposedInts2D[0].begin(), transposedInts2D[0].end());
  std::sort(transposedInts2D[1].begin(), transposedInts2D[1].end());

  int totalDistance{0};
  for (int i{0}; i < transposedInts2D[0].size(); ++i) {
    totalDistance += abs(transposedInts2D[0][i] - transposedInts2D[1][i]);
  }

  std::cout << "Total distance is: " << totalDistance << std::endl;

  return 0;
}
