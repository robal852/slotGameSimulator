#include "Wallet.hpp"
#include <iostream>
#include "Definitions.hpp"

Wallet::Wallet(uint64_t startCredit) : credits(startCredit) {
    std::cout << "Created wallet with " << startCredit << " credits.\n";
}

void Wallet::setCredits(uint64_t newCredits) {
    credits = newCredits;
}

void Wallet::addCredits(uint64_t amount) {
    credits += amount;
}

bool Wallet::chargeBet(size_t numOfBets) {
    if (numOfBets * BET <= credits) {
        credits -= numOfBets * BET;
        return true;
    }
    std::cout << "Not enough credits to bet!" << std::endl;
    return false;
}

uint64_t Wallet::getCredits() const {
    return credits;
}
