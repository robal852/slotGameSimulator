#include "gtest/gtest.h"
#include "../src/RandomGenerator.hpp"

TEST(RandomGeneratorTest, RandomIntInRange) {
    RandomGenerator randomGen;
    int min = 0;
    int max = 5;
    int randomInt = randomGen.getRandomInt(min, max);
    EXPECT_GE(randomInt, min);
    EXPECT_LE(randomInt, max);
}
