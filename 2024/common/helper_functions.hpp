#include <fstream>
#include <optional>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<char>>
extractLinesFromFile(const std::string &fileToOpen) {
  std::fstream myfile(fileToOpen);
  if (!myfile.is_open()) {
    throw("Error while opening the file!");
  }
  std::string line;
  std::vector<std::vector<char>> outputLines;
  while (getline(myfile, line)) {
    outputLines.push_back({line.begin(), line.end()});
  }
  myfile.close();
  return outputLines;
}

std::optional<std::smatch> findMatch(const std::string &text,
                                     const std::regex &pattern) {
  std::smatch match;
  if (std::regex_search(text, match, pattern)) {
    return match;
  }
  return std::nullopt;
}

std::string reverseString(const std::string &str) {
  return std::string(str.rbegin(), str.rend());
}

std::vector<int> extractIntsFromWord(const std::string &word) {
  std::vector<int> nums;
  std::string wholeNum;
  bool foundNum = false;
  for (int i{0}; i < word.length(); ++i) {
    while (word[i] >= '0' && word[i] <= '9') {
      wholeNum += word[i];
      ++i;
      foundNum = true;
    }
    if (foundNum) {
      nums.push_back(stoi(wholeNum));
      wholeNum.clear();
      foundNum = false;
      --i;
    }
  }
  return nums;
}

std::vector<int> extractIntsFromString(const std::string &sentence) {
  std::vector<int> intsVec;
  std::stringstream ss(sentence);
  std::string temp;
  while (ss >> temp) {
    for (auto num : extractIntsFromWord(temp)) {
      intsVec.push_back(num);
    }
  }
  return intsVec;
}

void extractIntegersFromFile(const std::string &fileToOpen,
                             std::vector<std::vector<int>> &integers) {
  std::fstream myfile(fileToOpen);
  if (!myfile.is_open()) {
    throw("Error while opening the file!");
  }
  std::string line;
  while (getline(myfile, line)) {
    integers.push_back(extractIntsFromString(line));
  }
  myfile.close();
}

std::vector<std::vector<int>>
transpose(const std::vector<std::vector<int>> &matrix) {
  std::vector<std::vector<int>> transposeM(matrix[0].size(),
                                           std::vector<int>(matrix.size()));
  for (int i{0}; i < matrix.size(); ++i) {
    for (int j{0}; j < matrix[i].size(); ++j) {
      transposeM[j][i] = matrix[i][j];
    }
  }

  return std::move(transposeM);
}
