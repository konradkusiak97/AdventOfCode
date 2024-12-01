#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
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

  fstream myfile("input.txt");

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

  unordered_map<int, int> leftInRightCount(integers2D[1].begin(),
                                           integers2D[1].end(), 0);

  return 0;
}
