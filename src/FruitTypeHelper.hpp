#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <vector>
#include "FruitType.hpp"
#include <set>
#include "Definitions.hpp"

class FruitTypeHelper {
public:
    static std::string toString(FruitType fruit) {
        switch (fruit) {
            case FruitType::Scatter:
                return "S";
            case FruitType::Cherry:
                return "C";
            case FruitType::Lemon:
                return "L";
            case FruitType::Orange:
                return "O";
            case FruitType::Plum:
                return "P";
            case FruitType::Grape:
                return "G";
            case FruitType::Watermelon:
                return "W";
            case FruitType::Seven:
                return "7";
        }
    }

    static FruitType charToEnum(char c) {
        static const std::map<char, FruitType> charMap{
                {'S', FruitType::Scatter},
                {'C', FruitType::Cherry},
                {'L', FruitType::Lemon},
                {'O', FruitType::Orange},
                {'P', FruitType::Plum},
                {'G', FruitType::Grape},
                {'W', FruitType::Watermelon},
                {'7', FruitType::Seven}
        };
        auto it = charMap.find(c);
        if (it != charMap.end()) {
            return it->second;
        }
        std::cerr << "Value out of range [0, 7]." << std::endl;
        return FruitType::Scatter;
    }

    static std::vector<std::vector<FruitType>> decodeFruits(const std::string &code) {
        std::vector<std::vector<FruitType>> fruits;
        std::istringstream iss(code);
        std::string line;
        while (std::getline(iss, line)) {
            if (!line.empty()) {
                std::vector<FruitType> series;
                for (char c: line) {
                    if (!isspace(c)) {
                        series.push_back(charToEnum(c));
                    }
                }
                fruits.push_back(series);
            }
        }
        return fruits;
    }

    static std::vector<FruitType> changeIndexingByRowsIntoByColumns(const std::vector<FruitType> &byRowsVec) {
        const int numRows = 3;
        const int numCols = 5;

        std::vector<FruitType> byColumnsVec(numRows * numCols);

        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                int indexByRows = row * numCols + col;
                int indexByCols = col * numRows + row;
                byColumnsVec[indexByCols] = byRowsVec[indexByRows];
            }
        }

        return byColumnsVec;
    }

    static bool isRollersSetupValid(const std::vector<std::vector<FruitType>> &rollersSetup) {
        for (const auto &row: rollersSetup) {
            std::set<size_t> scatterIndices;

            for (size_t i = 0; i < row.size(); ++i) {
                if (row[i] == FruitType::Scatter) {
                    scatterIndices.insert(i);
                }
            }
            if (scatterIndices.size() > 1) {
                // Check that the differences between consecutive indexes are at least equal to 2
                size_t prevIndex = std::numeric_limits<size_t>::max();
                for (auto it = scatterIndices.begin(); it != scatterIndices.end(); ++it) {
                    if (it != scatterIndices.begin() && (*it - prevIndex) < 3) {
                        std::cerr << "Scatters are too close!" << std::endl;
                        return false;
                    }
                    prevIndex = *it;
                }

                // Check if the difference between the first and last index is less than 18 the beginning and end of roller meet
                size_t firstIndex = *scatterIndices.begin();
                size_t lastIndex = *scatterIndices.rbegin();
                if ((lastIndex - firstIndex) >= (ROLLER_SIZE - 2)) {
                    std::cerr << "Scatters are too close!" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }
};

inline std::ostream &operator<<(std::ostream &os, FruitType fruit) {
    return os << FruitTypeHelper::toString(fruit);
}

