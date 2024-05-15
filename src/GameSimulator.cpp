#include "GameSimulator.hpp"
#include <iostream>
#include <fstream>
#include <utility>
#include "Definitions.hpp"
#include "FruitTypeHelper.hpp"
#include <iomanip>

GameSimulator::GameSimulator(RandomGenerator rG, uint64_t gamesCount, uint64_t startCredit, std::string creditOutFile)
        : randomGenerator(rG), gamesCount(gamesCount), startCredit(startCredit),
          creditOutFile(std::move(creditOutFile)), wallet(startCredit), drum(randomGenerator) {
    std::cout << "Created simulation with startCredit = " << startCredit << std::endl;
}

GameSimulator::GameSimulator(RandomGenerator rG, uint64_t gamesCount, uint64_t startCredit, std::string creditOutFile,
                             const std::vector<std::vector<FruitType>> &rollersSetting)
        : randomGenerator(rG), gamesCount(gamesCount), startCredit(startCredit),
          creditOutFile(std::move(creditOutFile)), wallet(startCredit), drum(randomGenerator, rollersSetting) {
    std::cout << "Created simulation with startCredit = " << startCredit << std::endl;
    std::cout << "And the rollersSetting is: \n";
    drum.displayContent();
}

//The principal method
void GameSimulator::runSimulation() {

    uint64_t winsSum{0};
    uint64_t hits{0};
    uint64_t playedGames{0}; //  differ from gamesCount in case lost all credits before end of simulation
    int highestWin{0};

    //keeps sum and count for each range
    std::map<std::pair<int, int>, std::pair<uint64_t, uint64_t>> rangeCounters = {
            {{1,    25},    {0, 0}},
            {{26,   100},   {0, 0}},
            {{101,  200},   {0, 0}},
            {{201,  300},   {0, 0}},
            {{301,  1000},  {0, 0}},
            {{1001, 5000},  {0, 0}},
            {{5001, 10000}, {0, 0}}
    };


    std::ofstream outFile(creditOutFile);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }


    for (uint64_t i = 0; i < gamesCount; i++) {
        outFile << wallet.getCredits() << std::endl;

        //only if there is enough credits in the wallet    
        if (wallet.chargeBet()) {
            playedGames++;
            drum.spinRollers(); //one spin is one game

            WinningLinesChecker checker(drum.getRetrievedValues());
            int winningAmount = checker.calculateWinnings();


            wallet.addCredits(winningAmount);

            if (winningAmount > 0) {
                if (winningAmount > highestWin) {
                    highestWin = winningAmount;
                }
                hits++;
                winsSum += winningAmount;

                for (auto &entry: rangeCounters) {
                    auto range = entry.first;
                    if (winningAmount >= range.first && winningAmount <= range.second) {
                        entry.second.first++;
                        entry.second.second += winningAmount;
                        break;
                    }
                }
            }
        }
    }
    outFile.close();

    uint64_t betsSum = playedGames * BET;
    double RTP = static_cast<double>(winsSum) / betsSum * 100;
    double HF = static_cast<double>(hits) / playedGames * 100;

    printReport(winsSum, hits, playedGames, highestWin, rangeCounters, betsSum, RTP, HF);
}

void GameSimulator::printReport(uint64_t winsSum, uint64_t hits, uint64_t playedGames, int highestWin,
                                std::map<std::pair<int, int>, std::pair<uint64_t, uint64_t>> &rangeCounters,
                                uint64_t betsSum, double RTP, double HF) const {
    auto setw11 = std::setw(11);

    std::cout << "\n\n";
    std::cout << "**************************************************************************************************\n";
    std::cout << "*************************************** Simulation report ****************************************\n";
    std::cout << "**************************************************************************************************\n";
    std::cout << "Module: slotGameSimulator\n";
    std::cout << "Number of games: " << gamesCount << "\n";
    std::cout << "Bet of each game: " << BET << "\n";
    std::cout << "Bets sum: " << playedGames << " * " << BET << " = " << betsSum << "\n\n";
    std::cout << "Distribution of wins (percentage of winning games in typical ranges):\n";
    std::cout << std::left << setw11 << "range" << setw11 << "count" << setw11 << "count %"
              << setw11 << "value" << setw11 << "value %" << "\n";

    for (const auto &entry: rangeCounters) {
        auto range = entry.first;
        auto count = entry.second;
        std::cout << std::left << setw11 << (std::to_string(range.first) + "-" + std::to_string(range.second))
                  << setw11 << count.first << setw11 << std::fixed << std::setprecision(2)
                  << static_cast<double>(count.first) / hits * 100 << " " << setw11 << count.second
                  << setw11 << std::fixed << std::setprecision(2)
                  << static_cast<double>(count.second) / winsSum * 100 << "\n";
    }


    std::cout << "\nThe highest win = " << highestWin << "\n";
    std::cout << "RTP = " << RTP << std::endl;
    std::cout << "HF = " << HF << std::endl;
}

