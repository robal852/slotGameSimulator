#pragma once

#include "FruitType.hpp"
#include <vector>
#include <map>

constexpr int NUM_ROLLERS = 5;
constexpr int ROLLER_SIZE = 40;

constexpr int BET = 100;


const std::vector<std::pair<FruitType, size_t>> WINNING_PAIRS = {
        {FruitType::Scatter,    5},
        {FruitType::Scatter,    4},
        {FruitType::Scatter,    3},
        {FruitType::Seven,      5},
        {FruitType::Seven,      4},
        {FruitType::Seven,      3},
        {FruitType::Watermelon, 5},
        {FruitType::Watermelon, 4},
        {FruitType::Watermelon, 3},
        {FruitType::Grape,      5},
        {FruitType::Grape,      4},
        {FruitType::Grape,      3},
        {FruitType::Plum,       5},
        {FruitType::Plum,       4},
        {FruitType::Plum,       3},
        {FruitType::Orange,     5},
        {FruitType::Orange,     4},
        {FruitType::Orange,     3},
        {FruitType::Lemon,      5},
        {FruitType::Lemon,      4},
        {FruitType::Lemon,      3},
        {FruitType::Cherry,     5},
        {FruitType::Cherry,     4},
        {FruitType::Cherry,     3},
        {FruitType::Cherry,     2},
};

//values of the winnings for the pairs - fruit, occurrences
const std::map<std::pair<FruitType, int>, int> PAYOUTS = {
        {{FruitType::Scatter,    5}, 5000},
        {{FruitType::Scatter,    4}, 1000},
        {{FruitType::Scatter,    3}, 200},
        {{FruitType::Scatter,    2}, 0},
        {{FruitType::Scatter,    1}, 0},
        {{FruitType::Scatter,    0}, 0},
        {{FruitType::Seven,      5}, 25000},
        {{FruitType::Seven,      4}, 5000},
        {{FruitType::Seven,      3}, 500},
        {{FruitType::Seven,      2}, 0},
        {{FruitType::Seven,      1}, 0},
        {{FruitType::Watermelon, 5}, 2500},
        {{FruitType::Watermelon, 4}, 1000},
        {{FruitType::Watermelon, 3}, 250},
        {{FruitType::Watermelon, 2}, 0},
        {{FruitType::Watermelon, 1}, 0},
        {{FruitType::Grape,      5}, 2500},
        {{FruitType::Grape,      4}, 1000},
        {{FruitType::Grape,      3}, 250},
        {{FruitType::Grape,      2}, 0},
        {{FruitType::Grape,      1}, 0},
        {{FruitType::Plum,       5}, 1000},
        {{FruitType::Plum,       4}, 250},
        {{FruitType::Plum,       3}, 100},
        {{FruitType::Plum,       2}, 0},
        {{FruitType::Plum,       1}, 0},
        {{FruitType::Orange,     5}, 1000},
        {{FruitType::Orange,     4}, 250},
        {{FruitType::Orange,     3}, 100},
        {{FruitType::Orange,     2}, 0},
        {{FruitType::Orange,     1}, 0},
        {{FruitType::Lemon,      5}, 1000},
        {{FruitType::Lemon,      4}, 250},
        {{FruitType::Lemon,      3}, 100},
        {{FruitType::Lemon,      2}, 0},
        {{FruitType::Lemon,      1}, 0},
        {{FruitType::Cherry,     5}, 1000},
        {{FruitType::Cherry,     4}, 250},
        {{FruitType::Cherry,     3}, 100},
        {{FruitType::Cherry,     2}, 25},
        {{FruitType::Cherry,     1}, 0}
};