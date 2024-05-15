#pragma once

#include <random>

class RandomGenerator {
public:
    RandomGenerator() : randomEngine(std::random_device()()) {}

    int getRandomInt(int min, int max) {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(randomEngine);
    }

private:
    std::mt19937 randomEngine;
};