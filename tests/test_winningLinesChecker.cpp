#include "gtest/gtest.h"
#include "../src/WinningLinesChecker.hpp"

TEST(WinningLinesCheckerTest, CalculateWinings) {
    std::vector<FruitType> drawnValues = {FruitType::Scatter, FruitType::Scatter, FruitType::Scatter, //first vertical
                                          FruitType::Scatter, FruitType::Scatter, FruitType::Scatter, //second vertical
                                          FruitType::Scatter, FruitType::Scatter, FruitType::Scatter, //...
                                          FruitType::Scatter, FruitType::Scatter, FruitType::Scatter,
                                          FruitType::Scatter, FruitType::Scatter, FruitType::Scatter};
    WinningLinesChecker winningLinesCheckerScatterWins(drawnValues);
    ASSERT_EQ(winningLinesCheckerScatterWins.calculateWinnings(), 5000);

    drawnValues = {FruitType::Cherry, FruitType::Cherry, FruitType::Cherry,
                   FruitType::Watermelon, FruitType::Watermelon, FruitType::Watermelon,
                   FruitType::Cherry, FruitType::Cherry, FruitType::Plum,
                   FruitType::Cherry, FruitType::Watermelon, FruitType::Plum,
                   FruitType::Scatter, FruitType::Lemon, FruitType::Watermelon};
    WinningLinesChecker winningLinesCheckerNoneWins(drawnValues);
    ASSERT_EQ(winningLinesCheckerNoneWins.calculateWinnings(), 0);


    drawnValues = {FruitType::Plum, FruitType::Orange, FruitType::Orange,
                   FruitType::Lemon, FruitType::Plum, FruitType::Watermelon,
                   FruitType::Cherry, FruitType::Cherry, FruitType::Plum,
                   FruitType::Cherry, FruitType::Watermelon, FruitType::Plum,
                   FruitType::Scatter, FruitType::Lemon, FruitType::Watermelon};

    WinningLinesChecker winningLinesChecker(drawnValues);
    ASSERT_EQ(winningLinesChecker.calculateWinnings(), 450);//3 plums in 3 lines

    drawnValues = {FruitType::Scatter, FruitType::Cherry, FruitType::Orange,
                   FruitType::Scatter, FruitType::Plum, FruitType::Cherry,
                   FruitType::Orange, FruitType::Scatter, FruitType::Plum,
                   FruitType::Cherry, FruitType::Plum, FruitType::Orange,
                   FruitType::Plum, FruitType::Grape, FruitType::Grape};

    WinningLinesChecker threeScattersAndTwoCherries(drawnValues);
    ASSERT_EQ(threeScattersAndTwoCherries.calculateWinnings(), 225);
}


