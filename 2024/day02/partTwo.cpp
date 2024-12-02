#include "../common/helper_functions.hpp"
#include <algorithm>
#include <forward_list>
#include <iostream>
#include <string>
#include <vector>

enum class SortType { Ascending, Descending };

bool isReportSafe(const std::vector<int> &report) {

  // Compares previous and current number and checks if based
  // on the type in which they are sorted, the constrains
  // are satisfied
  auto rulesSatisfied = [](int prev, int current, SortType type) -> bool {
    switch (type) {
    case SortType::Ascending:
      if (abs(current - prev) > 3 || (current <= prev)) {
        return false;
      }
      break;
    case SortType::Descending:
      if (abs(current - prev) > 3 || (current >= prev)) {
        return false;
      }
      break;
    }
    return true;
  };

  // Decide the sort type based on the first two numbers
  SortType type =
      (report[1] >= report[0]) ? SortType::Ascending : SortType::Descending;

  // Loop through the report vector and check if two consecutive numbers
  // satisfy the constrains
  int prev{}, current{};
  for (int i{1}; i < report.size(); ++i) {
    prev = report[i - 1];
    current = report[i];
    if (!rulesSatisfied(prev, current, type)) {
      return false;
    }
  }
  return true;
}

int main() {
  std::vector<std::vector<int>> integers2D;
  extractIntegersFromFile("../data/reports.txt", integers2D);

  int numOfSafeReports{0};

  for (const auto &report : integers2D) {
    if (isReportSafe(report)) {
      numOfSafeReports++;
    } else {
      // Check if by removing any single level, it becomes safe
      std::forward_list<int> reportList(report.begin(), report.end());
      auto it = reportList.before_begin();
      for (int i{0}; i < report.size(); ++i) {
        reportList.erase_after(it);
        int erased_val = report[i];
        if (isReportSafe({reportList.begin(), reportList.end()})) {
          numOfSafeReports++;
          break;
        }
        // If it's still unsafe, insert back the erased element and continue
        reportList.insert_after(it, erased_val);
        ++it;
      }
    }
  }

  std::cout << "Number of safe reports: " << numOfSafeReports << std::endl;

  return 0;
}


