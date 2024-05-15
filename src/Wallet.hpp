#pragma once
#include <cstdint>
#include <cstddef>


class Wallet
{
public:
	explicit Wallet(uint64_t startCredit);

	void setCredits(uint64_t newCredits);

	void addCredits(uint64_t amount);

    bool chargeBet(size_t numOfBets = 1);

	uint64_t getCredits() const;

private:
	uint64_t credits;
};

