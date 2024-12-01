#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void extractIntegers(string sentence, vector<vector<int>> &integers) {

  stringstream ss(sentence);
  string temp;
  bool isFirstNumber{true};
  while (ss >> temp) {
    if (temp[0] >= '0' && temp[0] <= '9') {
      if (isFirstNumber) {
        integers[0].push_back(stoll(temp));
        isFirstNumber = false;
      } else {
        integers[1].push_back(stoll(temp));
        isFirstNumber = true;
      }
    }
  }
}

int main() {

  fstream myfile("../data/input.txt");

  if (!myfile.is_open()) {
    cout << "Error while opening the file!";
    return 1;
  }

  string strLine;
  stringstream ss;
  vector<vector<int>> integers2D(2);

  while (getline(myfile, strLine)) {
    extractIntegers(strLine, integers2D);
  }

  myfile.close();

  std::sort(integers2D[0].begin(), integers2D[0].end());
  std::sort(integers2D[1].begin(), integers2D[1].end());

  int totalDistance{0};
  for (int i{0}; i < integers2D[0].size(); ++i) {
    totalDistance += abs(integers2D[0][i] - integers2D[1][i]);
  }

  std::cout << "Total distance is: " << totalDistance << std::endl;

  return 0;
}
