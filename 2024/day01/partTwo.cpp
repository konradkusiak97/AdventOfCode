#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

  string strNumbers;
  stringstream ss;
  vector<vector<int>> integers2D(2);

  while (getline(myfile, strNumbers)) {
    extractIntegers(strNumbers, integers2D);
  }

  myfile.close();

  unordered_multiset<int> leftCol(integers2D[0].begin(), integers2D[0].end());
  unordered_set<int> leftColUnique(integers2D[0].begin(), integers2D[0].end());

  unordered_multiset<int> rightCol(integers2D[1].begin(), integers2D[1].end());

  int similarityScore{0};

  for (auto entry : leftColUnique) {
    similarityScore += entry * leftCol.count(entry) * rightCol.count(entry);
  }

  std::cout << "Similarity score is: " << similarityScore << std::endl;

  return 0;
}
