#pragma once

#include "FruitType.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>

class WinningLinesChecker {
public:
    WinningLinesChecker(std::vector<FruitType> drawnValues);

    int calculateWinnings() const;

private:
    int calculateScatterWinnings() const;

    int calculateLineWinnings() const;

    template<typename... Indices>
    std::vector<FruitType> getLine(Indices... indices) const;

    std::vector<FruitType> getLineForIndex(int &index) const;

    int countScatterOccurrences() const;

    size_t countConsecutiveSameElements(const std::vector<FruitType> &line) const;

    std::vector<FruitType> drawnValues;
    std::vector<std::vector<FruitType>> lines; // 20 winning lines
    std::map<std::pair<FruitType, size_t>, int> payouts; //values of the winnings for the pairs - fruit, occurrences
};

/*
Structure:
5 rollers vertically with a length of 20 characters each,
we only see 3 drawn "fruits: from each roller (total 15):
-----------------------
| 0 | 3 | 6 |  9 | 12 |
-----------------------
| 1 | 4 | 7 | 10 | 13 |
-----------------------
| 2 | 5 | 8 | 11 | 14 |
-----------------------

Winning lines :

Line  1 : [1, 4, 7, 10, 13]
Line  2 : [0, 3, 6, 9, 12]
Line  3 : [2, 5, 8, 11, 14]
Line  4 : [1, 4, 6, 10, 13]
Line  5 : [0, 4, 8, 10, 12]
Line  6 : [2, 4, 6, 10, 14]
Line  7 : [1, 3, 7, 9, 13]
Line  8 : [1, 5, 7, 11, 13]
Line  9 : [0, 3, 7, 11, 14]
Line 10 : [2, 5, 7, 9, 12]
Line 11 : [2, 4, 6, 10, 13]
Line 12 : [2, 4, 6, 9, 12]
Line 13 : [0, 4, 8, 11, 14]
Line 14 : [0, 4, 8, 10, 13]
Line 15 : [0, 4, 6, 10, 12]
Line 16 : [2, 4, 8, 10, 14]
Line 17 : [0, 3, 7, 10, 13]
Line 18 : [2, 5, 7, 10, 13]
Line 19 : [2, 5, 8, 10, 12]
Line 20 : [0, 3, 6, 10, 14]

*/