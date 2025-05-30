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

  std::string word;
  char ch;

  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;
  tree.getAllWords(words);

  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });

  std::ofstream out("result/freq.txt");
  if (!out.is_open()) {
    std::cerr << "Cannot open result/freq.txt" << std::endl;
    return;
  }

  for (const auto& [word, count] : words) {
    std::cout << word << ": " << count << std::endl;
    out << word << ": " << count << std::endl;
  }

  out.close();
}
