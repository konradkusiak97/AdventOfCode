#include "../common/helper_functions.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>
#include <utility>

void extractCharsFromFile(const std::string &fileToOpen,
                          std::vector<std::vector<char>> &data2D) {
  std::fstream myfile(fileToOpen);

  if (!myfile.is_open()) {
    throw("Error while opening the file!");
  }
  std::string line;
  while (getline(myfile, line)) {
    std::vector vectorOfChars(line.begin(), line.end());
    data2D.push_back(vectorOfChars);
  }
  myfile.close();
}

bool checkX_MAS(const std::vector<std::vector<char>> &matrixofChars, int row,
                int col) {

  int rowMax = matrixofChars.size();
  int colMax = matrixofChars[row].size();
  std::string targetChars = "MS";

  if (!(row - 1 >= 0 && col - 1 >= 0 && row + 1 < rowMax && col + 1 < colMax)) {
    return false;
  }

  char upLeft = matrixofChars[row - 1][col - 1];
  char downRight = matrixofChars[row + 1][col + 1];
  char downLeft = matrixofChars[row + 1][col - 1];
  char upRight = matrixofChars[row - 1][col + 1];

  if (targetChars.find(upLeft) == std::string::npos ||
      targetChars.find(upRight) == std::string::npos ||
      targetChars.find(downLeft) == std::string::npos ||
      targetChars.find(downRight) == std::string::npos) {
    return false;
  }

  if ((upLeft == 'M' && downRight == 'S') &&
          (upRight == 'M' && downLeft == 'S') ||
      (upLeft == 'M' && downRight == 'S') &&
          (upRight == 'S' && downLeft == 'M') ||
      (upLeft == 'S' && downRight == 'M') &&
          (upRight == 'S' && downLeft == 'M') ||
      (upLeft == 'S' && downRight == 'M') &&
          (upRight == 'M' && downLeft == 'S')) {
    return true;
  }
  return false;
}

int main() {
  std::vector<std::vector<char>> matrixofChars;
  extractCharsFromFile("../data/xmas.txt", matrixofChars);

  int totalNumOfX_MAS = 0;
  for (int row{0}; row < matrixofChars.size(); ++row) {
    for (int col{0}; col < matrixofChars[row].size(); ++col) {
      if (matrixofChars[row][col] == 'A') {
        if (checkX_MAS(matrixofChars, row, col)) {
          ++totalNumOfX_MAS;
        };
      }
    }
  }

  std::cout << "Total number of x-mas words is: " << totalNumOfX_MAS
            << std::endl;
  return 0;
}
