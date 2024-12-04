#include "../common/helper_functions.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

enum Direction {
  right,
  left,
  up,
  down,
  rightDownDiag,
  rightUpDiag,
  leftDownDiag,
  leftUpDiag,
  dirCount
};

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

int checkAllPossibleXmas(const std::vector<std::vector<char>> &matrixofChars,
                         int row, int col) {
  auto checkRight = [&matrixofChars, row, col](int iter, char c) -> bool {
    if (matrixofChars[row][col + iter] == c) {
      return true;
    }
    return false;
  };

  auto checkLeft = [&matrixofChars, row, col](int iter, char c) -> bool {
    if (matrixofChars[row][col - iter] == c) {
      return true;
    }
    return false;
  };

  auto checkUp = [&matrixofChars, row, col](int iter, char c) -> bool {
    if (matrixofChars[row - iter][col] == c) {
      return true;
    }
    return false;
  };

  auto checkDown = [&matrixofChars, row, col](int iter, char c) -> bool {
    if (matrixofChars[row + iter][col] == c) {
      return true;
    }
    return false;
  };

  auto checkRightDownDiag = [&matrixofChars, row, col](int iter,
                                                       char c) -> bool {
    if (matrixofChars[row + iter][col + iter] == c) {
      return true;
    }
    return false;
  };

  auto checkRightUpDiag = [&matrixofChars, row, col](int iter, char c) -> bool {
    if (matrixofChars[row - iter][col + iter] == c) {
      return true;
    }
    return false;
  };

  auto checkLeftDownDiag = [&matrixofChars, row, col](int iter,
                                                      char c) -> bool {
    if (matrixofChars[row + iter][col - iter] == c) {
      return true;
    }
    return false;
  };

  auto checkLeftUpDiag = [&matrixofChars, row, col](int iter, char c) -> bool {
    if (matrixofChars[row - iter][col - iter] == c) {
      return true;
    }
    return false;
  };

  int xmasFound = 0;
  int rowMax = matrixofChars.size();
  int colMax = matrixofChars[row].size();
  std::string restStringToFind = "MAS";
  int lenStringToFind = restStringToFind.length();
  std::vector<bool> doLettersExistSoFar(dirCount, true);

  for (int i{1}; i <= lenStringToFind; ++i) {
    if (col + lenStringToFind < colMax && doLettersExistSoFar[right]) {
      doLettersExistSoFar[right] = checkRight(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[right] = false;
    }
    if (row + lenStringToFind < rowMax && doLettersExistSoFar[down]) {
      doLettersExistSoFar[down] = checkDown(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[down] = false;
    }
    if (col - lenStringToFind >= 0 && doLettersExistSoFar[left]) {
      doLettersExistSoFar[left] = checkLeft(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[left] = false;
    }
    if (row - lenStringToFind >= 0 && doLettersExistSoFar[up]) {
      doLettersExistSoFar[up] = checkUp(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[up] = false;
    }
    if (col + lenStringToFind < colMax && row + lenStringToFind < rowMax &&
        doLettersExistSoFar[rightDownDiag]) {
      doLettersExistSoFar[rightDownDiag] =
          checkRightDownDiag(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[rightDownDiag] = false;
    }
    if (col + lenStringToFind < colMax && row - lenStringToFind >= 0 &&
        doLettersExistSoFar[rightUpDiag]) {
      doLettersExistSoFar[rightUpDiag] =
          checkRightUpDiag(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[rightUpDiag] = false;
    }
    if (col - lenStringToFind >= 0 && row + lenStringToFind < rowMax &&
        doLettersExistSoFar[leftDownDiag]) {
      doLettersExistSoFar[leftDownDiag] =
          checkLeftDownDiag(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[leftDownDiag] = false;
    }
    if (col - lenStringToFind >= 0 && row - lenStringToFind >= 0 &&
        doLettersExistSoFar[leftUpDiag]) {
      doLettersExistSoFar[leftUpDiag] =
          checkLeftUpDiag(i, restStringToFind[i - 1]);
    } else {
      doLettersExistSoFar[leftUpDiag] = false;
    }
  }
  for (auto check : doLettersExistSoFar) {
    if (check) {
      ++xmasFound;
    }
  }
  return xmasFound;
}

int main() {
  std::vector<std::vector<char>> matrixofChars;
  extractCharsFromFile("../data/xmas.txt", matrixofChars);

  int totalNumOfXMAS = 0;
  for (int row{0}; row < matrixofChars.size(); ++row) {
    for (int col{0}; col < matrixofChars[row].size(); ++col) {
      if (matrixofChars[row][col] == 'X') {
        totalNumOfXMAS += checkAllPossibleXmas(matrixofChars, row, col);
      }
    }
  }
  std::cout << "Total number of xmas words is: " << totalNumOfXMAS << std::endl;

  return 0;
}
