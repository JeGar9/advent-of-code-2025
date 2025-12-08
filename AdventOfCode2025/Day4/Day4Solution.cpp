#include "Day4Solution.h"

#include <unordered_set>
#include <iostream>
#include <ostream>
#include <utility>

using namespace std;

namespace Day4 {

    int solveItem(const std::vector<std::string> &input, size_t n, size_t m, int i, int j) {
        int surroundCount = 0;
        for (int ii = -1; ii <= 1; ++ii) {
            int rowIndex =  i + ii;
            if (rowIndex >= 0 && rowIndex < n) {
                for (int jj = -1; jj <= 1; ++jj) {
                    if (jj != 0 || ii != 0) {
                        int colIndex = j + jj;
                        if (colIndex >= 0 && colIndex < m) {
                            if (input[rowIndex][colIndex] == '@') {
                                ++surroundCount;
                            }
                        }
                    }
                }
            }
        }
        if (surroundCount < 4) {
            return 1;
        }
        return 0;
    }

    std::string solve1(const std::vector<std::string>& input) {
        const size_t n = input.size();
        if (n == 0)
            return "0";

        int counter = 0;
        const size_t m = input[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (input[i][j] == '@') {
                    counter += solveItem(input, n, m, i, j);
                }
            }
        }
        return to_string(counter);
    }

    struct PairHash {
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
        }
    };

    bool solveItemHash(const pair<int,int> & p, unordered_set<pair<int,int>, PairHash> & elements) {
        int surroundCount = 0;
        for (int ii = -1; ii <= 1; ++ii) {
            for (int jj = -1; jj <= 1; ++jj) {
                if (jj != 0 || ii != 0) {
                    int rowIndex =  p.first + ii;
                    int colIndex = p.second + jj;
                    if (elements.find({rowIndex, colIndex}) != elements.end()) {
                        ++surroundCount;
                    }
                }
            }
        }
        return surroundCount < 4;
    }

    std::string solve2(const std::vector<std::string>& input) {
        const size_t n = input.size();
        if (n == 0)
            return "0";
        unordered_set<pair<int,int>, PairHash> elements;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (input[i][j] == '@') {
                    elements.emplace(i, j);
                }
            }
        }

        unordered_set<pair<int,int>, PairHash> elementsToRemove;
        int totalCounter = 0;
        int counter = 0;
        do {
            counter = 0;
            elementsToRemove.clear();
            const size_t m = input[0].size();
            for (const pair<int,int> & p : elements) {
                if (solveItemHash(p, elements)) {
                    elementsToRemove.insert(p);
                }
            }
            counter = elementsToRemove.size();
            for (auto& key : elementsToRemove) {
                elements.erase(key);
            }
            totalCounter += counter;
        } while (counter > 0);
        return to_string(totalCounter);
    }
}