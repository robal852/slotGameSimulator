#include "gtest/gtest.h"
#include "../src/Wallet.hpp"
#include "../src/Definitions.hpp"


TEST(WalletTest, ConstructorTest) {
    Wallet wallet(100);
    EXPECT_EQ(wallet.getCredits(), 100);
}

TEST(WalletTest, AddCreditsTest) {
    Wallet wallet(100);
    wallet.addCredits(50);
    EXPECT_EQ(wallet.getCredits(), 150);
}

TEST(WalletTest, ChargeBetTest) {
    {
        Wallet wallet(10500);
        size_t numOfBets = 5;
        EXPECT_TRUE(wallet.chargeBet(numOfBets));
        EXPECT_EQ(wallet.getCredits(), 10500 - numOfBets * BET);
    }

    {
        Wallet wallet(10);
        EXPECT_FALSE(wallet.chargeBet());
        EXPECT_EQ(wallet.getCredits(), 10);
    }
}

TEST(WalletTest, SetCreditsTest) {
    Wallet wallet(100);
    wallet.setCredits(200);
    EXPECT_EQ(wallet.getCredits(), 200);
}

