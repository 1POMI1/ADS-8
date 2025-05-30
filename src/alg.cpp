// Copyright 2021 NNTU-CS
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include <iostream>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "File error! Cannot open: " << filename << std::endl;
    return;
  }

  std::map<std::string, int> freq;
  std::string word;
  char ch;

  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(ch);
    } else if (!word.empty()) {
      freq[word]++;
      word.clear();
    }
  }

  if (!word.empty()) {
    freq[word]++;
  }

  file.close();

  std::vector<std::pair<std::string, int>> sorted_words(freq.begin(), freq.end());

  std::function<void(int, int)> insertBalanced = [&](int left, int right) {
    if (left > right) return;
    int mid = left + (right - left) / 2;
    for (int i = 0; i < sorted_words[mid].second; ++i) {
      tree.insert(sorted_words[mid].first);
    }
    insertBalanced(left, mid - 1);
    insertBalanced(mid + 1, right);
  };

  insertBalanced(0, sorted_words.size() - 1);
}
