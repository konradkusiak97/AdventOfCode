#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void extractIntegersFromFile(const std::string &fileToOpen,
                             std::vector<std::vector<int>> &integers) {

  std::fstream myfile(fileToOpen);

  if (!myfile.is_open()) {
    throw("Error while opening the file!");
  }

  std::string line;
  while (getline(myfile, line)) {
    std::stringstream ss(line);
    std::string temp;
    std::vector<int> tempVec;
    while (ss >> temp) {
      // Check if it's an integer
      if (temp[0] >= '0' && temp[0] <= '9') {
        tempVec.push_back(stoi(temp));
      }
    }
    integers.push_back(tempVec);
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

