#include "WinningLinesChecker.hpp"
#include <functional>
#include "Definitions.hpp"


extern std::map<std::pair<FruitType, size_t>, int> fruitCounter;

WinningLinesChecker::WinningLinesChecker(std::vector<FruitType> drawnValues) : drawnValues(drawnValues) {
    for (int i = 0; i < 20; ++i) {
        lines.push_back(getLineForIndex(i));
    }
};


int WinningLinesChecker::calculateWinnings() const {
    int result = calculateScatterWinnings();
    result += calculateLineWinnings();
    return result;
}


int WinningLinesChecker::calculateScatterWinnings() const {
    int numOfScatter = countScatterOccurrences();
    std::pair<FruitType, size_t> scatterKey = {FruitType::Scatter, numOfScatter};
    auto scatterPayout = PAYOUTS.find(scatterKey);
    auto payoutValue = scatterPayout->second;
    if (payoutValue) {
        fruitCounter[scatterKey]++;
    }
    return payoutValue;
}

//For each of the 20 lines, I check how many fruits starting from the first are repeated
int WinningLinesChecker::calculateLineWinnings() const {
    int totalWinnings = 0;
    for (const auto &line: lines) {
        if (!line.empty()) {
            FruitType fruit = line[0];
            size_t consecutiveCount = countConsecutiveSameElements(line);
            std::pair<FruitType, size_t> fruitKey = {fruit, consecutiveCount};
            //takes the appropriate value of the winnings from the hardcoded map
            auto payout = PAYOUTS.find({fruit, consecutiveCount});
            if (payout != PAYOUTS.end()) {
                auto payoutValue = payout->second;
                if (payoutValue) {
                    fruitCounter[fruitKey]++;
                    totalWinnings += payoutValue;
                }
            } else {
                std::cerr << "WinningLinesChecker::calculateScatterWinnings: Warning payout not found" << std::endl;
            }
        }
    }
    return totalWinnings;
}

template<typename... Indices>
std::vector<FruitType> WinningLinesChecker::getLine(Indices... indices) const {
    std::vector<FruitType> line;

    auto addIndexToLine = [&](int index) {
        if (index >= 0 && index < drawnValues.size()) {
            line.push_back(std::ref(drawnValues[index]));
        }
    };

    (addIndexToLine(indices), ...);//C++17


    if (line.size() != NUM_ROLLERS) {
        std::cerr << "Error: Incorrect number of elements in the line vector." << std::endl;
    }

    return line;
}

std::vector<FruitType> WinningLinesChecker::getLineForIndex(int &index) const {
    switch (index) {
        case 0:
            return getLine(1, 4, 7, 10, 13);
        case 1:
            return getLine(0, 3, 6, 9, 12);
        case 2:
            return getLine(2, 5, 8, 11, 14);
        case 3:
            return getLine(1, 4, 6, 10, 13);
        case 4:
            return getLine(0, 4, 8, 10, 12);
        case 5:
            return getLine(2, 4, 6, 10, 14);
        case 6:
            return getLine(1, 3, 7, 9, 13);
        case 7:
            return getLine(1, 5, 7, 11, 13);
        case 8:
            return getLine(0, 3, 7, 11, 14);
        case 9:
            return getLine(2, 5, 7, 9, 12);
        case 10:
            return getLine(2, 4, 6, 10, 13);
        case 11:
            return getLine(2, 4, 6, 9, 12);
        case 12:
            return getLine(0, 4, 8, 11, 14);
        case 13:
            return getLine(0, 4, 8, 10, 13);
        case 14:
            return getLine(0, 4, 6, 10, 12);
        case 15:
            return getLine(2, 4, 8, 10, 14);
        case 16:
            return getLine(0, 3, 7, 10, 13);
        case 17:
            return getLine(2, 5, 7, 10, 13);
        case 18:
            return getLine(2, 5, 8, 10, 12);
        case 19:
            return getLine(0, 3, 6, 10, 14);
        default:
            return std::vector<FruitType>();
    }
}

int WinningLinesChecker::countScatterOccurrences() const {
    int count = 0;
    for (const FruitType &fruit: drawnValues) {
        if (fruit == FruitType::Scatter) {
            count++;
        }
    }
    return count;
}

size_t WinningLinesChecker::countConsecutiveSameElements(const std::vector<FruitType> &line) const {
    size_t consecutiveCount = 1;
    for (size_t i = 0; i < line.size() - 1; ++i) {
        if (line[i] == line[i + 1]) {
            ++consecutiveCount;
        } else {
            return consecutiveCount;
        }
    }
    return consecutiveCount;
}