#pragma once

#include <string>
#include <vector>
#include "Wallet.hpp"
#include "Drum.hpp"
#include "WinningLinesChecker.hpp"
#include "RandomGenerator.hpp"
#include "FruitType.hpp"

class GameSimulator {
public:
    GameSimulator(
            RandomGenerator rG,
            uint64_t gamesCount,
            uint64_t startCredit,
            std::string creditOutFile); // with random drum setup

    GameSimulator(
            RandomGenerator rG,
            uint64_t gamesCount,
            uint64_t startCredit,
            std::string creditOutFile,
            const std::vector<std::vector<FruitType>> &rollersSetting); //with given drum setup

    void runSimulation();

    uint64_t getGamesCount() const;

    uint64_t getStartCredit() const;

    std::string getCreditOutFile() const;

    std::vector<std::vector<FruitType>> findProperRollersSetup(double RTPtarget = 96.00, double HFtarget = 30.00);

private:
    std::pair<double, double> checkRTP(Drum drum);// no wallet, no write to file

    RandomGenerator randomGenerator;
    uint64_t gamesCount;
    uint64_t startCredit;
    std::string creditOutFile;

    Wallet wallet;
    Drum drum;

    void printReport(uint64_t winsSum, uint64_t hits, uint64_t playedGames, int highestWin,
                     std::map<std::pair<int, int>, std::pair<uint64_t, uint64_t>> &rangeCounters, uint64_t betsSum,
                     double RTP, double HF) const;
};
