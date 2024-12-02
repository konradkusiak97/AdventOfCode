#include "../common/helper_functions.hpp"
#include <iostream>
#include <unordered_set>
#include <vector>

int main() {

  std::vector<std::vector<int>> integers2D;
  extractIntegersFromFile("../data/input.txt", integers2D);
  auto transposedInts2D = transpose(integers2D);

  std::unordered_multiset<int> leftCol(transposedInts2D[0].begin(),
                                       transposedInts2D[0].end());
  std::unordered_set<int> leftColUnique(transposedInts2D[0].begin(),
                                        transposedInts2D[0].end());
  std::unordered_multiset<int> rightCol(transposedInts2D[1].begin(),
                                        transposedInts2D[1].end());

  int similarityScore{0};

  for (auto entry : leftColUnique) {
    similarityScore += entry * leftCol.count(entry) * rightCol.count(entry);
  }

  std::cout << "Similarity score is: " << similarityScore << std::endl;

  return 0;
}