uint64_t GameSimulator::getGamesCount() const {
    return gamesCount;
}

uint64_t GameSimulator::getStartCredit() const {
    return startCredit;
}

std::string GameSimulator::getCreditOutFile() const {
    return creditOutFile;
}

std::pair<double, double> GameSimulator::checkRTP(Drum drum) {
    std::vector<FruitType> drawnValues;
    uint64_t betsSum = BET * gamesCount;
    uint64_t winsSum{0};
    uint64_t hits{0};

    for (uint64_t i = 0; i < gamesCount; i++) {
        drum.spinRollers();
        drawnValues = drum.getRetrievedValues();
        WinningLinesChecker checker = WinningLinesChecker(drawnValues);
        auto winningAmount = checker.calculateWinnings();
        if (winningAmount > 0) {
            winsSum += winningAmount;
            hits++;
        }

    }
    double RTP = static_cast<double>(winsSum) / betsSum * 100;
    double HF = static_cast<double>(hits) / gamesCount * 100;
    return std::make_pair(RTP, HF);
}


//A simple genetic algorithm to find the layout on the drum
//RTPtarget, HFtarget, epsilon, gamesCount, numOfFruitsToChange and maxNumOfIterations are the parameters to be manipulated to determine the desired outcome
std::vector<std::vector<FruitType>> GameSimulator::findProperRollersSetup(double RTPtarget, double HFtarget) {
    const uint64_t maxNumOfIterations = 100;
    double epsilon = 1.5;
    gamesCount = 100000; // per generation
    size_t numOfFruitsToChange = 1;

    double RTP{0};
    double HF{0};
    double newGenerationRTP{0};
    double newGenerationHF{0};


    std::vector<std::vector<FruitType>> rollers = drum.getRollers();
    Drum newGenerationDrum = Drum(randomGenerator, rollers);


    int generation = 0;

    auto indicators = checkRTP(drum);
    RTP = indicators.first;
    HF = indicators.second;

    int row;
    int col;
    FruitType fruit;

    //Draw one element on the drum to be changed and then check if it gives closer results to target
    for (auto i = 0; i < maxNumOfIterations; i++) {
        for (auto j = 0; j < numOfFruitsToChange; j++) {
            row = randomGenerator.getRandomInt(0, NUM_ROLLERS - 1);
            col = randomGenerator.getRandomInt(0, ROLLER_SIZE - 1);
            fruit = static_cast<FruitType>(randomGenerator.getRandomInt(0, 7));
            newGenerationDrum.setValue(row, col, fruit);// it may produce rollers with to close scatters,
        }


        indicators = checkRTP(newGenerationDrum);
        newGenerationRTP = indicators.first;
        newGenerationHF = indicators.second;

        // if so it is used to the next generation
        if (std::abs(RTPtarget - newGenerationRTP) < std::abs(RTPtarget - RTP) ||
            (epsilon > std::abs(RTPtarget - newGenerationRTP) &&
             std::abs(HFtarget - newGenerationHF) < std::abs(HFtarget - HF))) {
            drum = newGenerationDrum;
            RTP = newGenerationRTP;
            HF = newGenerationHF;
            generation++;
        }

        std::cout << "iteration = " << i << " generation = " << generation << ", RTP = " << RTP << ", HF = " << HF
                  << std::endl;
    }

    std::cout << "Final setup = \n";
    drum.displayContent(); //If satisfactory result then copy from this log and use for simulations



    return drum.getRollers();
}
