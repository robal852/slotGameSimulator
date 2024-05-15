#include "gtest/gtest.h"
#include "../src/FruitTypeHelper.hpp"

TEST(FruitTypeHelperTest, ToStringTest) {
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Scatter), "S");
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Cherry), "C");
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Lemon), "L");
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Orange), "O");
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Plum), "P");
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Grape), "G");
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Watermelon), "W");
    EXPECT_EQ(FruitTypeHelper::toString(FruitType::Seven), "7");
}

TEST(FruitTypeHelperTest, OutputOperatorTest) {
    std::stringstream ss;
    ss << FruitType::Scatter;
    EXPECT_EQ(ss.str(), "S");

    ss.str("");
    ss << FruitType::Cherry;
    EXPECT_EQ(ss.str(), "C");

    ss.str("");
    ss << FruitType::Lemon;
    EXPECT_EQ(ss.str(), "L");

    ss.str("");
    ss << FruitType::Orange;
    EXPECT_EQ(ss.str(), "O");

    ss.str("");
    ss << FruitType::Plum;
    EXPECT_EQ(ss.str(), "P");

    ss.str("");
    ss << FruitType::Grape;
    EXPECT_EQ(ss.str(), "G");

    ss.str("");
    ss << FruitType::Watermelon;
    EXPECT_EQ(ss.str(), "W");

    ss.str("");
    ss << FruitType::Seven;
    EXPECT_EQ(ss.str(), "7");
}

TEST(FruitTypeHelperTest, CharToEnumTest) {
    EXPECT_EQ(FruitTypeHelper::charToEnum('S'), FruitType::Scatter);
    EXPECT_EQ(FruitTypeHelper::charToEnum('C'), FruitType::Cherry);
    EXPECT_EQ(FruitTypeHelper::charToEnum('L'), FruitType::Lemon);
    EXPECT_EQ(FruitTypeHelper::charToEnum('O'), FruitType::Orange);
    EXPECT_EQ(FruitTypeHelper::charToEnum('P'), FruitType::Plum);
    EXPECT_EQ(FruitTypeHelper::charToEnum('G'), FruitType::Grape);
    EXPECT_EQ(FruitTypeHelper::charToEnum('W'), FruitType::Watermelon);
    EXPECT_EQ(FruitTypeHelper::charToEnum('7'), FruitType::Seven);
}

TEST(FruitTypeHelperTest, DecodeFruitsTest) {
    std::string code = "CLWO\nPGS    7";
    std::vector<std::vector<FruitType>> expected{
            {FruitType::Cherry, FruitType::Lemon, FruitType::Watermelon, FruitType::Orange},
            {FruitType::Plum,   FruitType::Grape, FruitType::Scatter,    FruitType::Seven}
    };
    EXPECT_EQ(FruitTypeHelper::decodeFruits(code), expected);
}

TEST(FruitTypeHelperTest, ChangeIndexingByRowsIntoByColumnsTest) {
    std::vector<FruitType> byRowsVec{
            FruitType::Cherry, FruitType::Lemon, FruitType::Watermelon, FruitType::Orange, FruitType::Scatter,
            FruitType::Plum, FruitType::Grape, FruitType::Scatter, FruitType::Seven, FruitType::Lemon,
            FruitType::Watermelon, FruitType::Orange, FruitType::Orange, FruitType::Grape, FruitType::Seven
    };
    std::vector<FruitType> expected{
            FruitType::Cherry, FruitType::Plum, FruitType::Watermelon,
            FruitType::Lemon, FruitType::Grape, FruitType::Orange,
            FruitType::Watermelon, FruitType::Scatter, FruitType::Orange,
            FruitType::Orange, FruitType::Seven, FruitType::Grape,
            FruitType::Scatter, FruitType::Lemon, FruitType::Seven
    };
    EXPECT_EQ(FruitTypeHelper::changeIndexingByRowsIntoByColumns(byRowsVec), expected);
}

TEST(RollersSetupTest, ValidSetupTest) {

    {
        std::vector<std::vector<FruitType>> validSetup = {
                {FruitType::Scatter, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Scatter, FruitType::Orange, FruitType::Orange},

        };

        EXPECT_TRUE(FruitTypeHelper::isRollersSetupValid(validSetup));
    }
    {
        std::vector<std::vector<FruitType>> validSetup = {
                {FruitType::Orange, FruitType::Scatter, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Scatter, FruitType::Orange},

        };

        EXPECT_TRUE(FruitTypeHelper::isRollersSetupValid(validSetup));
    }


}

TEST(RollersSetupTest, InvalidSetupTest) {
    {
        std::vector<std::vector<FruitType>> invalidSetup = {
                {FruitType::Cherry,     FruitType::Scatter, FruitType::Scatter, FruitType::Orange},
                {FruitType::Plum,       FruitType::Grape,   FruitType::Orange,  FruitType::Scatter},
                {FruitType::Watermelon, FruitType::Orange,  FruitType::Grape,   FruitType::Lemon, FruitType::Scatter}
        };
        EXPECT_FALSE(FruitTypeHelper::isRollersSetupValid(invalidSetup));
    }

    {
        std::vector<std::vector<FruitType>> invalidSetup = {
                {FruitType::Scatter, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Scatter},

        };
        EXPECT_FALSE(FruitTypeHelper::isRollersSetupValid(invalidSetup));
    }

    {
        std::vector<std::vector<FruitType>> invalidSetup = {
                {FruitType::Orange, FruitType::Scatter, FruitType::Orange, FruitType::Scatter, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange, FruitType::Orange,
                 FruitType::Orange, FruitType::Orange, FruitType::Scatter, FruitType::Orange, FruitType::Orange},

        };
        EXPECT_FALSE(FruitTypeHelper::isRollersSetupValid(invalidSetup));
    }
}