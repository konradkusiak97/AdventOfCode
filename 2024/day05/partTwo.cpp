#include "../common/helper_functions.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

bool isInOrder(std::vector<int> &update,
               std::unordered_map<int, std::vector<int>> &pageRules) {
  for (int i{0}; i < update.size(); ++i) {
    int currentNum = update[i];
    const auto &succVec = pageRules[currentNum];
    for (int j{i + 1}; j < update.size(); ++j) {
      if (std::find(succVec.begin(), succVec.end(), update[j]) ==
          succVec.end()) {
        return false;
      }
    }
  }
  return true;
}

bool sortIfNotInOrder(std::vector<int> &update,
                      std::unordered_map<int, std::vector<int>> &pageRules) {
  if (isInOrder(update, pageRules)) {
    return false;
  }
  std::sort(update.begin(), update.end(), [&pageRules](int first, int sec) {
    const auto &succVec = pageRules[first];
    return std::find(succVec.begin(), succVec.end(), sec) != succVec.end();
  });
  return true;
}

int main() {
  std::fstream myfile("../data/pageUpdate.txt");

  if (!myfile.is_open()) {
    throw("Error while opening the file!");
  }

  std::string line;
  std::vector<int> rightCol;
  std::vector<int> leftCol;
  std::vector<std::vector<int>> updates;

  // Read the input
  while (std::getline(myfile, line)) {
    if (line.find('|') != std::string::npos) {
      auto pageRulePair = extractIntsFromWord(line);
      leftCol.push_back(pageRulePair[0]);
      rightCol.push_back(pageRulePair[1]);
    } else {
      auto updateVec = extractIntsFromWord(line);
      if (updateVec.size()) {
        updates.push_back(updateVec);
      }
    }
  }

  myfile.close();

  // Each page rule number and a vector of its successors
  std::unordered_map<int, std::vector<int>> pageRules{};

  for (int i{0}; i < leftCol.size(); ++i) {
    auto predecessor = leftCol[i];
    auto successor = rightCol[i];

    if (pageRules.find(predecessor) != pageRules.end()) {
      pageRules[predecessor].push_back(successor);
    } else {
      pageRules[predecessor] = {successor};
    }
  }

  std::vector<int> updatesInOrder;
  for (int i{0}; i < updates.size(); ++i) {
    if (sortIfNotInOrder(updates[i], pageRules)) {
      updatesInOrder.push_back(i);
    }
  }

  int sumOfMiddles{0};
  for (auto idx : updatesInOrder) {
    auto middleIdx = updates[idx].size() / 2;
    sumOfMiddles += updates[idx][middleIdx];
  }

  std::cout << "Middle sum is: " << sumOfMiddles;

  return 0;
}
