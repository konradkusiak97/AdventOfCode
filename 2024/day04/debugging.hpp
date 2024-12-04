
// for (int row{0}; row < matrixofChars.size(); ++row) {
//   for (int col{0}; col < matrixofChars[row].size(); ++col) {
//     if (xmas_indieces.find({row, col}) != xmas_indieces.end()) {
//       std::cout << matrixofChars[row][col];
//     } else {
//       std::cout << '.';
//     }
//   }
//   std::cout << std::endl;
// }
//
// if (xmasFound > 0) {
//   for (int i{0}; i < doLettersExistSoFar.size(); ++i) {
//     if (doLettersExistSoFar[i]) {
//       addIndicestoXmasSet(i);
//     }
//   }
// }
struct pair_hash {
  template <typename T1, typename T2>
  std::size_t operator()(const std::pair<T1, T2> &p) const {
    std::size_t h1 = std::hash<T1>()(p.first);
    std::size_t h2 = std::hash<T2>()(p.second);
    return h1 ^ (h2 << 1); // Combine the two hash values
  }
};

std::unordered_set<std::pair<int, int>, pair_hash> xmas_indieces;
auto addIndicestoXmasSet = [&](int i) {
  if (i == right) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row, col + j});
    }
  }
  if (i == left) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row, col - j});
    }
  }
  if (i == up) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row - j, col});
    }
  }
  if (i == down) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row + j, col});
    }
  }
  if (i == rightDownDiag) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row + j, col + j});
    }
  }
  if (i == rightUpDiag) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row - j, col + j});
    }
  }
  if (i == leftDownDiag) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row + j, col - j});
    }
  }
  if (i == leftUpDiag) {
    for (int j{0}; j < lenStringToFind + 1; ++j) {
      xmas_indieces.insert({row - j, col - j});
    }
  }
};
