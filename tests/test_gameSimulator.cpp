#include "gtest/gtest.h"
#include "../src/GameSimulator.hpp"


TEST(GameSimulatorTest, simulatorTest) {
    RandomGenerator randomGen;
    uint64_t gamesCount = 10;
    uint64_t startCredit = 10000;
    std::string creditOutFile = "file.txt";

    GameSimulator simulator(randomGen, gamesCount, startCredit, creditOutFile);

    EXPECT_EQ(simulator.getGamesCount(), gamesCount);
    EXPECT_EQ(simulator.getStartCredit(), startCredit);
    EXPECT_EQ(simulator.getCreditOutFile(), creditOutFile);


    simulator.runSimulation();// Assuming that the simulation runs without errors
}

TEST(GameSimulatorTest, FindProperRollersSetupTest) {
    RandomGenerator randomGen;
    uint64_t gamesCount = 10;
    uint64_t startCredit = 10000;
    std::string creditOutFile = "file.txt";

    GameSimulator simulator(randomGen, gamesCount, startCredit, creditOutFile);
    auto rollersSetup = simulator.findProperRollersSetup(96.0, 30.0);
    ASSERT_TRUE(!rollersSetup.empty());
}